# USR-Thread-Lib

Names: Liam Davies, Kevin Lee, Brian Ellsworth
NetIDs: lmd312, kjl156, bje40
ilab machine used for testing: factory.cs.rutgers.edu

A suite of test programs are provided in the Tests directory. They are labeled "Test#" where # is
an integer test number. These tests can be compiled by running the "make Test#" command. 
For example, "make Test12" will compile Test12. 

Make all will compile all tests

Rationale for number of queues:

Rationale for priority increment/decrement size:

Rationale for priority values: 

Rationale for how priority value update frequency:

Rationale for time slice durations per priority value:


Tests:
Test1:
  This test outputs...
Test2:
Test3:
Test4:
Test5:
Test6:
Test7:
  This test outputs the thread ID of 13 threads that are initialized and called, then joined
  back to the main function. 

Testing results: 

Functions

 
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg);
Returns: -1 if malloc fails Args:
Description: 

/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg);
Description: my_pthread_create can be called to create a new thread to run a function. 
Return values: -1 if malloc fails
Arguments: a my_pthread_t struct, thread attributes (ignored), a pointer to the function to be run, and
a pointer to the argument to be passed into the function. 

/* give CPU pocession to other user level threads voluntarily */
int my_pthread_yield();

/* terminate a thread */
void my_pthread_exit(void *value_ptr);

/* wait for thread termination */
int my_pthread_join(my_pthread_t thread, void **value_ptr);

/* initial the mutex lock */
int my_pthread_mutex_init(my_pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);

/* aquire the mutex lock */
int my_pthread_mutex_lock(my_pthread_mutex_t *mutex);

/* release the mutex lock */
int my_pthread_mutex_unlock(my_pthread_mutex_t *mutex);

/* destroy the mutex */
int my_pthread_mutex_destroy(my_pthread_mutex_t *mutex);
