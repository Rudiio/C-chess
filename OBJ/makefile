CFLAGS = -Wall
CC = gcc
EXEC = chess
INCFLAGS = -I ../includes
LIBFLAGS = -lSDL2 -lSDL2main
DIR = ../OBJ
OBJS = *.o

all : compile

compile : $(OBJS)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(EXEC) $(OBJS) $(LIBFLAGS)

clean :
	rm -f *.o 