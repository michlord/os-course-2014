CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99
TARGETS = task1

all: $(TARGETS)

task1: task1.o

clean:
		rm -f *.o

distclean: clean
		rm -f $(TARGETS)