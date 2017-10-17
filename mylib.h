#define BUF_LEN 1024

FILE *open_file(char *file)
{
    char *filename = file; // File to open as char pointer
    FILE *file_ptr = NULL; // File type pointer
    // Opening the file error
    if((file_ptr = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "error opening %s\n", filename);
        exit(-1); // Die with error
    }
    return file_ptr;
}

void die_with_error(char *message) {
	char error_message[100];
	perror(error_message);
	exit(-1);
}

void reverse_dns_lookup(char *ip)
{
    char hostname[BUF_LEN];
    char service[100];
    struct sockaddr_in socketaddress;
    #ifdef DEBUG
        printf("%d\n", *(int *)ip); // void * to int *(int *)
    #endif

    socketaddress.sin_family = AF_INET;
    socketaddress.sin_port = htons(80);
    socketaddress.sin_addr.s_addr = inet_addr(ip);
    // printf("%d\n", socketaddress.sin_addr.s_addr);

    int result = getnameinfo((struct sockaddr *) &socketaddress, sizeof(socketaddress), hostname, sizeof(hostname), service, sizeof(service), 0);

    printf("%s\n", hostname);
}
