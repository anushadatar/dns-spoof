/**
 * DNS Manager
 * Contains implementation of methods associated with parsing incoming
 * messages and creating responses by modifying those messages in place.
*/

#include <err.h>
#include <string.h>

#include "dns_defns.h"
#include "dns_manager.h"

ssize_t add_answers(uint8_t *message, uint16_t message_qd, ssize_t message_size, char *default_adddress_response)
{
    // The total response size, offset by the header.
    ssize_t response_size = DNS_HEADER_SIZE;

    // Keep track of the current position within the message.
    uint16_t positions[DNS_MAX_QUESTIONS];

    // Go through all of the questions and update the response size accordingly.
    // Parsed based on information from RFC 1035 4.1.2.
    for (uint8_t question_number = 0; question_number < message_qd; question_number++)
    {
        // Keep response size so far within the qustions.
        positions[question_number] = response_size;

        // Ensure the name size is valid and then add it to the response size.
        int name_size = get_name_size(response_size + message);
        if (name_size < 0)
        {
            set_format_error_flags(message);
            return message_size;
        }
        response_size += name_size;

        // Ensure that we support the question type.
        uint16_t question_type = ntohs(*(uint16_t *)(message + response_size));
        if (question_type != DNS_RR_TYPE_ANY && question_type != DNS_RR_TYPE_A)
        {
            set_not_implemented_flags(message);
            return message_size;
        }

        // The next value is the question class, ensure we support that.
        uint16_t question_class = ntohs(*(uint16_t *)(message + response_size + sizeof(uint16_t)));
        if (question_class != DNS_RR_CLASS_ANY && question_class != DNS_RR_CLASS_IN)
        {
            set_not_implemented_flags(message);
            return message_size;
        }

        // Add 32 bits to the response size to account for the question class
        // and type.
        response_size += sizeof(uint32_t);
    }

    // Go through and add to the answers section, see RFC 1035 4.1.3.
    for (uint8_t answer_number = 0; answer_number < message_qd; answer_number++)
    {
        positions[answer_number] |= 0xC000; // First two bits should be one.
                                            // See RFC 1035 4.1.4.

        // Add the response length so far.
        *(uint16_t *)(message + response_size) = htons(positions[answer_number]);
        response_size += sizeof(uint16_t);

        // Add the resource record types.
        *(uint16_t *)(message + response_size) = htons(DNS_RR_TYPE_A);
        *(uint16_t *)(message + response_size + sizeof(uint16_t)) = htons(DNS_RR_CLASS_IN);
        response_size += sizeof(uint32_t);

        // Add the TTL and account for its size
        *(uint32_t *)(message + response_size) = htonl(DNS_TTL);
        response_size += sizeof(uint32_t);

        // Add the size of the address and the address itself.
        *(uint16_t *)(message + response_size) = htons(sizeof(in_addr_t));
        *(in_addr_t *)(message + response_size + sizeof(uint16_t)) = inet_addr(default_adddress_response);

        // Add both of their sizes to the response size.
        response_size += sizeof(in_addr_t) + sizeof(uint16_t);
    }
    // Return the entire aggregated response size.
    return response_size;
}

ssize_t parse_message(uint8_t *message, ssize_t message_size, char *default_adddress_response)
{
    // If the message is a response, drop it.
    if (get_dns_flags(message) & DNS_FLAG_QR)
    {
        return 0;
    }

    // The number of questions should usually be 1, but confirm that the count
    // falls within the supported threshold before continuing.
    uint16_t message_qd = get_dns_qdcount(message);
    if (message_qd == 0 || message_qd > DNS_MAX_QUESTIONS)
    {
        set_not_implemented_flags(message);
        return message_size;
    }

    // Check that we support the contents of the request.
    if (get_dns_ancount(message) || get_dns_nscount(message))
    {
        set_not_implemented_flags(message);
        return message_size;
    }

    // Overwrite any additional records present in the request..
    if (get_dns_arcount(message))
    {
        set_dns_arcount(message, 0);
    }

    // Process each question, return the response length as its needed when
    // calling sendto() to respond.
    ssize_t response_size = add_answers(message, message_qd, message_size, default_adddress_response);

    // Set the DNS answer to the number of questions asked.
    set_dns_ancount(message, message_qd);

    // Set the default DNS flags associated with what this minimal
    // implementation can actually support.
    set_default_dns_flags(message);
    return response_size;
}

