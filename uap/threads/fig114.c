#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct foo {
	int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp)
{
	printf("%s", s);
	printf("\tstructure at 0x%lx\n", (unsigned long) fp);
	printf("\tfoo.a = %d\n", fp->a);
	printf("\tfoo.b = %d\n", fp->b);
	printf("\tfoo.c = %d\n", fp->c);
	printf("\tfoo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg)
{
	struct foo foo = {1, 2, 3, 4};
	printfoo("thread 1:\n", &foo);
	pthread_exit((void *) &foo); ////
}

void *thr_fn2(void *arg)
{
	printf("thread 2: ID is %lu\n", (unsigned long) pthread_self());
	pthread_exit((void *) 0);
}


int err_exit(const char *s)
{
	perror(s);
	exit(-1);
}

int main(void)
{
	int err;
	pthread_t tid1, tid2;
	struct foo *fp;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
		err_exit("creating thread 1");
	err = pthread_join(tid1, (void *) &fp);
	if (err != 0)
		err_exit("joining thread 1");
	sleep(1);
	puts("parent starting second thread");
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
		err_exit("creating thread 2");
	sleep(1);
	printfoo("parent:\n", fp);
	exit(0);
}
