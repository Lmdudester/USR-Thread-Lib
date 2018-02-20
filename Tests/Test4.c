#include <sys/types.h>
#include <stdio.h>
#include "../my_pthread_t.h"

pthread_mutex_t lock;
int sum;

void *add2(void *param) {
	printf("In the add method #2\n");

	pthread_mutex_lock(&lock);
	int i;
	for (i = 0; i < 10000000; i++) {
		sum = sum + 1;
	}
	pthread_mutex_unlock(&lock);

	printf("sum #2:%d\n",sum);

	printf("exited #2\n");

	pthread_exit(NULL);
	return NULL;
}

void *add1(void *param) {
	printf("In the add method #1\n");

	pthread_mutex_lock(&lock);
	int i;
	for (i = 0; i < 10000000; i++) {
		sum = sum + 1;
	}
	pthread_mutex_unlock(&lock);

	printf("sum #1:%d\n",sum);

	printf("exited #1\n");

	pthread_exit(NULL);
	return NULL;
}

void main(int argc, char ** argv){
	pthread_t tid1, tid2;

	pthread_mutex_init(&lock, NULL);

	printf("Starting\n");
	// void * (*ptr1)(void *) = add1;
	// void * (*ptr2)(void *) = add2;

	pthread_create(&tid1, NULL, add1, NULL);
	pthread_create(&tid2, NULL, add2, NULL);

	void *ret;
	pthread_join(tid1, &ret);
	pthread_join(tid2, &ret);

	pthread_mutex_destroy(&lock);

	printf("Ended, %d\n",sum);
}

/* Needs to print out (or some variation of)
   Starting
   In the add method #1
   In the add method #2
   sum #1:m
   exited #1
   sum #2:20000000
   exited #2
   Ended, 20000000
   */
