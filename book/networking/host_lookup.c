#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include "hacking.h"

/*
* This program accepts a hostname as its only argument and prints out the IP address.
* The gethostbyname() function returns a pointer to a hostent structure,
* which contains the IP address in element h_addr . A pointer to this element
* is typecast into an in_addr pointer, which is later dereferenced for the call to
* inet_ntoa() , which expects a in_addr structure as its argument.
*/

int main(int argc, char *argv[]) {
    struct hostent *host_info;
    struct in_addr *address;

    if(argc < 2) {
        printf("Usage: %s <hostname>\n", argv[0]);
        exit(1);
    }

    host_info = gethostbyname(argv[1]); // Return the pointer to a hostent struct
    if(host_info == NULL) {
        printf("Couldn't lookup %s\n", argv[1]);

    } else {
        address = (struct in_addr *) (host_info->h_addr);
        printf("%s has address %s \n", argv[1], inet_ntoa(*address));
    }
    return 0;
}
