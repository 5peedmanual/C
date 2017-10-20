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
#define BUF_LEN 100
#define FIXQA
#define THREADS
// #define ARGS

void die_with_error(char *); // error function
FILE *open_file(char *file); // read ip and uri lists
void *connect_to(void* ip); // Creates the socket sends the request and checks status response
void reverse_dns_lookup(char *ip); // reverse dns
void remove_new_line(char *source); // remove the new-line character at the end of a string
void print_usage(char *program_name); // Print run program usage

int main(int argc, char *argv[])
{
    #ifdef THREADS
        static int i = 0;
        pthread_t threads[i];
        pthread_attr_t attr;
    #endif
    #ifdef ARGS
        /* Check arguments */
        if( argc < 2 || argc > 4)
            print_usage(argv[0]);

        if((strlen(argv[1])) || (strlen(argv[2]) > 100))
            exit(-1);

        FILE *ptr = open_file(argv[1]);
    #else
        FILE *ptr = open_file("ips.txt");
    #endif

    char read_string[100];
    // char *fgets(char *s, int size, FILE *stream);
    while(fgets(read_string, sizeof(read_string), ptr) != NULL)
    {
        // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
        #if (defined(DEBUG) && defined(THREADS))
            printf("%i\n", i);
            printf("IP %s\n", read_string);
        #endif
        #ifdef THREADS

            printf("Creating a thread for [%s]...\n", read_string);
            pthread_attr_init(&attr);
            pthread_create(&threads[i], &attr, connect_to, (void*) &read_string);
            i++;
        #else
            connect_to(read_string);
        #endif
    }
    #ifdef THREADS
        pthread_join(threads[i],NULL);
    #endif

   return 0;
}

void *connect_to(void* ip)
{
    char get_request_buffer[BUF_LEN] /*,get_response_buffer[BUF_LEN]*/; // Buffers for request and response
    char *get_response_buffer;
    get_response_buffer = (char *) malloc(1024*1024*100); // 100mb
    // -- Headers -- //
    char request_headers_one[1024] = "GET ";
    char request_headers_two[200] = "HTTP/1.1\r\nHost: 195.23.42.21\r\nuser-Agent: TotallynotaBotMozilla/5.0 (X11; Linux x86_64; rv:12.0) Gecko/20100101 Firefox/12.0\r\nContent-type: application/x-www-form-urlencoded\r\n\r\n";
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

    // memset(&hints, 0, sizeof hints); // Zero out the struct
    hostent = gethostbyname("195.23.42.21"); //  Here name is either a hostname or an IPv4 address
    /* Change gethostbyname to getaddrinfo!
    int getaddrinfo(const char *node, // e.g. "www.example.com" or IP
    const char *service, // e.g. "http" or port number
    const struct addrinfo *hints,
    struct addrinfo **res);
    */
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
        printf("[DEBUG]\t[hostent] addr %s \n", hostent->h_name);
        // printf("[hostent] aliases %s \n", *(hostent->h_aliases));
    #endif


    in_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));
    server_addr.sin_addr.s_addr = in_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);


    printf("[DEBUG]\tConnecting to %s port %d\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));
    if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        die_with_error("connecting");

    /* ssize_t write(int fd, const void *buf, size_t count); */
    FILE *ptr = open_file("dirs.txt");
    char read_string[100];
    char *ptr_rm;

    while(fgets(read_string, sizeof(read_string), ptr) != NULL)
    {
        remove_new_line(read_string); // sin

        strcpy(request_headers_one+4, (char *) read_string); // add the readstring with '\n' removed
        strcat(request_headers_one, request_headers_two); // join the rest of the request to the end
        // printf("DIRECTORY %s\n", (char *)ptr_rm);
        // printf("request_headers_one\n%s\n", request_headers_one);

        printf("[URI]\t%s\n", read_string);
        // printf("\n-----------REQUEST-------------\n%s--------------------------------\n",request_headers_one );
        bytes_to_send = 0;

        puts("\n[DEBUG]\tSending...\n");
        while(bytes_to_send < sizeof(request_headers_one))
        {
            if((line = write(sock, request_headers_one, sizeof(request_headers_one))) == -1)
                die_with_error("in write");
            bytes_to_send += line;
        }

        puts("[DEBUG]\treceiving...\n");
        bytes_received = recv(sock, get_response_buffer, 4096, 0);
        while(bytes_received > 1)
        {
            printf("\n----------RESPONSE-----------\n%s\n-----------------------------\n",get_response_buffer);
            printf("%d\n", bytes_received);
            bytes_received = recv(sock, get_response_buffer, 4096, 0);
            printf("%d\n", bytes_received);
            printf("\n----------RESPONSE-----------\n%s\n-----------------------------\n",get_response_buffer);
            // free(get_response_buffer);
        }

        #ifdef THREADS
            close(sock);
            pthread_exit(0);
        #endif

    }
    // exit(-1);
}

void remove_new_line(char *source)
{
    for(int i = 0;i < strlen(source); i++)
    {
        if(source[i] == '\n')
        {
            source[i] = ' ';
            break;
        }
    }
}

void print_usage(char *program_name)
{
    printf("Usage: %s <ip list filename> <directories list filename>\n", program_name);
    exit(0);
}

