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


#define SLEEP
#define CONN
#define DEBUG
#define BUF_LEN 1024
// #define FIXQA
#define THREADS
// #define ARGS

/* Funtion prototypes */
void die_with_error(char *); // error function
FILE *open_file(char *file); // read ip and uri lists
void *connect_to(void* ip); // Creates the socket sends the request and checks status response
void reverse_dns_lookup(char *ip); // reverse dns
void write_it(int status,char *host, char *get_request_buffer, char *get_response_buffer);
void remove_new_line(char *source); // remove the new-line character at the end of a string
void print_usage(char *program_name); // Print run program usage
// --------------------//

// ----- Headers ----- //
char request_headers_one[1024] = "HEAD ";
char request_headers_two[250] = "HTTP/1.1\r\nHost: ";
char request_headers_three[200] = "\r\nuser-Agent: TotallynotaBotMozilla/5.0 (X11; Linux x86_64; rv:12.0) Gecko/20100101 Firefox/12.0\r\n\r\n";


// --------------------//

// Connection: close
int main(int argc, char *argv[])
{
    #ifdef THREADS
    static int i = 1;
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
            printf("Creating a thread for %s...", read_string);
            sleep(5);
            pthread_attr_init(&attr);
            pthread_create(&threads[i], &attr, connect_to, (void*) &read_string);
            i++;
        #else
            // sleep(5);
            connect_to(read_string);
        #endif
    }
    fclose(ptr);
    #ifdef THREADSjoin
    for(int j = 1; j < i; j++)
    {
        printf("Joinging %d...\n",j );
        pthread_join(threads[j],NULL);
    }
    #endif
    pthread_join(threads[1],NULL);
    sleep(5);
    pthread_join(threads[2],NULL);
   return 0;
}

