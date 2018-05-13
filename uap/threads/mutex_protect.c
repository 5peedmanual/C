#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* * Example of using a mutex to protect a data struct * */

struct foo {
	int f_count;
	pthread_mutex_t f_lock;
	int f_id;
}

struct foo *foo_alloc(int id)
{
	struct foo *fp;
	if ((fo = malloc(sizeof(struct foo))) != NULL) {
		fp->f_count = 1;
		fp->f_id = id;
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0) { // alocate the mutex dynamically
			free(fp);
			return(NULL);
		}
		// continue initialization
	}
	return(fp);
}

void foo_hold(struct foo *fp) // add reference to the object
{
	pthread_mutex_lock(&fp->f_lock); // lock
	fp->f_count++; // increment
	pthread_mutex_unlock(&fp->f_lock); // unlock
}

void foo_release(struct foo *fp) // release a reference to the object
{
	pthread_mutex_lock(&fp->f_lock);
	if (--fp->f_count == 0) { // last reference
		pthread_mutex_unlock(&fp->f_lock);	
		pthread_mutex_destroy(&fp->f_lock); // we must destroy the mutex before freeing the memory
		free(fp);
	} else {
		pthread_mutex_unlock(&fp->f_lock);
	}
}
