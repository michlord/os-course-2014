CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99
TARGETS = task1 task2 task3

all: $(TARGETS)

task1: task1.o

task2: task2.o

task3: task3.o

clean:
		rm -f *.o

distclean: clean
		rm -f $(TARGETS)