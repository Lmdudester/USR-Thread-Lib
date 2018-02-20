#include <sys/types.h>
#include <stdio.h>
#include "../my_pthread_t.h"

/* TEST2 tests the following:
 * - argument passing
 * - basic locks
 */
typedef struct largerData {
	int d1;
	int d2;
	int d3;
	pthread_mutex_t m;
} ldata;

void * f1(void * i){
	printf("f1 start.\n");
	ldata * d = i;

	pthread_yield();

	pthread_mutex_lock(&((*d).m));
	pthread_yield();
	pthread_yield();

	pthread_yield();

	pthread_mutex_unlock(&((*d).m));

	printf("f1 end.\n");
	pthread_exit(NULL);
	return NULL;
}

void * f2(void * i){
	printf("f2 start.\n");
	ldata * d = i;
	pthread_mutex_lock(&((*d).m));

	pthread_yield();

	pthread_yield();

	pthread_mutex_unlock(&((*d).m));

	printf("f2 end.\n");
	pthread_exit(NULL);
	return NULL;
}

void * f3(void * i){
	printf("f3 start.\n");
	ldata * d = i;

	pthread_mutex_lock(&((*d).m));

	pthread_mutex_unlock(&((*d).m));

	printf("f3 end.\n");
	pthread_exit(NULL);
	return NULL;
}

void main(int argc, char ** argv){
	printf("main start.\n");
	my_pthread_t t1, t2, t3;
	void * (*f1ptr)(void *) = f1;
	void * (*f2ptr)(void *) = f2;
	void * (*f3ptr)(void *) = f3;

	ldata * data = malloc(sizeof(ldata));
	pthread_mutex_init(&((*data).m), NULL);

	(*data).d1 = 27;

	// Make sure no crash on double lock/unlock - w/ 1 thread
	pthread_mutex_lock(&((*data).m));
	if(pthread_mutex_lock(&((*data).m)) == 0){
		printf("ERROR: Mutex double lock - 1 thread - no error.\n");
	}

	pthread_mutex_unlock(&((*data).m));

	pthread_create(&t1, NULL, f1ptr, data);
	pthread_create(&t2, NULL, f2ptr, data);
	pthread_yield();

	pthread_yield();

	pthread_yield();

	pthread_create(&t3, NULL, f3ptr, data);

	void * ret;
	pthread_join(t1, &ret);

	pthread_join(t2, &ret);

	pthread_join(t3, &ret);

	printf("main end.\n");
}
