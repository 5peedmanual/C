#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "hacking.h"

#define PORT 80
#define WEBROOT "/home/joji/Desktop/C/book/networking/webroot" // The webserver's root directory

void handle_connection(int, struct sockaddr_in *); // Handle web requests
int get_file_size(int); // Returns the filesize of open file descriptor

int main(int argc, char const *argv[]) {
    int sockfd, new_sockfd, yes=1;
    struct sockaddr_in host_addr, client_addr; // My address information
    socklen_t sin_size;

    printf("Accepting web requests on port %d\n", PORT);

    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        fatal("in socket");

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        fatal("setting socket option SO_REUSEADDR");

    host_addr.sin_family = AF_INET; // Host byte order
    host_addr.sin_port = htons(PORT); // Short, network byte order
    host_addr.sin_addr.s_addr = INADDR_ANY; // Automatically fill with my IP
    memset(&(host_addr.sin_zero), '\0', 8); // Zero the rest of the struct

    if(bind(sockfd, (struct sockaddr *) &host_addr, sizeof(struct sockaddr)) == -1)
        fatal("binding socket");

    if(listen(sockfd, 20) == -1)
        fatal("listening on socket");

    while(1) {
        sin_size = sizeof(struct sockaddr_in);
        new_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &sin_size);
        if(new_sockfd == -1)
            fatal("accepting connection");

        handle_connection(new_sockfd, &client_addr);
    }
    return 0;
}

/*
* This function handles the connection on the passed socket from the
* passed client address. The connection is processed as a web request,
* and this function replies over the connected socket. Finally, the
* passed socket is closed at the end of the function.
*/

void handle_connection(int sockfd, struct sockaddr_in *client_addr_ptr) {
    unsigned char *ptr, request[500], resource[500];
    int fd, length;

    length = recv_line(sockfd, request);

    printf("Got request from %s:%d \"%s\"\n", inet_ntoa(client_addr_ptr->sin_addr), ntohs(client_addr_ptr->sin_port), request);

/*
* The  strstr() function finds the first occurrence of the substring nee‐
* dle in the string haystack.  The terminating null bytes ('\0') are  not
* compared. In this case the substring is HTTP/ in the request buffer
*/
    ptr = strstr(request, "HTTP/"); // Search for valid-looking request
    printf("Printing ptr: %s\n", ptr);
    if(ptr == NULL) { //Then this isn't valid HTTP
        printf("NOT HTTP!\n");
    } else {
        /*
        * requests HEAD and GET are recognized as processable
        * requests. A HEAD request will just return the headers, while a GET request will
        * also return the requested resource
        */
        *ptr = 0; // Terminate the buffer at the end of the URL
        ptr = NULL; // Set ptr to NULL (used to flag for an invalid request)
        if(strncmp(request, "GET ", 4) == 0) { // GET request
            ptr = request+4; // ptr is the URL
            printf("Printing ptr (GET): %s\n", ptr);
        }
        if(strncmp(request, "HEAD ", 5) == 0) { // HEAD request
            ptr = request+5;
            printf("Printing ptr (HEAD): %s\n", ptr);
        }


        if(ptr == NULL) { // Then this is not a recognized request
            printf("\tUNKNOWN REQUEST!\n");
        } else { // Valid request, with ptr pointing to the resource name
            if(ptr[strlen(ptr) -1] == '/') // For resources ending with '/',
                // strcat(char *dest, const char *src);
                strcat(ptr, "index.html"); // add 'index.html' to the end
            strcpy(resource, WEBROOT);     // Begin resource with web root path
            strcat(resource, ptr);         // and join it with resource path
            fd = open(resource, O_RDONLY, 0); // open the file
            printf("\tOpening \'%s\'", resource);
            if(fd == -1) {
                printf(" 404 Not Found\n");
                send_string(sockfd, "HTTP/1.0 404 NOT FOUND\r\n");
                send_string(sockfd, "Server: Tiny webserver\r\n\r\n");
                send_string(sockfd, "<html><head><title>404 Not Found</title></head>");
                send_string(sockfd, "<body><h1>URL not found</h1></body></html>\r\n");
            } else {  // Otherwise, server up the file
                printf(" 200 OK\n");
                send_string(sockfd, "HTTP/1.0 200 OK\r\n");
                send_string(sockfd, "Server: Tiny webserver\r\n\r\n");
                if(ptr == request +4) {
                    if((length = get_file_size(fd)) ==  -1)
                        fatal("getting resorce file size");
                    if((ptr = (unsigned char *) malloc(length)) == NULL)
                        fatal("allocating memory for reading resource");
                    /*
                    * read(int fd, void *buf, size_t count);
                    * read()  attempts to read up to count bytes from file descriptor fd into
                    * the buffer starting at buf.
                    */
                    read(fd, ptr, length); // Read the file into memory
                    // send(int sockfd, const void *buf, size_t len, int flags);
                    send(sockfd, ptr, length, 0); // Send it to the socket
                    free(ptr); // Free file memory
                }
                close(fd); // Close the file
            } // End if block for file found/not found
        } // End if block for valid request
    } // End if block for valid HTTP
    shutdown(sockfd, SHUT_RDWR); // Close the socket
}
/*
* This function accepts an open file descriptor and returns
* the size of the associated file. Returns -1 on failure.
*/
int get_file_size(int fd) {
    struct stat stat_struct;
    if(fstat(fd, &stat_struct) == -1) // Get file status
        return -1;
    return (int) stat_struct.st_size;
}
