// File:	my_pthread_t.h
// Author:	Yujie REN
// Date:	09/23/2017

// name: 							Liam Davies,	Kevin Lee
// username of iLab: 	lmd312,				kjl156
// iLab Server: factory

#ifndef MY_PTHREAD_T_H
#define MY_PTHREAD_T_H

#define _GNU_SOURCE

/* include lib header files that you need here: */
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <sys/time.h>

#define P_RUN 0
#define P_YIELD 1
#define P_WAIT_M 2
#define P_WAIT_T 3
#define P_EXIT 4

#define STKSZE 1024*64

typedef uint my_pthread_t;

// mutex struct definition
typedef struct my_pthread_mutex_t {
	/* add something here */
} my_pthread_mutex_t;

// tcb struct definition
typedef struct threadControlBlock {
  my_pthread_t tID; // Identification for the thread
  ucontext_t ctxt; // Contains all context info for thread
  int qNum; // The number of the prev queue this thread was in
  int stat; // Current status of the thread
  void * ret; // Pointer to return value
} tcb;

// tcb Node definition
typedef struct threadControlBlockNode {
  tcb data;
  struct threadControlBlockNode * next;
} tcbNode;

// Queues
tcbNode * q1;
tcbNode * q2;
tcbNode * q3;

// Linked Lists
tcbNode * finished;

// The currently running context
tcbNode * currCtxt;

// For threadID generation
my_pthread_t idCount;

/* Function Declarations: */

/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg);

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

#endif
