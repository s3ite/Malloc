CC = gcc
CPPFLAGS = -D_DEFAULT_SOURCE
CFLAGS = -Wall -Wextra -Werror -std=c99 -fPIC -fno-builtin -Wvla -g
LDFLAGS = -shared
VPATH = src

TARGET_LIB = libmalloc.so
OBJS = allocator.o interface.o
MALLOC = malloc.o

all: library

library: $(TARGET_LIB)
$(TARGET_LIB): CFLAGS += -pedantic -fvisibility=hidden
$(TARGET_LIB): LDFLAGS += -Wl,--no-undefined
$(TARGET_LIB): $(OBJS) $(MALLOC)
	$(CC) $(LDFLAGS) -o $@ $^

check:
	$(CC) $(CFLAGS) $(OBJS) $(MALLOC) ./tests/tests.c -o test
	./test

debug: CFLAGS += -g
debug: clean $(TARGET_LIB)

clean:
	$(RM) $(TARGET_LIB) $(OBJS) $(MALLOC)

.PHONY: all $(TARGET_LIB) clean
