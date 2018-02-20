#include <sys/types.h>
#include <stdio.h>
#include "../my_pthread_t.h"
#include <unistd.h>

void * f1(void * i) {
	int * iptr = (int *)i;
	nanosleep(25000);
	pthread_exit(NULL);
}

void main(int argc, char ** argv) {
	pthread_t t1;
	void * (*f1ptr)(void *) = f1;

	int i1 = 0;

	pthread_create(&t1, NULL, f1ptr, &i1);

	void * ret;

	pthread_join(t1, &ret);

	printf("Complete.\n");
	printf("i1: %d\n", i1);
}
