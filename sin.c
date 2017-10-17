#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netdb.h>
#include <unistd.h>
#include <assert.h>
#include "mylib.h"

#define CONN
#define DEBUG
#define req "GET / HTTP/1.1\r\n"
#define BUF_LEN 1024


void die_with_error(char *);
FILE *open_file(char *file);
void *connect_to(void* ip);
void reverse_dns_lookup(char *ip);



int main(int argc, char *argv[])
{
    #ifdef THREADS
        static int i = 0;
        pthread_t threads[i];
    #endif

    FILE *ptr = open_file("ips.txt");
    char read_string[100];
    // char *fgets(char *s, int size, FILE *stream);
    while(fgets(read_string, sizeof(read_string), ptr) != NULL)
    {
        /* int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg); */
        #if (defined(DEBUG) && defined(THREADS))
            printf("%i\n", i);
            printf("IP %s\n", read_string);
        #endif
        #ifdef THREADS
            pthread_attr_t attr;
            printf("Creating a thread for [%s]...\n", read_string);
            pthread_attr_init(&attr);
            pthread_create(&threads[i], &attr, connect_to, (void*) &read_string);
            i++;
        #endif

        connect_to(read_string);
    }
    #ifdef THREADS
        pthread_join(threads[i],NULL);
    #endif

   return 0;
}
void *connect_to(void* ip)
{
    char get_request_buffer[BUF_LEN], get_response_buffer[BUF_LEN]; // Buffers for request and response
    // -- Headers -- //
    char request_headers_one[1024] = "GET ";
    char request_headers_two[200] = "HTTP/1.1\r\nHost: %s\r\nuser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:12.0) Gecko/20100101 Firefox/12.0\r\nContent-type: application/x-www-form-urlencoded\r\n\r\n";

    // ------------- //
    char *hostname = "195.23.42.21";
    in_addr_t in_addr;
    int request_len, sock, bytes_received;
    ssize_t bytes_to_send, line;
    struct hostent *hostent;
    struct sockaddr_in server_addr;
    uint16_t server_port = 80;

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        die_with_error("creating socket");

    hostent = gethostbyname("195.23.42.21"); //  Here name is either a hostname or an IPv4 address
    reverse_dns_lookup("195.23.42.21");
    // printf("%d\n", *hostent->h_name);


    //      struct hostent {
    //            char  *h_name;            /* official name of host */
    //            char **h_aliases;         /* alias list */
    //            int    h_addrtype;        /* host address type */
    //            int    h_length;          /* length of address */
    //            char **h_addr_list;       /* list of addresses */
    //        }
    #ifdef DEBUG
        printf("[hostent] addr %s \n", hostent->h_name);
        printf("[hostent] aliases %s \n", *(hostent->h_aliases));
    #endif


    in_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));

    server_addr.sin_addr.s_addr = in_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);


    printf("Connecting to %s port %d\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));
    if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        die_with_error("connecting");

    /* ssize_t write(int fd, const void *buf, size_t count); */
    FILE *ptr = open_file("dirs.txt");
    char read_string[100];
    char *ptr_rm;
    ptr_rm = read_string;
    // ptr_dir = (char *)&request_headers + 4;
    // ptr_dir = request_headers+3;
    while(fgets(read_string, sizeof(read_string), ptr) != NULL)
    {
        printf("%d\n", sizeof(read_string));
        for(ptr_rm; *ptr_rm < sizeof(read_string); ptr_rm++)
        {
            printf("ptr %c\n", *ptr_rm+1);
            if(*ptr_rm == ' ')
                *ptr_rm = 'a';
        }
        printf("DIRECTORY %s", (char *)ptr_rm);
        request_len = 0;
        // snprintf(get_request_buffer, BUF_LEN, request_headers_two, hostname);
        strcpy(request_headers_one+4, (char *) read_string); // Remove the newline character
        // printf("%s\n",request_headers_one );
        // strcpy(request_headers_one, request_headers_two); // add 'index.html' to the end.
        // strcat(ptr_dir+3, request_headers); // add 'index.html' to the end.
        printf("%s\n", request_headers_one);
        // strcat(request_headers, ptr_dir + sizeof(read_string)); // and join it with resource path.


        // printf("%s\n", read_string);
        // printf("\n-----------REQUEST-------------\n%s--------------------------------\n",get_request_buffer );
        // bytes_to_send = 0;
        // puts("Sending...");
        // while(bytes_to_send < request_len)
        // {
        //     if((line = write(sock, get_request_buffer, request_len)) == -1)
        //         die_with_error("in write");
        //     bytes_to_send += line;
        // }
        //
        // puts("receiving...");
        // bytes_received = 1;
        // while(bytes_received = recv(sock, &get_response_buffer, BUF_LEN, 0) > 1)
        // {
        //     #ifdef DEBUG
        //         printf("RECV: %d bytes\n", bytes_received);
        //     #endif
        //     bytes_received = write(sock, &get_response_buffer, BUF_LEN);
        //     // printf("%d\n",recv_length );
        //     printf("\n-----------RESPONSE-------------\n%s-----------------------------\n",get_response_buffer );
        //     if(strstr(get_response_buffer, "HTTP/1.1 404 Not Found"))
        //     {
        //         puts("Not found");
        //     }
        //     else if(strstr(get_response_buffer, "HTTP/1.1 302 Found"))
        //     {
        //         puts("302");
        //         exit(-1);
        //         break;
        //     }
        //     else if(strstr(get_response_buffer, "HTTP/1.1 200 OK"))
        //     {
        //         puts("OK");
        //         // exit(-1);
        //     }
        //     else
        //     {
        //         puts("not OK");
        //         // exit(-1);
        //     }


            // }

        // close(sock);
        // pthread_exit(0);

    }
    exit(-1);
}
