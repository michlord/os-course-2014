CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99
TARGETS = task1 task2 task3 task4 task5 task7 task8 task9 task10

all: $(TARGETS)

task1: task1.o

task2: task2.o

task3: task3.o

task4: task4.o

task5: task5.o

task7: task7.o

task8: task8.o

task9: task9.o

task10.o: task10.c
		$(CC) $(CFLAGS) -pthread task10.c -c -o task10.o

task10: task10.o
		$(CC) -pthread task10.o -o task10

clean:
		rm -f *.o

distclean: clean
		rm -f $(TARGETS)