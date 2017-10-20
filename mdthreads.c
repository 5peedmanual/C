#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // manipulate fd
#include <sys/socket.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h> // close, write
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


static int i = 1;

int main(int argc, char *argv[])
{
    #ifdef THREADS
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

        #if (defined(DEBUG) && defined(THREADS))
            printf("[%d] Creating a thread for %s.\n", i, read_string);
        #endif
        #ifdef THREADS
            pthread_attr_init(&attr);
            // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
            pthread_create(&threads[i], &attr, connect_to, (void*) &read_string);
            puts("[DEBUG\tjoining threads");
            i++;

        #else
            connect_to(read_string);
        #endif
    }
    // for(int j = 0; j < 2; j++)
    // {
    //     printf("joining thread %d\n", j);
    //     pthread_join(threads[j],NULL);
    // }


   return 0;
}

void *connect_to(void* ip)
{
    printf("in here\n");
    char get_request_buffer[BUF_LEN];/*,get_response_buffer[1024*1024*100]*/; // Buffers for request and response
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

    printf("[i] == %d Creating socket\n", i);
    // if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    //     die_with_error("creating socket");

    // memset(&hints, 0, sizeof hints); // Zero out the struct
    hostent = gethostbyname(ip);

    in_addr = inet_addr(inet_ntoa(*(struct in_addr*)ip));
    memset((char *) &server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = in_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    printf("[i] == %d Connecting socket\n", i);
    printf("[DEBUG]\tConnecting to %s port %d\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));
    if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        die_with_error("connecting");

    printf("[i] == %d opening dirfile\n", i);
    FILE *ptr = open_file("dirs.txt");
    char read_string[100];
    printf("before while\n");
    while(fgets(read_string, sizeof(read_string), ptr) != NULL)
    {
        remove_new_line(read_string); // sin
        strcpy(request_headers_one+4, (char *) read_string); // add the readstring with '\n' removed
        strcat(request_headers_one, request_headers_two); // join the rest of the request to the end
        printf("[URI]\t%s\n", read_string);
        printf("\n[i] %d %s\n",i,request_headers_one);

        puts("\n[DEBUG]\tSending...\n");
        puts("[DEBUG]\treceiving...\n");

    }

    puts("[DEBUG] closing socket...");
    close(sock);
    #ifdef THREADS
        pthread_exit(0);
    #endif

    puts("[DEBUG] end of connect_to");
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
