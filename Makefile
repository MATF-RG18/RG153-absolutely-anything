PROGRAM   = rg_projekat
CC        = gcc
CFLAGS    = -g -Wall -Wextra -lm
LDFLAGS   = -lGL -lGLU -lglut
CUSTOMHEADERS = functions.c

$(PROGRAM): main.o
	$(CC) -o $(PROGRAM) main.o  $(CFLAGS) $(LDFLAGS) && ./rg_projekat


