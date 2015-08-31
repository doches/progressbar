CC = gcc
SHARED_CFLAGS = -Iinclude -Wimplicit-function-declaration -Wall -Wextra -pedantic
CFLAGS = -std=c99 $(SHARED_CFLAGS)
# The demo program isn't pure C99, because it uses usleep(). Hence the SHARED_CFLAGS nonsense.
DEMO_CFLAGS = -std=gnu99 $(SHARED_CFLAGS)
EXECUTABLES = demo

all: demo libprogressbar.so libprogressbar.a

demo: progressbar.o demo.o statusbar.o
	$(CC) $(DEMO_CFLAGS) progressbar.o statusbar.o progressbar_demo.o -lncurses -o demo

demo.o:
	$(CC) -c $(DEMO_CFLAGS) test/progressbar_demo.c

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