void *connect_to(void* ip)
{
    char get_request_buffer[BUF_LEN],get_response_buffer[1024]; // Buffers for request and response
    // char *get_response_buffer;
    // get_response_buffer = (char *) malloc(1024*1024); // 100mb

    char *hostname = ip;

    in_addr_t in_addr;
    int request_len, sock, bytes_received;
    ssize_t bytes_to_send, line;
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    //*     Loop directories    *//
    FILE *ptr = open_file("dirs.txt");
    char read_string[100];

    while(fgets(read_string, sizeof(read_string), ptr) != NULL)
    {
        //beej//
        printf("host %s\n",hostname );
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC; // use AF_INET6 to force IPv6
        hints.ai_socktype = SOCK_STREAM;

        if ((rv = getaddrinfo(hostname, "http", &hints, &servinfo)) != 0)
        {
            die_with_error("getaddrinfo");
        }

        // loop through all the results and connect to the first we can
        for(p = servinfo; p != NULL; p = p->ai_next)
        {
            if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            {
                perror("socket");
                continue;
            }

            if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
            {
                perror("connect");
                close(sockfd);
                continue;
            }

            break; // if we get here, we must have connected successfully
        }

        if (p == NULL)
        {
            // looped off the end of the list with no connection
            fprintf(stderr, "failed to connect\n");
            exit(2);
        }

        /* ssize_t write(int fd, const void *buf, size_t count); */
        remove_new_line(read_string); // sin
        remove_new_line(hostname);
        strcpy(request_headers_two+16, (char *) hostname); // add hostname "HTTP/1.1\r\nHost: %s"
        strcpy(request_headers_one+5, (char *) read_string); // add the readstring with '\n' removed HEAD /DIR HTTP/1.1
        // printf("+18%s\n", request_headers_two+17);
        strcat(request_headers_one, request_headers_two); // join the rest of the request to the end
        strcat(request_headers_one, request_headers_three); // join the rest of the request to the end


        bytes_to_send = 0;

        printf("[URI]\t%s\n", read_string);
        printf("\n-----------REQUEST-------------\n%s--------------------------------\n",request_headers_one );
        printf("bytes_to_send %ld\n", bytes_to_send);
        printf("request_headers_one %ld\n", sizeof(request_headers_one));
        #ifdef SLEEP
        sleep(5);
        #endif
        #ifndef FIXQA
        // while(bytes_to_send < sizeof(request_headers_one))
        // {
        //     puts("\n[DEBUG]\tSending...\n");
        //     if((line = write(sock, request_headers_one, sizeof(request_headers_one))) == -1)
        //         die_with_error("in write");
        //     bytes_to_send += line;
        // }

        while(bytes_to_send < sizeof(request_headers_one))
        {
            puts("\n[DEBUG]\tSending...\n");
            if((line = send(sockfd, request_headers_one, sizeof(request_headers_one), 0)) == -1)
                die_with_error("in write");
            bytes_to_send += line;
            printf("%ld\n",bytes_to_send );
        }

        puts("[DEBUG]\treceiving...\n");
        if(bytes_received = read(sockfd, get_response_buffer, 1024) == -1)
            die_with_error("reading from socket");
        else if(bytes_received == 0)
            printf("Closed\n" );

        printf("\n----------RESPONSE-----------\n%s\n-----------------------------\n",get_response_buffer);
        #ifdef SLEEP
        sleep(5);
        #endif
        // while(bytes_received > 1)
        // {
            // int fd;
        // printf("%d\n", bytes_received);
        // write(sock, get_response_buffer, 1024);
        // printf("\n----------RESPONSE-----------\n%s\n-----------------------------\n",get_response_buffer);
        if(strstr(get_response_buffer, "HTTP/1.1 404 Not Found"))
        {
            // printf("[404 NOT FOUND]\tGET %s %s\n",inet_ntoa(*(p->ai_addr)), read_string);
            printf("404\n" );
            write_it(404,hostname, request_headers_one, get_response_buffer);
            #ifdef SLEEP
            sleep(5);
            #endif
            // break;
        }
        else if(strstr(get_response_buffer, "HTTP/1.1 302 Found"))
        {
            // printf("[302 FOUND]\tGET %s %s\n", inet_ntoa(p->ai_addr), read_string);
            printf("[302 FOUND]\n");
            write_it(302,hostname, request_headers_one, get_response_buffer);
            #ifdef SLEEP
            sleep(5);
            #endif
            // break;
        }
        else if(strstr(get_response_buffer, "HTTP/1.1 200 OK"))
        {
            // printf("[200 OK]\t GET %s %s\n", inet_ntoa(p->ai_addr), read_string);
            printf("[200 OK]\t \n");
            write_it(200,hostname, request_headers_one, get_response_buffer);
            #ifdef SLEEP
            sleep(5);
            #endif
            // break;
        }
        else
        {
            puts("not OK");
            // exit(-1);
            // break;
        }
        printf("[DEBUG] Resetting\n");
        bzero(get_response_buffer,1024);
        bzero(get_request_buffer, BUF_LEN);
        freeaddrinfo(servinfo); // all done with this structure
        #endif
        #ifdef SLEEP
        sleep(5);
        #endif
        puts("[DEBUG] closing socket...");
        close(sockfd);

    }
    #ifdef THREADS
           pthread_exit(0);
    #endif
    puts("[DEBUG] end of connect_to");
    // exit(-1);
}


void write_it(int status, char *host, char *get_request_buffer, char *get_response_buffer)
{
    int fd;
    char filename[20];

    if(status == 404)
        strcpy(filename, "404.txt");
    else if(status == 302)
        strcpy(filename, "302.txt");

    else if(status == 200)
        strcpy(filename, "200.txt");
    else
        strcpy(filename, "notok.txt");
    printf("In writeit %s\n", get_request_buffer );
        // probably write a structure to be easier to writ estuff to the file //
    fd = open(filename, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    if(fd == -1)
        die_with_error("opening file");
    if(write(fd, host, strlen(host)) == -1) // host
        die_with_error("writing to file");
    if(write(fd, get_request_buffer, strlen(get_request_buffer)) == -1) // request
        die_with_error("writing to file");
    if(write(fd, get_response_buffer, strlen(get_response_buffer)) == -1) // response
        die_with_error("writing to file");
    if(close(fd) == -1)
        die_with_error("closing file");

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
