CC = gcc
CFLAGS = -g -c
LDFLAGS =-lmy_pthread
AR = ar -rc
RANLIB = ranlib

Target: my_pthread.a

all: Test1 Test2 Test3 Test4 Test5 Test6 Test7 Test8

my_pthread.a: my_pthread.o
	$(AR) libmy_pthread.a my_pthread.o
	$(RANLIB) libmy_pthread.a

my_pthread.o: my_pthread_t.h
	$(CC) -pthread $(CFLAGS) my_pthread.c

tester: my_pthread.o
	$(CC) p_thread_test.c my_pthread.o

Test1: ./Tests/Test1.c my_pthread.a
	$(CC) ./Tests/Test1.c -L. $(LDFLAGS) -o Test1

Test2: ./Tests/Test2.c my_pthread.a
	$(CC) ./Tests/Test2.c -L. $(LDFLAGS) -o Test2

Test3: ./Tests/Test3.c my_pthread.a
	$(CC) ./Tests/Test3.c -L. $(LDFLAGS) -o Test3

Test4: ./Tests/Test4.c my_pthread.a
	$(CC) ./Tests/Test4.c -L. $(LDFLAGS) -o Test4

Test5: ./Tests/Test5.c my_pthread.a
	$(CC) ./Tests/Test5.c -L. $(LDFLAGS) -o Test5

Test6: ./Tests/Test6.c my_pthread.a
	$(CC) ./Tests/Test6.c -L. $(LDFLAGS) -o Test6

Test7: ./Tests/Test7.c my_pthread.a
	$(CC) ./Tests/Test7.c -L. $(LDFLAGS) -o Test7

Test8: ./Tests/Test8.c my_pthread.a
	$(CC) ./Tests/Test8.c -L. $(LDFLAGS) -o Test8

#compile any individual arbitrary test
#%: Tests/%.c my_pthread.a
#	$(CC) $< -L. -lmy_pthread -o $@

clean:
	rm -rf Test[0-9]* testfile *.o *.a *.out
