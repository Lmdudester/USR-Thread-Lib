#include <sys/types.h>
#include <stdio.h>
#include "../my_pthread_t.h"

int data = 0;
int limit = 1000;
pthread_mutex_t lock;

void *print(void *param) {
	printf("Thread Num - %d\n", *(int *)param);
	int x = 0;
	pthread_mutex_lock(&lock);
	for (x = 0; x < limit; x++) {
		data++;
	}
	pthread_mutex_unlock(&lock);

	pthread_exit(NULL);
	return NULL;
}

void main(int argc, char ** argv) {
	pthread_t tid0, tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8, tid9, tid10, tid11, tid12, tid13;

	// pthread_mutex_init(&lock, NULL);

	pthread_create(&tid0, NULL, print, &data);
	pthread_create(&tid1, NULL, print, &data);
	pthread_create(&tid2, NULL, print, &data);
	pthread_create(&tid3, NULL, print, &data);
	pthread_create(&tid4, NULL, print, &data);
	pthread_create(&tid5, NULL, print, &data);
	pthread_create(&tid6, NULL, print, &data);
	pthread_create(&tid7, NULL, print, &data);
	pthread_create(&tid8, NULL, print, &data);
	pthread_create(&tid9, NULL, print, &data);
	pthread_create(&tid10, NULL, print, &data);
	pthread_create(&tid11, NULL, print, &data);
	pthread_create(&tid12, NULL, print, &data);
	pthread_create(&tid13, NULL, print, &data);

	void * ret;

	pthread_join(tid0, &ret);
	pthread_join(tid1, &ret);
	pthread_join(tid2, &ret);
	pthread_join(tid3, &ret);
	pthread_join(tid4, &ret);
	pthread_join(tid5, &ret);
	pthread_join(tid6, &ret);
	pthread_join(tid7, &ret);
	pthread_join(tid8, &ret);
	pthread_join(tid9, &ret);
	pthread_join(tid10, &ret);
	pthread_join(tid11, &ret);
	pthread_join(tid12, &ret);
	pthread_join(tid13, &ret);

	pthread_mutex_destroy(&lock);

	printf("Can you hear me?\n");
}
