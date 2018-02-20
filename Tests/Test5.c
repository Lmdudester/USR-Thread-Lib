#include <sys/types.h>
#include <stdio.h>
#include "../my_pthread_t.h"

/* Test5 tests the following:
 * - return value passing
 * - nested thread creation
 */
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
	pthread_exit(ret);
	return NULL;
}

void * t_creater(void * i) {
	printf("t_creater begins.\n");
	pthread_t t2;

	printf("t_creater creates createe.\n");
	pthread_create(&t2, NULL, createe, NULL);

	void *ret;
	printf("t_creater joining on createe\n");
	pthread_join(t2, &ret);

	printf("t_creater ends.\n");
	pthread_exit(ret);
	return NULL;
}

void main(int argc, char ** argv) {
	printf("Main begins.\n");
	pthread_t t1;

	printf("Main creates t_creater.\n");
	pthread_create(&t1, NULL, t_creater, NULL);

	void * r;
	printf("Main joining on t_creater\n");
	pthread_join(t1, &r);

	data * ret = r;

	printf("Main ends, ret values -> d1 = %d, d2 = %d.\n", (*ret).d1, (*ret).d2);
}
