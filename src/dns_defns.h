/**
 * Definitions associated with the DNS specification as needed for a minimal
 * DNS spoofing daemon implementation.
*/

#ifndef DNS_DEFNS_H
#define DNS_DEFNS_H

#include <stdint.h>

// Total header size, as specified in RFC 1035 4.1.1.
#define DNS_HEADER_SIZE 12

// Each item's position in the header, as specified in RFC 1035 4.1.1.
#define DNS_POSITION_ID 0
#define DNS_POSITION_FLAGS 2
#define DNS_POSITION_QDCOUNT 4
#define DNS_POSITION_ANCOUNT 6
#define DNS_POSITION_NSCOUNT 8
#define DNS_POSITION_ARCOUNT 10

// Size parameters, as specified in RFC 1035 2.3.4.
#define DNS_TTL_LIMIT 60 // Can be modified according to system reqs.
#define DNS_NAME_MAX_SIZE 255
#define DNS_UDP_MAX_SIZE 255
#define DNS_LABEL_MAX_SIZE 63

// Flag definitions for manipulation of entire vector.
// Defined in RFC 1035 4.1.4.
#define DNS_FLAG_QR 0x8000
#define DNS_FLAG_OPCODE 0x7400
#define DNS_FLAG_AA 0x0400
#define DNS_FLAG_RD 0x0100
#define DNS_FLAG_RA 0x0080
#define DNS_FLAG_Z 0x0070
#define DNS_FLAG_RCODE_MASK 0x000F
#define DNS_FLAG_RCODE_FORMAT_ERROR 0x0001
#define DNS_FLAG_RCODE_NOT_IMPLEMENTED 0x0004

// Supported Resource Record types, specified in RFC 1035 3.2.3.
#define DNS_RR_TYPE_A 1     // A host address.
#define DNS_RR_TYPE_ANY 255 // Any record.

// Supported Resource Record classes, specified in RFC 1035 3.2.4.
#define DNS_RR_CLASS_IN 1    // Internet class.
#define DNS_RR_CLASS_ANY 255 // Any class.

// The maximum number of questions to answer.
#define DNS_MAX_QUESTIONS 10

// The Time To Live, can be modified as needed.
#define DNS_TTL 3600

// The number of packets to process
#define DNS_NUMBER_OF_PACKETS 1000

#endif // DNS_DEFNS_H