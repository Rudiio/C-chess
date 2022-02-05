CFLAGS = -std=c11 -Wall -ggdb3
CC = gcc
EXEC = chess
INCFLAGS = -I ../includes
LIBFLAGS = -lSDL2 -lSDL2main
DIR = ../OBJ
OBJS = *.o
SRC = *.c

all: board.o copy 

board.o : $(SRC)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SRC) $(LIBFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c -o $@ $< $(LIBFLAGS)

copy : $(OBJS)
	cp $(OBJS) $(DIR)

clean :
	rm -f *.o
