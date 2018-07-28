#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <inttypes.h>
#include <arpa/inet.h> // inet_addr
#include <pthread.h>
#include <unistd.h>


#include "../err_handling/error.h"
#include "interface/file_config.h"
#include "client.h"
// #include "cli.h"
#include "colors.h"

struct thread_foo_st {
        int             f_count; // reference count to ensura that we don't free
                                 // the memory before all threads
        pthread_mutex_t f_lock;
        int             f_id;
        int             fd;
};


static struct thread_foo_st *createconn_sock(struct thread_foo_st *fsp)
{
        puts("here");
        // printf("a : %s", fsp->a);
        #ifdef CONNECTION
            // int fd;
            struct sockaddr_in server_addr;
        #endif

        #ifdef CONNECTION
            // Create socket
            if((fsp->fd = socket(PF_INET, SOCK_STREAM,0)) == -1)
                error(FTL_SYS, "[!!][DEBUG][ERROR][createconn_sock] creating socket");

            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(PORT);
            server_addr.sin_addr.s_addr = 0;

                // server.sin_addr.s_addr = inet_addr("ip");

            if(connect(fsp->fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
                error(FTL_SYS, "[!!][DEBUG][ERROR][main] creating connection");

            printf(ANSI_COLOR_YELLOW "\n[+][DEBUG][main] Connection established.\n" ANSI_COLOR_RESET);
        #endif
        return(fsp);

}

void *thr1_input(void *foop)
{
        pthread_t tid;
        tid = pthread_self();
	printf("tid %lu (0x%lx)\n", (unsigned long) tid, (unsigned long) tid);
        puts("[DEBUG][thr1_input] ");
        while(1) {
                puts("[DEBUG][thr1_input] loop");
            #ifdef CONNECTION
                input(foop);
            #else
                input();
            #endif
        }
        puts("[DEBUG][thr1_input] exit");
        pthread_exit((void *) 0);
        // return((void *) 0);
}

// void *thr2_getdir(void)
// {
//         get_curr_dir();
// }



int main(void)
{
        int sock;
        int err;
        pthread_t tid;
        void *tret;
        open_file("textfiles/opening.txt"); // Print ascii
        createconn_sock(thrfoop); // pass pointer of struct
        err = pthread_create(&tid, NULL, thr1_input, (void *) &thrfoop);
        if (err != 0)
                error(FTL_SYS, "[!!][DEBUG][ERROR][main] creating thread");
        err = pthread_join(tid, &tret);
        if (err != 0)
                error(FTL_SYS, "[!!][DEBUG][ERROR][main] creating thread");
        else
                printf("[+][DEBUG][main] t1 exit status: %ld\n", (long) tret);
        puts("[DEBUG][main] exit");

        exit(0);
}
