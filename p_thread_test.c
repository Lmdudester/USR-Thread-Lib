#include <sys/types.h>
#include <stdio.h>
#include "my_pthread_t.h"

void handlr(int signum){
  swap(0);
}

int swap(int x){
  tcbNode * mainTCB = currCtxt;
  tcbNode * ptr = (*q1).next;

  if(x == 0)
		swapcontext(&(*mainTCB).data.ctxt, &(*ptr).data.ctxt);
	if(x == 1)
		swapcontext(&(*ptr).data.ctxt, &(*mainTCB).data.ctxt);
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
	signal(SIGALRM, handlr);

	my_pthread_t t1, t2, t3;
  int i = 0;
  void * (*fptr)(void *) = funct;

  my_pthread_create(&t1, NULL, fptr, &i);
  my_pthread_create(&t2, NULL, fptr, &i);
  my_pthread_create(&t3, NULL, fptr, &i);

  raise(SIGALRM);
	raise(SIGALRM);

  printf("Res: %d\n", i);

}
