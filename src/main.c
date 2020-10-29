/**
 * Run the DNS spoofing daemon on the user-specified address and port.
 */
// TODO Trim all unnecessary import statements.
#include <err.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "dns_defns.h"
#include "dns_manager.h"

// Support unit testing the main method.
#ifdef UNIT_TEST
  #define main PRODUCTION_MAIN // Break from macro style a little.
  #define NUMBER_OF_PACKETS 1  // Run exactly once for unit tests.
#endif

// The buffer associated with the current packet the daemon is handling.
uint8_t current_packet[DNS_UDP_MAX_SIZE];

/**
 * Display a usage message when the user specifies an unknown or incorrect
 * argument or uses the -h argument.
*/
void display_help_message(void)
{
  fprintf(stderr, "Run this program with ./dnsspoof, wit");
  exit(1);
}

/**
 * Loop through incoming data sent over the socket, parse the message, modify it
 * in place with a response, and then send the response over the socket.
 *
 * socket : The int number associated with the initialized socket.
 * default_address_response : The char array holding the hardcoded response.
 */
void process_incoming_data(int socket, char *default_address_response)
{
    (void) socket;
    struct sockaddr_in client_sin;
    unsigned int client_sin_len;

    ssize_t received_message_size; 
    int number_of_packets = 0;

    while(number_of_packets < DNS_NUMBER_OF_PACKETS)
    {
        client_sin_len = sizeof(client_sin); // reset the size every time we call recvfrom()
        received_message_size = recvfrom(socket, current_packet, sizeof(current_packet), 0, (struct sockaddr *)&client_sin, (socklen_t *)&client_sin_len);
        // Drop any messages that are smaller than the DNS header size as they are likely invalid.
        if (received_message_size < DNS_HEADER_SIZE) {
            fprintf(stderr, "Received message has insufficient length, dropping message\n");
            continue;
        }
        ssize_t new_message_size = parse_message(current_packet, received_message_size, default_address_response);
        // If we get some received packet, we can go ahead and respond with it.
        if (new_message_size > DNS_HEADER_SIZE) {
            // TODO Modify this command
          if (sendto(socket, current_packet, new_message_size, 0, (struct sockaddr *)&client_sin, (socklen_t)(client_sin_len)) != new_message_size)
          {
            warn("sendto");
          }
        }
        else {
          fprintf(stderr, "Message is too small , dropping message\n");
        }
        number_of_packets++;
    }
}

/**
 * Initializes socket and starts processing incoming packets.
 * 
 * param port : The port number associated with the socket.
 * param default_address_response : The hardcoded address to respond to all
 *                                  requests with.
 * TODO remove dependency on sockaddr_in 
*/
void initialize_data_processing(int port, char *default_address_response)
{
  (void)port;
  int new_socket;
  struct sockaddr_in socket_parameters;

  new_socket = socket(PF_INET, SOCK_DGRAM, 0);

  if (new_socket < 0) {
    err(1, "socket");
  }

  // Set the port number.
  socket_parameters.sin_port = htons(port);
  // Set other socket parameters for DNS/Internet.
  socket_parameters.sin_family = AF_INET;
  socket_parameters.sin_addr.s_addr = INADDR_ANY;
  // Bind socket. 
  int bind_result = bind(new_socket, (struct sockaddr *)&socket_parameters, sizeof(socket_parameters)); 
  if (bind_result) {
    err(1, "bind");
  }
  process_incoming_data(new_socket, default_address_response);
  
}

/** 
 * Parse incoming arguments for the port and address. If the port and address
 * are specified and valid (or unspecified and therefore default), initialize
 * the socket and start processing incoming packets. If this method executes in
 * a unit test, it should process exactly one packet, otherwise it should
 * continue indefinitely.
 */
int main(int argc, char *argv[])
{  
  // Current argument (for parsing incoming arguments).
  int current;
  // Default port number, user can overwrite with '-p' command.
  int portnum = 12345;
  // Defauylt address response, user can overwrite with '-a' command.
  char default_address_response[100] = "6.6.6.6";
 
  // Iterate through incoming arguments. Referenced following resource:
  // https://www.geeksforgeeks.org/getopt-function-in-c-to-parse-command-line-arguments/
  while((current = getopt(argc, argv, "p:h:a:")) != -1) {
    switch((char)current) {     
      case 'h':
        display_help_message();
        break;
      case 'p':
        // TODO Add error checking here.
        portnum = strtoul(optarg, &optarg, 0);
        break;
      case 'a':
        // TODO Add error checking here, this does not work.
        strncpy(default_address_response, optarg, sizeof(default_address_response));
        if (inet_addr(default_address_response) < 0) {
          fprintf(stderr, "Invalid IP address.");
          display_help_message();
        }
        break;
      default:
        display_help_message();
        break;
    }
  }
  // Initialize socket on given port, and run loop for incoming messages.
  initialize_data_processing(portnum, default_address_response);    
  return 0;
}
