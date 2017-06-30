void fatal(char * message) {
	char error_message[100];

	strcpy(error_message, "[!!] Fatal Error ");
	strncat(error_message, message, 83);
	perror(error_message);
	exit(-1);
}

// An error-check malloc() wrapper function
void *ec_malloc(unsigned int size) {
	void *ptr;
	ptr = malloc(size);
	if (ptr == NULL) {
		fatal("in ec_malloc() on memory allocation");
	}
	return ptr;
}




// Dumps raw memory in hex byte and printable split format
void dump(const unsigned char *data_buffer, const unsigned int length) {
	unsigned char byte;
	unsigned int i, j;
	for(i=0; i < length; i++) {
		byte = data_buffer[i];
		printf("%02x ", data_buffer[i]); // Display byte in hex.
		if(((i%16)==15) || (i==length-1)) {
			for(j=0; j < 15-(i%16); j++) {
				printf(" ");
				printf("| ");
				for(j=(i-(i%16)); j <= i; j++) { // Display printable bytes from line.
					byte = data_buffer[j];
					if((byte > 31) && (byte < 127)) {// Outside printable char range
						printf("%c", byte);
					} else {
						printf(".");
					}
				}
			}
		printf("\n"); // End of the dump line (each line is 16 bytes)
		} // End if
	} // End for
}

/* This function accepts a socket FD and a ptr to the null terminated
* string to send. The function will make sure all the bytes of the
* string are sent. Returns 1 on success and 0 on failure.
*/

int send_string(int sockfd, unsigned char *buffer) {
	int sent_bytes, bytes_to_send;
	bytes_to_send = strlen(buffer);
	while(bytes_to_send > 0) {
		sent_bytes = send(sockfd, buffer, bytes_to_send, 0);
		if(sent_bytes == -1) {
			return 0;
		}

	bytes_to_send -= sent_bytes;
	buffer += sent_bytes;
	}
	return 1; // on sucess
}

/* This function accepts a socket FD and a ptr to a destination
* buffer. It will receive from the socket until the EOL byte
* sequence in seen. The EOL bytes are read from the socket, but
* the destination buffer is terminated before these bytes.
* Returns the size of the read line (without EOL bytes).
*/

int recv_line(int sockfd, unsigned char *dest_buffer) {
#define EOL "\r\n" // end-of-line byte sequence
#define EOL_SIZE 2
	unsigned char *ptr;
	int eol_matched = 0;
	ptr = dest_buffer;
	while (recv(sockfd, ptr, 1, 0) == 1) { // Read a single byte.
		/* code */
		if (*ptr == EOL[eol_matched]) { // Does this byte match terminator?
			/* code */
			eol_matched++;
			if(eol_matched == EOL_SIZE) { // If all bytes match terminator,
				*(ptr + 1 - EOL_SIZE) = '\0'; // terminate the string.
				return strlen(dest_buffer); // Return bytes received
			}
		} else {
			eol_matched = 0;
		}
		ptr++; // Increment the pointer to the next byte.
	}
	return 0; // Didn't find the end-of-line characters.

}
