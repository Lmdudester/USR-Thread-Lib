#include <sys/types.h>
#include <stdio.h>
#include "my_pthread_t.h"

/* MUST DEFINE A TEST TO COMPILE */
// #define TEST1
// #define TEST2
// #define TEST3
// #define TEST4
// #define TEST5
// #define TEST6
#define TEST7


/* TEST1 tests the following:
 * - my_pthread_t
 * - my_pthread_exit
 */
#ifdef TEST1	//	Liam
	void * f1(void * i){
	  int * iptr = (int *) i;
	  *iptr += 1;
	  my_pthread_exit(NULL);
	}

	void * f2(void * i){
	  int * iptr = (int *) i;
	  *iptr += 2;
	  my_pthread_exit(NULL);
	}

	void * f3(void * i){
	  int * iptr = (int *) i;
	  *iptr += 3;
	  my_pthread_exit(NULL);
	}

	void main(int argc, char ** argv){
	  my_pthread_t t1, t2, t3, t4, t5;
	  void * (*f1ptr)(void *) = f1;
	  void * (*f2ptr)(void *) = f2;
	  void * (*f3ptr)(void *) = f3;

	  int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0;

	  my_pthread_create(&t1, NULL, f1ptr, &i1);
	  my_pthread_create(&t2, NULL, f2ptr, &i2);
	  my_pthread_create(&t3, NULL, f3ptr, &i3);
	  my_pthread_create(&t4, NULL, f1ptr, &i4);
	  my_pthread_create(&t5, NULL, f2ptr, &i5);

	  void * ret;

	  my_pthread_join(t1, &ret);
	  my_pthread_join(t2, &ret);
	  my_pthread_join(t3, &ret);
	  my_pthread_join(t4, &ret);
	  my_pthread_join(t5, &ret);

	  printf("Complete.\n");
	  printf("i1: %d, i2: %d, i3: %d, i4: %d, i5: %d\n", i1, i2, i3, i4, i5);
	}
#endif

/* TEST2 tests the following:
 * - argument passing
 * - basic locks
 */
#ifdef TEST2	//	Liam
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
#endif

#ifdef TEST3	//	Kevin
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
#endif

#ifdef TEST4	//	Kevin
	my_pthread_mutex_t lock;
	int sum;

	void *add2(void *param) {
	    printf("In the add method #2\n");

			my_pthread_mutex_lock(&lock);
	    int i;
	    for (i = 0; i < 10000000; i++) {
	      sum = sum + 1;
	    }
	    my_pthread_mutex_unlock(&lock);

	    printf("sum #2:%d\n",sum);

	    printf("exited #2\n");

	    my_pthread_exit(NULL);
	    return NULL;
	}

	void *add1(void *param) {
	    printf("In the add method #1\n");

			my_pthread_mutex_lock(&lock);
	    int i;
	    for (i = 0; i < 10000000; i++) {
	      sum = sum + 1;
	    }
	    my_pthread_mutex_unlock(&lock);

	    printf("sum #1:%d\n",sum);

	    printf("exited #1\n");

	    my_pthread_exit(NULL);
	    return NULL;
	}

	void main(int argc, char ** argv){
	    my_pthread_t tid1, tid2;

	    my_pthread_mutex_init(&lock, NULL);

	    printf("Starting\n");
	    // void * (*ptr1)(void *) = add1;
	    // void * (*ptr2)(void *) = add2;

	    my_pthread_create(&tid1, NULL, add1, NULL);
	    my_pthread_create(&tid2, NULL, add2, NULL);

	    void *ret;
	    my_pthread_join(tid1, &ret);
	    my_pthread_join(tid2, &ret);

	    my_pthread_mutex_destroy(&lock);

	    printf("Ended, %d\n",sum);
	}

	/* Needs to print out (or some variation of)
	Starting
	In the add method #1
	In the add method #2
	sum #1:m
	exited #1
	sum #2:20000000
	exited #2
	Ended, 20000000
	*/
#endif

/* TEST5 tests the following:
 * - return value passing
 * - nested thread creation
 */
