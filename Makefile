# compiler to use
CC = gcc

# flags to pass compiler
CFLAGS = -ggdb3 -std=c11 -Wall

# name for executable
EXE = test

# space-separated list of header files
HDRS = array.h trie.h stack.h re.h queue.h bloom_filter.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# space-separated list of source files
SRCS = trie.c test.c stack.c re.c array.c queue.c bloom_filter.c

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)


# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) -lm

# dependencies
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o
