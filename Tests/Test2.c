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
	my_pthread_mutex_t m;
} ldata;

void * f1(void * i){
	ldata * d = i;

	my_pthread_yield();

	my_pthread_mutex_lock(&((*d).m));
	my_pthread_yield();
	my_pthread_yield();

	my_pthread_yield();

	my_pthread_mutex_unlock(&((*d).m));

	my_pthread_exit(NULL);
	return NULL;
}

void * f2(void * i){
	ldata * d = i;
	my_pthread_mutex_lock(&((*d).m));

	my_pthread_yield();

	my_pthread_yield();

	my_pthread_mutex_unlock(&((*d).m));

	my_pthread_exit(NULL);
	return NULL;
}

void * f3(void * i){
	ldata * d = i;

	my_pthread_mutex_lock(&((*d).m));

	my_pthread_mutex_unlock(&((*d).m));

	my_pthread_exit(NULL);
	return NULL;
}

void main(int argc, char ** argv){
	my_pthread_t t1, t2, t3;
	void * (*f1ptr)(void *) = f1;
	void * (*f2ptr)(void *) = f2;
	void * (*f3ptr)(void *) = f3;

	ldata * data = malloc(sizeof(ldata));
	my_pthread_mutex_init(&((*data).m), NULL);

	(*data).d1 = 27;

	// Make sure no crash on double lock/unlock - w/ 1 thread
	my_pthread_mutex_lock(&((*data).m));
	if(my_pthread_mutex_lock(&((*data).m)) == 0){
		printf("ERROR: Mutex double lock - 1 thread - no error.\n");
	}

	my_pthread_mutex_unlock(&((*data).m));

	my_pthread_create(&t1, NULL, f1ptr, data);
	my_pthread_create(&t2, NULL, f2ptr, data);
	my_pthread_yield();

	my_pthread_yield();

	my_pthread_yield();

	my_pthread_create(&t3, NULL, f3ptr, data);

	void * ret;
	my_pthread_join(t1, &ret);

	my_pthread_join(t2, &ret);

	my_pthread_join(t3, &ret);

}

