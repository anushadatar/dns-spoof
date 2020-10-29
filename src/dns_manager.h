/**
 * Contains implementation of methods associated with parsing incoming DNS
 * requests and creating responses by modifying those messages in place.
 */
#ifndef DNS_MANAGER_H
#define DNS_MANAGER_H
#include <err.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <stdint.h>

/**
 * Set the non-implemented flags in the given message. Modifies the message
 * in place.
 * 
 * message : Pointer to the message to set the non-implemented flags for.
 * returns : Void, modifies the message in place.
 */
ssize_t add_answers(uint8_t *message, uint16_t message_qd, ssize_t message_size, char *default_adddress_response);

/** 
 * Process incoming messages. If the received message is valid,
 * process its content to generate a response, modify the message in place to
 * match that response, and then send it.
 * 
 * message : Pointer to the incoming message.
 * returns : Size of new message. Message itself modified in place.
 */
ssize_t parse_message(uint8_t *message, ssize_t message_size, char *default_adddress_response);

/**
 * Set the non-implemented flags in the given message. Modifies the message
 * in place.
 * 
 * message : Pointer to the message to set the non-implemented flags for.
 * returns : Void, modifies the message in place.
 */
void set_not_implemented_flags(uint8_t *message);

/**
 * Set the flags to indicate there is a formatting error. Modifies the message
 * in place.
 * 
 * message : Pointer to the message to set the format error flags for.
 * returns : Void, modifies the message in place. 
 */
void set_format_error_flags(uint8_t *message);

/**
 * Set the DNS flags to default values for a valid response.
 * 
 * message : Pointer to the message to set the flags for.
 * returns : Void, modifies the message in place. 
 */
void set_default_dns_flags(uint8_t *message);

/**
 * Returns the name size of the given question.
 * 
 * message : Pointer to the message to find the name size for, shifted to the question location.
 * returns : Name size, as a uint8_t.
 */
uint8_t get_name_size(uint8_t *message);

/**
 * Get the DNS ID which is a 16 bit identifier used to match queries and their replies.
 * 
 * message : Pointer to the message to get the ID of.
 * returns : The message's associated DNS ID, as a uint16_t.
 */
uint16_t get_dns_id(uint8_t *message);

/**
 * Set the DNS ID which is a 16 bit identifier used to match queries and their replies.
 * Modifies the message in place.
 * 
 * message : Pointer to the message to get the ID of.
 * value   : The message's associated DNS ID, as a uint16_t.
 */
void set_dns_id(uint8_t *message, uint16_t value);

/**
 * Get the DNS flags.
 * 
 * message : Pointer to the message to get the flags of.
 * returns : The message's associated flags, as a uint16_t.
 */
uint16_t get_dns_flags(uint8_t *message);

/**
 * Set the DNS flags.
 * Modifies the message in place.
 * 
 * message : Pointer to the message to get the ID of.
 * value   : The message's associated DNS ID, as a uint16_t.
 */
void set_dns_flags(uint8_t *message, uint16_t val);

/**
 * Get the DNS QD count which is a 16 bit count of the number 
 * of entries in the question section.
 * 
 * message : Pointer to the message to get the QD count of.
 * returns : The message's QD count, as a uint16_t.
 */

uint16_t get_dns_qdcount(uint8_t *message);

/**
 * Set the DNS QD count which is a 16 bit count of the number 
 * of entries in the question section.
 * 
 * message : Pointer to the message to get the QD count of.
 * value   : The message's desired QD count, as a uint16_t.
 */
void set_dns_qdcount(uint8_t *message, uint16_t val);

/**
 * Get the DNS AN count which is a 16 bit count of the number 
 * of resource records in the answer section
 * 
 * message : Pointer to the message to get the flags of.
 * returns : The message's AN count, as a uint16_t.
 */
uint16_t get_dns_ancount(uint8_t *message);

/**
 * Set the DNS AN count which is a 16 bit count of the number 
 * of resource records in the answer section
 * 
 * message : Pointer to the message to get the flags of.
 * value   : The message's desired AN count, as a uint16_t.
 */
void set_dns_ancount(uint8_t *message, uint16_t val);

/**
 * Get the DNS NS count which is a 16 bit count of the number 
 * of name server resource records in the authority records section.
 * 
 * message : Pointer to the message to get the flags of.
 * returns : The message's NS count, as a uint16_t.
 */
uint16_t get_dns_nscount(uint8_t *message);

/**
 * Set the DNS NS count which is a 16 bit count of the number 
 * of resource records in the answer section
 * 
 * message : Pointer to the message to get the flags of.
 * value   : The message's desired NS count, as a uint16_t.
 */
void set_dns_nscount(uint8_t *message, uint16_t val);

/**
 * Set the DNS AR count which is a 16 bit count of the number 
 * of resource records in the additional records section.
 * 
 * message : Pointer to the message to get the AR count of.
 * returns   : The message's AR count, as a uint16_t.
 */
uint16_t get_dns_arcount(uint8_t *message);

/**
 * Set the DNS AR count which is a 16 bit count of the number 
 * of resource records in the additional records section.
 * 
 * message : Pointer to the message to set the AR count of.
 * value   : The message's desired AR count, as a uint16_t.
 */
void set_dns_arcount(uint8_t *message, uint16_t val);

#endif // DNS_MANAGER_H
