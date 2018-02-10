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
		(*main).tID = idCount;
		gettimeofday(&(*main).start, NULL);
		(*main).stat = P_WORKING;
		(*main).secQ = 25;

		//Create ucontext


		idCount ++; //increment id generation int
	}

	// getcontext(&(thread->ctxt)); //wait, nm... my_pthread_create is a uint
	// do uc_stack.ss_sp  uc_stack.ss_size uc_stack.uc_link
	// than makecontext()
	return 0;
};

/* give CPU pocession to other user level threads voluntarily */
int my_pthread_yield() {
	// Just set the status to yield (3) <and while loop for block>??
	return 0;
};

/* terminate a thread */
void my_pthread_exit(void *value_ptr) {
	// use swapcontext to the main <function>?
	// free the exited thread
};

/* wait for thread termination */
int my_pthread_join(my_pthread_t thread, void **value_ptr) {
	// Do <swapcontext???>
	// free the past joined thread
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
