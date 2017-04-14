CC       = gcc
CPPFLAGS =#
CFLAGS   = -Wall -Wextra -Og -g3
LDFLAGS  =#
LDLIBS   =#

all: paq

paq: paq.o dates.o astro.o
paq.o: paq.c dates.h astro.h
dates.o: dates.c dates.h
astro.o: astro.c astro.h

clean:
	${RM} *.o paq

.PHONY: clean all