void set_not_implemented_flags(uint8_t *message)
{
    uint16_t flags = get_dns_flags(message);
    flags &= ~DNS_FLAG_RCODE_MASK;
    flags = DNS_FLAG_QR | DNS_FLAG_RCODE_FORMAT_ERROR;
    set_dns_flags(message, flags);
}

void set_format_error_flags(uint8_t *message)
{
    uint16_t flags = get_dns_flags(message);
    flags &= ~DNS_FLAG_RCODE_MASK;
    flags = DNS_FLAG_QR | DNS_FLAG_RCODE_FORMAT_ERROR;
    set_dns_flags(message, flags);
}

void set_default_dns_flags(uint8_t *message)
{
    uint16_t flags = get_dns_flags(message);
    flags &= ~DNS_FLAG_AA;
    flags |= DNS_FLAG_QR;
    flags |= DNS_FLAG_RD;
    flags |= DNS_FLAG_RA;
    flags &= ~DNS_FLAG_RCODE_MASK;
    flags &= ~DNS_FLAG_Z;
    set_dns_flags(message, flags);
}

uint8_t get_name_size(uint8_t *message)
{
    int length = 0;
    while (message[length] > 0 && length <= DNS_NAME_MAX_SIZE)
    {
        length += message[length];
        // Shift over to the next value.
        length += 1;
    }
    if (length < DNS_NAME_MAX_SIZE)
    {
        return length + 1;
    }
    return -1;
}

uint16_t get_dns_id(uint8_t *message)
{
    return ntohs(*(uint16_t *)(message + DNS_POSITION_ID));
}

void set_dns_id(uint8_t *message, uint16_t value)
{
    *(uint16_t *)(message + DNS_POSITION_ID) = htons(value);
}

uint16_t get_dns_flags(uint8_t *message)
{
    return ntohs(*(uint16_t *)(message + DNS_POSITION_FLAGS));
}

void set_dns_flags(uint8_t *message, uint16_t value)
{
    *(uint16_t *)(message + DNS_POSITION_FLAGS) = htons(value);
}

uint16_t get_dns_qdcount(uint8_t *message)
{
    return ntohs(*(uint16_t *)(message + DNS_POSITION_QDCOUNT));
}

void set_dns_qdcount(uint8_t *message, uint16_t value)
{
    *(uint16_t *)(message + DNS_POSITION_QDCOUNT) = htons(value);
}

uint16_t get_dns_ancount(uint8_t *message)
{
    return ntohs(*(uint16_t *)(message + DNS_POSITION_ANCOUNT));
}

void set_dns_ancount(uint8_t *message, uint16_t value)
{
    *(uint16_t *)(message + DNS_POSITION_ANCOUNT) = htons(value);
}

uint16_t get_dns_nscount(uint8_t *message)
{
    return ntohs(*(uint16_t *)(message + DNS_POSITION_NSCOUNT));
}

void set_dns_nscount(uint8_t *message, uint16_t value)
{
    *(uint16_t *)(message + DNS_POSITION_NSCOUNT) = htons(value);
}

uint16_t get_dns_arcount(uint8_t *message)
{
    return ntohs(*(uint16_t *)(message + DNS_POSITION_ARCOUNT));
}

void set_dns_arcount(uint8_t *message, uint16_t value)
{
    *(uint16_t *)(message + DNS_POSITION_ARCOUNT) = htons(value);
}