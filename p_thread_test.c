#include <sys/types.h>
#include <stdio.h>
#include "my_pthread_t.h"

/* MUST DEFINE A TEST TO COMPILE */
//#define TEST1
#define TEST2
//#define TEST3
//#define TEST4

/*TEST1 tests the following:
 * my_pthread_t
 * my_pthread_exit
*/
#ifdef TEST1
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

#ifdef TEST2
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
