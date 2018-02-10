// File:	my_pthread.c
// Author:	Yujie REN
// Date:	09/23/2017

// name: 							Liam Davies,	Kevin Lee
// username of iLab: 	lmd312,				kjl156
// iLab Server: factory

#include "my_pthread_t.h"

// Data for main
tcbNode * mainTCB = NULL;

// For threadID generation
my_pthread_t idCount = 0;

tcbNode * currCtxt = NULL;

/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg) {
	// First time being called, store main's current context
	if(mainTCB == NULL){
		mainTCB = malloc(sizeof(tcbNode));
		if(mainTCB == NULL){
			//ERROR
		}

		//Set defaults
		(*mainTCB).data.tID = __sync_fetch_and_add(&idCount, 1); //Fetch and increment idCounter atomically
		gettimeofday(&(*mainTCB).data.start, NULL);
		(*mainTCB).data.stat = P_WORKING;
		(*mainTCB).data.secQ = 25;
		(*mainTCB).data.ret = NULL;

		//Create ucontext
		getcontext(&(*mainTCB).data.ctxt);

		//Set default currCtxt
		currCtxt = mainTCB;
	}

	// Reguardless, create new thread and add to running list
	tcbNode * newNode = malloc(sizeof(tcbNode));

	(*newNode).data.tID = __sync_fetch_and_add(&idCount, 1);
	gettimeofday(&(*newNode).data.start,NULL);
	(*newNode).data.stat = P_NEW;
	(*newNode).data.secQ = 25;
	(*newNode).data.ret = NULL;

	//Create ucontext
	getcontext(&(*newNode).data.ctxt);
	(*newNode).data.ctxt.uc_link = 0;
 	(*newNode).data.ctxt.uc_stack.ss_sp = malloc(STKSZE);
 	(*newNode).data.ctxt.uc_stack.ss_size = STKSZE;
 	(*newNode).data.ctxt.uc_stack.ss_flags = 0;

	if((*newNode).data.ctxt.uc_stack.ss_sp == NULL){
		//ERROR
	}

	makecontext(&(*newNode).data.ctxt, (void *) function, 1, arg);

	// Place in queue
	(*newNode).next = ready;
	ready = newNode;

	(*thread) = (*newNode).data.tID;

	return 0;
};

/* give CPU pocession to other user level threads voluntarily */
int my_pthread_yield() {
	if (currCtxt == NULL) {		//Not there
		printf("Didn't initalize anything, thus cannot yield");
		return;
	}

	(*currCtxt).data.stat = P_YIELDING;
	return 0;
};

/* terminate a thread */
void my_pthread_exit(void *value_ptr) {
	if (currCtxt == NULL) {		//Not there
		printf("Didn't initalize anything, thus cannot exit");
		return;
	}

	(*currCtxt).data.stat = P_TERMINATED;
	(*currCtxt).data.ret = value_ptr;

	(*currCtxt).next = finished;
	finished = currCtxt;
};

/* wait for thread termination */
int my_pthread_join(my_pthread_t thread, void **value_ptr) {
	//Here, you'll free the ss_sp within uc_stack
	if (currCtxt == NULL) {		//Not there
		printf("Didn't initalize anything, thus cannot join");
		return;
	}

	(*currCtxt).data.ret = value_ptr;
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
