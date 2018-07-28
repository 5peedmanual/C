#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


void daemonize(const char *cmd);

int main(void)
{
	daemonize("A");
	sleep(10);
}

void daemonize(const char *cmd)
{
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit r_lim;
	struct sigaction sig_act;

	umask(0);

	if (getrlimit(RLIMIT_NOFILE, &r_lim) < 0) {
		perror("can't get file limit");
		exit(-1);
	}

	// become a session leader to lose controlling TTY
	if ((pid = fork()) < 0) {
		perror("can't fork");
		exit(-1);
	} else if (pid != 0) { // parent
		exit(0);
	}

	setsid(); // create a new session

	// Ensure future opens wont allocate controlling TTYs
	sig_act.sa_handler = SIG_IGN;
	sigemptyset(&sig_act.sa_mask);
	sig_act.sa_flags = 0;

	if (sigaction(SIGHUP, &sig_act, NULL) < 0) {
		perror("can't ignore SIGHUP");
		exit(-1);
	}
	if ((pid = fork()) < 0) {
		perror("can't fork");
		exit(-1);
	} else if (pid != 0) { // parent
		exit(0);
	}

	// change the current working directory to the root 
	// so we won't prevent fs from being unmounted
	if (chdir("/") < 0) {
		perror("can't cd");
		exit(-1);
	}

	// close all fds
	if (r_lim.rlim_max == RLIM_INFINITY)
		r_lim.rlim_max = 1024;
	for (i= 0; i < r_lim.rlim_max; i++)
		close(i);

	// attach fds 0, 1 and 2 to /dev/null
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0); // duplicate file descriptor fd0
	fd2 = dup(0);

	// initialize the log file
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if ( fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}
}

