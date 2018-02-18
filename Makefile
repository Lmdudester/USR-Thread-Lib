CC = gcc
CFLAGS = -g -c
AR = ar -rc
RANLIB = ranlib


Target: my_pthread.a

my_pthread.a: my_pthread.o
	$(AR) libmy_pthread.a my_pthread.o
	$(RANLIB) libmy_pthread.a

my_pthread.o: my_pthread_t.h
	$(CC) -pthread $(CFLAGS) my_pthread.c

tester: my_pthread.o
	$(CC) p_thread_test.c my_pthread.o

%: %.c my_pthread.o
	$(CC) my_pthread.o $< -o $@

clean:
	rm -rf testfile *.o *.a *.out
