CC = gcc
CFLAGS = -std=c99 -Iinclude
EXECUTABLES = demo

demo: progressbar.o demo.o
	$(CC) $(CFLAGS) progressbar.o progressbar_demo.o -o demo

demo.o:
	$(CC) -c $(CFLAGS) test/progressbar_demo.c

progressbar.o: include/progressbar.h lib/progressbar.c
	$(CC) -c $(CFLAGS) lib/progressbar.c

clean:
	rm *.o $(EXECUTABLES)