CC = gcc
CFLAGS = -std=c99 -Iinclude
EXECUTABLES = demo

demo: progressbar.o demo.o statusbar.o
	$(CC) $(CFLAGS) progressbar.o statusbar.o progressbar_demo.o -o demo

demo.o:
	$(CC) -c $(CFLAGS) test/progressbar_demo.c

progressbar.o: include/progressbar.h lib/progressbar.c
	$(CC) -c $(CFLAGS) lib/progressbar.c

statusbar.o: include/statusbar.h lib/statusbar.c
	$(CC) -c $(CFLAGS) lib/statusbar.c

.PHONY: clean

clean:
	-rm *.o $(EXECUTABLES)