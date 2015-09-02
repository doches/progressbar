EXECUTABLE = demo
SHARED_LIB = libprogressbar.so
STATIC_LIB = libprogressbar.a

SRC=lib
INCLUDE=include
TEST=test
CFLAGS += -std=c99 -I$(INCLUDE) -Wimplicit-function-declaration -Wall -Wextra -pedantic
CFLAGS_DEBUG = -g -O0
LDLIBS = -lncurses

all: $(EXECUTABLE) $(SHARED_LIB) $(STATIC_LIB)

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(EXECUTABLE)

doc: include/progressbar.h include/statusbar.h
	mkdir -p doc
	doxygen

$(EXECUTABLE): $(EXECUTABLE).o progressbar.o statusbar.o

libprogressbar.so: $(INCLUDE)/progressbar.h $(SRC)/progressbar.c
	$(CC) -fPIC -shared -o $@ -c $(CFLAGS) $(CPPFLAGS) $(SRC)/progressbar.c

libprogressbar.a: libprogressbar.a(progressbar.o)

%.o: $(SRC)/%.c $(INCLUDE)/%.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

demo.o: CFLAGS += -std=gnu99 # Demo uses usleep which requires POSIX or BSD source
demo.o: $(TEST)/demo.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o demo.o

.PHONY: clean
clean:
	rm -f *.o $(EXECUTABLE) $(SHARED_LIB) $(STATIC_LIB)
	rm -rf doc
