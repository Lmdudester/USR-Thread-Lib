//#include <unistd.h>
//#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
//#include <stdlib.h>


void main(int argc, char ** argv){
  uint i = 0;

  uint temp = __sync_fetch_and_add(&i, 1);

  printf("Temp: %u, i: %u", temp, i);
}
