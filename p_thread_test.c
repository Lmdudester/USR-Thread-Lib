#include <sys/types.h>
#include <stdio.h>
#include "my_pthread_t.h"

void * funct(void * x) {
  int * y = x;
  *y += 12;
}

void main(int argc, char ** argv){
  my_pthread_t t1, t2;
  int i = 0;
  void * (*fptr)(void *) = funct;

  my_pthread_create(&t1, NULL, fptr, &i);
  my_pthread_create(&t2, NULL, fptr, &i);

  printf("%u - %u\n", t1, t2);

}
