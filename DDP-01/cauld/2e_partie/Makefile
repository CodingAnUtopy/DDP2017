CC = gcc
CFLAGS = -Wall -Wextra -pedantic -pedantic-errors
DEL_FILE = rm -rf


ddp_01_02: main.o easter.o
	$(CC) main.o easter.o -o ddp_01_02

main.o: main.c easter.h
	$(CC) -c main.c -o main.o $(CFLAGS)

easter.o: easter.c easter.h
	$(CC) -c easter.c -o easter.o $(CFLAGS)


.PHONY: clean mrproper

clean:
	$(DEL_FILE) *.o

mrproper: clean
	$(DEL_FILE) ddp_01_02