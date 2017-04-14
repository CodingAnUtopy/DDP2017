CC = gcc
CFLAGS = -Wall -Wextra -pedantic -pedantic-errors
DEL_FILE = rm -rf


ddp_01_01: main.o
	$(CC) main.o -o ddp_01_01

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)



.PHONY: clean mrproper

clean:
	$(DEL_FILE) *.o

mrproper: clean
	$(DEL_FILE) ddp_01_01