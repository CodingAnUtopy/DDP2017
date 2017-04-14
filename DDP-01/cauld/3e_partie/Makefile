CC = gcc
CFLAGS = -Wall -Wextra -pedantic -pedantic-errors
DEL_FILE = rm -rf


frequence: main.o
	$(CC) main.o -o frequence

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)



.PHONY: clean mrproper

clean:
	$(DEL_FILE) *.o

mrproper: clean
	$(DEL_FILE) frequence