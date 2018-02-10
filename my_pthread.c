// File:	my_pthread.c
// Author:	Yujie REN
// Date:	09/23/2017

// name: 							Liam Davies,	Kevin Lee
// username of iLab: 	lmd312,				kjl156
// iLab Server: factory

#include "my_pthread_t.h"

/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg) {
	// First time being called, store main's current context
	if(main == NULL){
		main = malloc(sizeof(tcb));

		//Set defaults
		(*main).tID = __sync_fetch_and_add(&idCount, 1); //Fetch and increment idCounter atomically
		gettimeofday(&(*main).start, NULL);
		(*main).stat = P_WORKING;
		(*main).secQ = I_QUANTA;

		//Create ucontext
		getcontext(&(*main).ctxt);
	}

	// Reguardless, create new thread and add to running list
	tcb *newThread = malloc(sizeof(tcb));

	(*newThread).tID = __sync_fetch_and_add(&idCount, 1);
	gettimeofday(&(*main).start,NULL);
	(*newThread).stat = P_NEW;
	(*newThread).secQ = I_QUANTA;

	//Create ucontext

	return 0;
};

/* give CPU pocession to other user level threads voluntarily */
int my_pthread_yield() {
	return 0;
};

/* terminate a thread */
void my_pthread_exit(void *value_ptr) {
	// use swapcontext to the main <function>?
	// free the exited thread
};

/* wait for thread termination */
int my_pthread_join(my_pthread_t thread, void **value_ptr) {
	return 0;
};

//------------------------------------------------------------------------------------------------

/* initial the mutex lock */
int my_pthread_mutex_init(my_pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr) {
	return 0;
};

/* aquire the mutex lock */
int my_pthread_mutex_lock(my_pthread_mutex_t *mutex) {
	return 0;
};

/* release the mutex lock */
int my_pthread_mutex_unlock(my_pthread_mutex_t *mutex) {
	return 0;
};

/* destroy the mutex */
int my_pthread_mutex_destroy(my_pthread_mutex_t *mutex) {
	return 0;
};
