CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99
TARGETS = task1 task2 task3 task4 task5 task7 task9

all: $(TARGETS)

task1: task1.o

task2: task2.o

task3: task3.o

task4: task4.o

task5: task5.o

task7: task7.o

task9: task9.o

clean:
		rm -f *.o

distclean: clean
		rm -f $(TARGETS)