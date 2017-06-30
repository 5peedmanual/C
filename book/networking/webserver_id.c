#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "hacking.h"

int main(int argc, char const *argv[]) {
    int sockfd;
    struct hostent *host_info;
    struct sockaddr_in target_addr;
    unsigned char buffer[4096];

    if(argc < 2) {
        printf("Usage: %s <hostname>\n", argv[0]);
        exit(1);
    }

    if((host_info = gethostbyname(argv[1])) == NULL)
        fatal("looking up hostname");
    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        fatal("in socket");

    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(80);
    target_addr.sin_addr = *((struct in_addr *)host_info->h_addr);

    /*
    * memset() - Fill memory with a constant byte
    * Fills the first n bytes of the memory area pointed to by s with the
    * constant byte c
    * Returns a pointer to the memory area s
    */
    memset(&(target_addr.sin_zero), '\0', 8); // Zero out the rest of the struct

    /*
    * connect - initiate a connection on a socket
    * int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    * The connect() system call connects the socket referred to by the file
    * descriptor sockfd to the address specified by addr. The addrlen argument
    * specifies the size of addr
    */
    if(connect(sockfd,(struct sockaddr *)&target_addr, sizeof(struct sockaddr)) == -1)
        fatal("connecting to target server");

    send_string(sockfd, "HEAD / HTTP/1.0\r\n\r\n");

    while(recv_line(sockfd, buffer)) {
        if (strncasecmp(buffer,"Server:", 7) == 0) { // strncasecmp compares 2 strings ignoring the case
            printf("The web server for %s is %s\n", argv[1], buffer+8);
            exit(0);
        }
    }
    printf("Server line not found\n");
    exit(1);
    // return 0;
}
