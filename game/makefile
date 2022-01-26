CFLAGS = -Wall
CC = gcc
EXEC = chess
INCFLAGS = -I ../includes
LIBFLAGS = -lSDL2 -lSDL2main
DIR = ../OBJ
OBJS = *.o
SRC = *.c

all: chess.o copy 

chess.o : $(SRC)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SRC) $(LIBFLAGS) && touch *

%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c -o $@ $< $(LIBFLAGS)

copy : $(OBJS)
	cp $(OBJS) $(DIR)

clean :
	rm -f *.o