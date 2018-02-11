#include <sys/types.h>
#include <stdio.h>
#include "my_pthread_t.h"

int swap(int x){
	if(x == 0)
		swapcontext(&(*mainTCB).data.ctxt, &(*ready).data.ctxt);
	if(x == 1)
		swapcontext(&(*ready).data.ctxt, &(*mainTCB).data.ctxt);
	if(x == 2)
		setcontext(&(*mainTCB).data.ctxt);

	return 0;
}

void * funct(void * x) {
  int * y = x;
  *y += 12;
  swap(2);
}

void main(int argc, char ** argv){
  my_pthread_t t1, t2;
  int i = 0;
  void * (*fptr)(void *) = funct;

  my_pthread_create(&t1, NULL, fptr, &i);
  my_pthread_create(&t2, NULL, fptr, &i);

  swap(0);
  swap(0);

  printf("Res: %d\n", i);

}
