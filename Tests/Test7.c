#include <sys/types.h>
#include <stdio.h>
#include "../my_pthread_t.h"

int data = 0;
int limit = 1000;
my_pthread_mutex_t lock;

void *print(void *param) {
	printf("Thread Num - %d\n", *(int *)param);
	int x = 0;
	my_pthread_mutex_lock(&lock);
	for (x = 0; x < limit; x++) {
		data++;
	}
	my_pthread_mutex_unlock(&lock);

	my_pthread_exit(NULL);
	return NULL;
}

void main(int argc, char ** argv) {
	my_pthread_t tid0, tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8, tid9, tid10, tid11, tid12, tid13;

	// my_pthread_mutex_init(&lock, NULL);

	my_pthread_create(&tid0, NULL, print, &data);
	my_pthread_create(&tid1, NULL, print, &data);
	my_pthread_create(&tid2, NULL, print, &data);
	my_pthread_create(&tid3, NULL, print, &data);
	my_pthread_create(&tid4, NULL, print, &data);
	my_pthread_create(&tid5, NULL, print, &data);
	my_pthread_create(&tid6, NULL, print, &data);
	my_pthread_create(&tid7, NULL, print, &data);
	my_pthread_create(&tid8, NULL, print, &data);
	my_pthread_create(&tid9, NULL, print, &data);
	my_pthread_create(&tid10, NULL, print, &data);
	my_pthread_create(&tid11, NULL, print, &data);
	my_pthread_create(&tid12, NULL, print, &data);
	my_pthread_create(&tid13, NULL, print, &data);

	void * ret;

	my_pthread_join(tid0, &ret);
	my_pthread_join(tid1, &ret);
	my_pthread_join(tid2, &ret);
	my_pthread_join(tid3, &ret);
	my_pthread_join(tid4, &ret);
	my_pthread_join(tid5, &ret);
	my_pthread_join(tid6, &ret);
	my_pthread_join(tid7, &ret);
	my_pthread_join(tid8, &ret);
	my_pthread_join(tid9, &ret);
	my_pthread_join(tid10, &ret);
	my_pthread_join(tid11, &ret);
	my_pthread_join(tid12, &ret);
	my_pthread_join(tid13, &ret);

	my_pthread_mutex_destroy(&lock);

	printf("Can you hear me?\n");
}

