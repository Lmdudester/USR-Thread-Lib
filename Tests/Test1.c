#include <sys/types.h>
#include <stdio.h>
#include "../my_pthread_t.h"

/* Test1 tests the following:
* - my_pthread_t
* - my_pthread_exit
*/
void * f1(void * i) {
	int * iptr = (int *)i;
	*iptr += 1;
	pthread_exit(NULL);
}

void * f2(void * i) {
	int * iptr = (int *)i;
	*iptr += 2;
	pthread_exit(NULL);
}

void * f3(void * i) {
	int * iptr = (int *)i;
	*iptr += 3;
	pthread_exit(NULL);
}

void main(int argc, char ** argv) {
	pthread_t t1, t2, t3, t4, t5;
	void * (*f1ptr)(void *) = f1;
	void * (*f2ptr)(void *) = f2;
	void * (*f3ptr)(void *) = f3;

	int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0;

	pthread_create(&t1, NULL, f1ptr, &i1);
	pthread_create(&t2, NULL, f2ptr, &i2);
	pthread_create(&t3, NULL, f3ptr, &i3);
	pthread_create(&t4, NULL, f1ptr, &i4);
	pthread_create(&t5, NULL, f2ptr, &i5);

	void * ret;

	pthread_join(t1, &ret);
	pthread_join(t2, &ret);
	pthread_join(t3, &ret);
	pthread_join(t4, &ret);
	pthread_join(t5, &ret);

	printf("Complete.\n");
	printf("i1: %d, i2: %d, i3: %d, i4: %d, i5: %d\n", i1, i2, i3, i4, i5);
}