#ifdef TEST5	//	Liam
	typedef struct data_test {
		int d1;
		int d2;
	} data;

	void * createe(void * i) {
		printf("createe begins.\n");

		printf("createe creates ret struct.\n");
		data * ret = malloc(sizeof(data));
		(*ret).d1 = 5;
		(*ret).d2 = 20;

		printf("createe ends.\n");
		my_pthread_exit(ret);
		return NULL;
	}

	void * t_creater(void * i) {
		printf("t_creater begins.\n");
		my_pthread_t t2;

		printf("t_creater creates createe.\n");
		my_pthread_create(&t2, NULL, createe, NULL);

		void *ret;
		printf("t_creater joining on createe\n");
		my_pthread_join(t2, &ret);

		printf("t_creater ends.\n");
		my_pthread_exit(ret);
		return NULL;
	}

	void main(int argc, char ** argv) {
		printf("Main begins.\n");
		my_pthread_t t1;

		printf("Main creates t_creater.\n");
		my_pthread_create(&t1, NULL, t_creater, NULL);

		void * r;
		printf("Main joining on t_creater\n");
		my_pthread_join(t1, &r);

		data * ret = r;

		printf("Main ends, ret values -> d1 = %d, d2 = %d.\n", (*ret).d1, (*ret).d2);
	}
#endif

#ifdef TEST6 // Kevin
	my_pthread_mutex_t lock;
	int sum = 0;

	void *add2(void *param) {
	    printf("In the add method 2\n");

			my_pthread_mutex_lock(&lock);
			sum += *(int *)param;
			my_pthread_mutex_unlock(&lock);

	    printf("sum #2:%d\n",sum);
	    printf("exited #2\n");

	    my_pthread_exit(NULL);
	    return NULL;
	}

	void *add1(void *param) {
	    printf("In the add method 1\n");

			my_pthread_mutex_lock(&lock);
			sum += *(int *)param;
			my_pthread_mutex_unlock(&lock);

	    printf("sum #1:%d\n",sum);
	    printf("exited #1\n");

	    my_pthread_exit(NULL);
	    return NULL;
	}

	void main(int argc, char ** argv){
	    my_pthread_t tid1, tid2, tid3;

	    my_pthread_mutex_init(&lock, NULL);

	    printf("Starting\n");

			int x = 4;

	    my_pthread_create(&tid1, NULL, add1, &x);
			my_pthread_create(&tid2, NULL, add2, &x);

	    void *ret;
	    my_pthread_join(tid1, &ret);
			my_pthread_join(tid2, &ret);
			printf("Here?");

	    my_pthread_mutex_destroy(&lock);

			printf("Done...\n");
	    printf("Ended, %d\n",sum);
	}
#endif

#ifdef TEST7 // Kevin
	int data = 0;
	int limit = 1000;
	my_pthread_mutex_t lock;

	void *print(void *param) {
		printf("Thread Num - %d\n",*(int *)param);
		int x = 0;
		my_pthread_mutex_lock(&lock);
		for(x = 0; x < limit; x++){
			data ++;
		}
		my_pthread_mutex_unlock(&lock);

		my_pthread_exit(NULL);
		return NULL;
	}

	void main(int argc, char ** argv){
		my_pthread_t tid0, tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8, tid9, tid10, tid11, tid12, tid13;

		// my_pthread_mutex_init(&lock, NULL);

		my_pthread_create(&tid0, NULL, print, &data);
		my_pthread_create(&tid1, NULL, print, &data);
		my_pthread_create(&tid2, NULL, print, &data);
		my_pthread_create(&tid3, NULL, print, &data);
		my_pthread_create(&tid4, NULL, print, &data);
		my_pthread_create(&tid5, NULL, print, &data);
		my_pthread_create(&tid6, NULL, print, &data);
		my_pthread_create(&tid7, NULL, print, &data);
		my_pthread_create(&tid8, NULL, print, &data);
		my_pthread_create(&tid9, NULL, print, &data);
		my_pthread_create(&tid10, NULL, print, &data);
		my_pthread_create(&tid11, NULL, print, &data);
		my_pthread_create(&tid12, NULL, print, &data);
		my_pthread_create(&tid13, NULL, print, &data);

		void * ret;

		my_pthread_join(tid0, &ret);
		my_pthread_join(tid1, &ret);
		my_pthread_join(tid2, &ret);
		my_pthread_join(tid3, &ret);
		my_pthread_join(tid4, &ret);
		my_pthread_join(tid5, &ret);
		my_pthread_join(tid6, &ret);
		my_pthread_join(tid7, &ret);
		my_pthread_join(tid8, &ret);
		my_pthread_join(tid9, &ret);
		my_pthread_join(tid10, &ret);
		my_pthread_join(tid11, &ret);
		my_pthread_join(tid12, &ret);
		my_pthread_join(tid13, &ret);

		my_pthread_mutex_destroy(&lock);

		printf("Can you hear me?\n");
	}
#endif
