CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99
TARGETS = task1 task1_helper1 task1_helper2 task2 task5

all: $(TARGETS)

task1: task1.o
task1_helper1: task1_helper1.o
task1_helper2: task1_helper2.o

task2.o: task2.c
		$(CC) $(CFLAGS) -pthread -lrt task2.c -c -o task2.o
task2: task2.o
		$(CC) -pthread -lrt task2.o -o task2

task5.o: task5.c
		$(CC) $(CFLAGS) -pthread -lrt task5.c -c -o task5.o
task5: task5.o 
		$(CC) -pthread -lrt task5.o -o task5

clean:
		rm -f *.o

distclean: clean
		rm -f $(TARGETS)