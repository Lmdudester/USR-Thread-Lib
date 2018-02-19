#include <sys/types.h>
#include <stdio.h>
#include "../my_pthread_t.h"

void *simplePrint(void *param) {
	printf("HERE\n");

	my_pthread_exit(NULL);
	return NULL;
}

void main(int argc, char ** argv){
	my_pthread_t tid1, tid2;
	printf("Starting\n");
	void * (*spPtr)(void *) = simplePrint;

	my_pthread_create(&tid1, NULL, spPtr, NULL);
	my_pthread_create(&tid2, NULL, spPtr, NULL);

	//Wait for both threads to finish:3
	void *ret;
	my_pthread_join(tid1, &ret);
	my_pthread_join(tid2, &ret);

	printf("Ending\n");
}
