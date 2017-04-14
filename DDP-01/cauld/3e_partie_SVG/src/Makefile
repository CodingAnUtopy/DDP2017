CC = gcc
CFLAGS = -Wall -Wextra -pedantic -pedantic-errors
#CFLAGS = -Weverything -Wno-padded
LDLIBS = -lm
DEL_FILE = rm -rf
EXEC = ddp_01_03

$(EXEC): main.o error.o llist.o svgbarchart.o svgutil.o test.o
	$(CC) main.o error.o llist.o svgbarchart.o svgutil.o test.o -o $(EXEC) $(LDLIBS)

error.o: error.c error.h
	$(CC) -c error.c -o error.o $(CFLAGS)

llist.o: llist.c llist.h error.h
	$(CC) -c llist.c -o llist.o $(CFLAGS)

svgbarchart.o: svgbarchart.c svgbarchart.h svgutil.h error.h
	$(CC) -c svgbarchart.c -o svgbarchart.o $(CFLAGS)

svgutil.o: svgutil.c llist.h error.h
	$(CC) -c svgutil.c -o svgutil.o $(CFLAGS)

test.o: test.c test.h llist.h svgutil.h svgbarchart.h
	$(CC) -c test.c -o test.o $(CFLAGS)



.PHONY: clean mrproper

clean:
	$(DEL_FILE) *.o

mrproper: clean
	$(DEL_FILE) $(EXEC)