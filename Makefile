# compiler to use
CC = gcc

# flags to pass compiler
CFLAGS = -ggdb3 -O3 -std=c11 -Wall -Werror

# name for executable
EXE = trie_test

# space-separated list of header files
HDRS = trie.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# space-separated list of source files
SRCS = trie_test.c trie.c

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)


# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o
