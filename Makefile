PROGRAM   = rg_projekat
CC        = gcc
CFLAGS    = -g -Wall -Wextra -lm
LDFLAGS   = -lGL -lGLU -lglut
CUSTOMHEADERS = functions.c


%.o: %.c utility.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROGRAM): main.o utility.o
	$(CC) -o $(PROGRAM) main.o utility.o $(CFLAGS) $(LDFLAGS) && ./rg_projekat

.PHONY:clean

clean:
	rm *.o rg_projekat
