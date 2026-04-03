CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -std=c11

OBJ = main.o board.o links.o wincheck.o

all: twixt

twixt: $(OBJ)
	$(CC) $(CFLAGS) -o twixt $(OBJ)

clean:
	rm -f *.o twixt
