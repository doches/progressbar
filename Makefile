CC = gcc
CFLAGS = -std=c99 -Iinclude
EXECUTABLES = demo

all: demo libprogressbar.so libprogressbar.a

demo: progressbar.o demo.o statusbar.o
	$(CC) $(CFLAGS) progressbar.o statusbar.o progressbar_demo.o -lncurses -o demo

demo.o:
	$(CC) -c $(CFLAGS) test/progressbar_demo.c

progressbar.o: include/progressbar.h lib/progressbar.c
	$(CC) -c $(CFLAGS) lib/progressbar.c

libprogressbar.so: include/progressbar.h lib/progressbar.c
	$(CC) -fPIC -shared -o $@ -c $(CFLAGS) lib/progressbar.c

libprogressbar.a: progressbar.o
	ar rs libprogressbar.a progressbar.o

statusbar.o: include/statusbar.h lib/statusbar.c
	$(CC) -c $(CFLAGS) lib/statusbar.c

.PHONY: clean

clean:
	-rm -f *.o libprogressbar.so libprogressbar.a $(EXECUTABLES)
