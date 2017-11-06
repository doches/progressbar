EXECUTABLE = demo
#SHARED_LIB = libprogressbar.so
#STATIC_LIB = libprogressbar.a

SRC=lib
INCLUDE=include/progressbar
TEST=test
CFLAGS += -std=c99 -I$(INCLUDE) -Wimplicit-function-declaration -Wall -Wextra -pedantic
CFLAGS_DEBUG = -g -O0
LDLIBS = -lncurses

all: $(EXECUTABLE) libprogressbar.so libprogressbar.a libstatusbar.so libstatusbar.a

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(EXECUTABLE)

doc: $(INCLUDE)/progressbar.h $(INCLUDE)/statusbar.h
	mkdir -p doc
	doxygen

$(EXECUTABLE): $(EXECUTABLE).o progressbar.o statusbar.o

libprogressbar.so: $(INCLUDE)/progressbar.h $(SRC)/progressbar.c
	$(CC) -fPIC -shared -o $@ -c $(CFLAGS) $(CPPFLAGS) $(SRC)/progressbar.c

libprogressbar.a: libprogressbar.a(progressbar.o)

libstatusbar.so: $(INCLUDE)/statusbar.h $(SRC)/statusbar.c
	$(CC) -fPIC -shared -o $@ -c $(CFLAGS) $(CPPFLAGS) $(SRC)/statusbar.c

libstatusbar.a: libstatusbar.a(statusbar.o)	

install:
	cp libprogressbar.* libstatusbar.* /usr/local/lib
	cp -r include/progressbar /usr/local/include

%.o: $(SRC)/%.c $(INCLUDE)/%.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

demo.o: CFLAGS += -std=gnu99 # Demo uses usleep which requires POSIX or BSD source
demo.o: $(TEST)/demo.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o demo.o

.PHONY: clean
clean:
	rm -f *.o $(EXECUTABLE) $libprogressbar.so libprogressbar.a libstatusbar.so libstatusbar.a
	rm -rf doc
