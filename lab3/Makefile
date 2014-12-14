CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99
TARGETS = task1 task1_helper1 task1_helper2

all: $(TARGETS)

task1: task1.o
task1_helper1: task1_helper1.o
task1_helper2: task1_helper2.o

clean:
		rm -f *.o

distclean: clean
		rm -f $(TARGETS)