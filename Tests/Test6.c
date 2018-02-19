#include <sys/types.h>
#include <stdio.h>
#include "../my_pthread_t.h"

my_pthread_mutex_t lock;
int sum = 0;

void *add2(void *param) {
	printf("In the add method 2\n");

	my_pthread_mutex_lock(&lock);
	sum += *(int *)param;
	my_pthread_mutex_unlock(&lock);

	printf("sum #2:%d\n", sum);
	printf("exited #2\n");

	my_pthread_exit(NULL);
	return NULL;
}

void *add1(void *param) {
	printf("In the add method 1\n");

	my_pthread_mutex_lock(&lock);
	sum += *(int *)param;
	my_pthread_mutex_unlock(&lock);

	printf("sum #1:%d\n", sum);
	printf("exited #1\n");

	my_pthread_exit(NULL);
	return NULL;
}

void main(int argc, char ** argv) {
	my_pthread_t tid1, tid2, tid3;

	my_pthread_mutex_init(&lock, NULL);

	printf("Starting\n");

	int x = 4;

	my_pthread_create(&tid1, NULL, add1, &x);
	my_pthread_create(&tid2, NULL, add2, &x);

	void *ret;
	my_pthread_join(tid1, &ret);
	my_pthread_join(tid2, &ret);
	printf("Here?");

	my_pthread_mutex_destroy(&lock);

	printf("Done...\n");
	printf("Ended, %d\n", sum);
}
