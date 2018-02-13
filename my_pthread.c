// File:	my_pthread.c
// Author:	Yujie REN
// Date:	09/23/2017

// name: 							Liam Davies,	Kevin Lee
// username of iLab: 	lmd312,				kjl156
// iLab Server: factory

#include "my_pthread_t.h"

// Queues
tcbNode * q1 = NULL;
tcbNode * q2 = NULL;
tcbNode * q3 = NULL;

// Linked Lists
tcbNode * completed = NULL;

// The currently running context
tcbNode * currCtxt = NULL;

// For threadID generation
my_pthread_t idCount = 1;


/* HELPER FUNCTIONS */

/* __enqueue()__
 *	Adds the newly created node to the parameter queue.
 *	Args:
 *		- tcbNode ** queue - a pointer to q1, q2 or q3 (use &q1, &q2, &q3)
 *		- tcbNode * newNode - the node to be inserted
 *	Returns:
 *		- N/A
 * NOTE: Assumes all newNode(s) have had their next ptr set to NULL
 */
void enqueue(tcbNode ** queue, tcbNode * newNode){
	if(*queue == NULL) { // Its empty
		(*queue) = newNode;
		return;
	}

	// 1-More Items
	tcbNode * ptr = (*queue);
	while((*ptr).next != NULL) {
		ptr = (*ptr).next;
	}
	(*ptr).next = newNode;
}

 /* __dequeue()__
  *	Returns the top tcbNode from the parameter queue.
  *	Args:
  *		- tcbNode ** queue - a pointer to q1, q2 or q3 (use &q1, &q2, &q3)
  *	Returns:
  *		- tcbNode * - the top tcbNode
	* NOTE: To meet NULL requirement of enqueue, returned node has a next of NULL
  */
tcbNode * dequeue(tcbNode ** queue){
	if(*queue == NULL) // Its empty
		return NULL;

	tcbNode * ret = *queue;
	*queue = (**queue).next;
	(*ret).next = NULL;
	return ret;
}


/* SCHEDULER FUNCTIONS */

void scheduler(int signum){
	// Set up sigmask

	// Decide which queue to send current cTxt to

	// Maintainance + Choose next ctxt

	// Reset Timer

	// Swap contexts
}


/* MAIN FUNCTIONS */

/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg) {
	if(currCtxt == NULL) { // First time any my_pthread function has been evoked (so store main)
		currCtxt = malloc(sizeof(tcbNode));
		if(currCtxt == NULL){
			//ERROR
			return -1;
		}
		(*currCtxt).next = NULL;

		// Set defaults
		(*currCtxt).data.tID = __sync_fetch_and_add(&idCount, 1); //Fetch and increment idCounter atomically
		(*currCtxt).data.stat = P_RUN;
		(*currCtxt).data.qNum = 1;
		(*currCtxt).data.ret = NULL;
		(*currCtxt).data.w_mutex = NULL;
		(*currCtxt).data.w_tID = 0;

		// Create ucontext
		getcontext(&(*currCtxt).data.ctxt);
	}

	// Reguardless, create new thread and add to running list
	tcbNode * newNode = malloc(sizeof(tcbNode));
	if(newNode == NULL){
		//ERROR
		return -1;
	}
	(*newNode).next = NULL;

	// Set defaults
	(*newNode).data.tID = __sync_fetch_and_add(&idCount, 1); //Fetch and increment idCounter atomically
	(*newNode).data.stat = P_RUN;
	(*newNode).data.qNum = 1;
	(*newNode).data.ret = NULL;
	(*newNode).data.w_mutex = NULL;
	(*newNode).data.w_tID = 0;

	//Create ucontext
	getcontext(&(*newNode).data.ctxt);
	(*newNode).data.ctxt.uc_link = 0;
 	(*newNode).data.ctxt.uc_stack.ss_sp = malloc(STKSZE);
 	(*newNode).data.ctxt.uc_stack.ss_size = STKSZE;
 	(*newNode).data.ctxt.uc_stack.ss_flags = 0;

	if((*newNode).data.ctxt.uc_stack.ss_sp == NULL){
		//ERROR
		return -1;
	}

	makecontext(&(*newNode).data.ctxt, (void *) function, 1, arg);

	// Place in queue
	enqueue(&q1, newNode);

	return 0;
};

/* give CPU pocession to other user level threads voluntarily */
int my_pthread_yield() {
	return 0;
};

/* terminate a thread */
void my_pthread_exit(void *value_ptr) {
	return;
};

/* wait for thread termination */
int my_pthread_join(my_pthread_t thread, void **value_ptr) {
	//Here, you'll free the ss_sp within uc_stack
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
