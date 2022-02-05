CFLAGS = -std=c11 -Wall -ggdb3
CC = gcc
EXEC = chess
INCFLAGS = -I/includes
LIBFLAGS = -lSDL2 -lSDL2main


all : game graphics OBJ install 

graphics :
	cd graphics && make

game : 
	cd game && make

OBJ: 
	cd OBJ && touch * && make

install:
	cd OBJ && mv chess  ../

clean :	clean_graphics clean_OBJ clean_game
	rm -f $(EXEC)
	 
clean_graphics :
	cd graphics && make clean

clean_game :
	cd game && make clean

clean_OBJ :
	cd OBJ && make clean

.PHONY :all graphics game OBJ

