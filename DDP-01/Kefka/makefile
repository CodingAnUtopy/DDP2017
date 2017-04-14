#########################
# customise these
CFILES := affichage.c DDP-01.01.c DDP-01.02.c DDP-01.03.c svg.c main.c
PROG := prog
CFLAGS := -Wall -Wextra -g
LDFLAGS :=
########################

# -MMD generates dependencies while compiling
CFLAGS += -MMD
CC := gcc

OBJFILES := $(CFILES:.c=.o)
DEPFILES := $(CFILES:.c=.d)

$(PROG) : $(OBJFILES)
	$(LINK.o) $(LDFLAGS) -o $@ $^

clean :
	rm -rf $(PROG) $(OBJFILES) $(DEPFILES)
	
cleanwin :
	del /f $(PROG) $(OBJFILES) $(DEPFILES)

-include $(DEPFILES)