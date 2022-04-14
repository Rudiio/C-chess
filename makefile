CC = gcc
CFLAGS = -std=c11 -Wall -ggdb3
EXEC = chess
INCFLAGS = -I ./includes/
LIBFLAGS = -lSDL2 -lSDL2main
OBJ= 2players.o chess.o Jeu.o List.o ListArray.o board.o input.o pieces.o 

.PHONY : all $(OBJ) $(EXEC) clean clean_OBJ

all : $(EXEC)

2players.o : game/2players.c 
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< $(LIBFLAGS)

chess.o : game/chess.c 
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< $(LIBFLAGS)

Jeu.o : game/Jeu.c 
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< $(LIBFLAGS)
	
List.o : game/List.c 
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< $(LIBFLAGS)

ListArray.o : game/ListArray.c 
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< $(LIBFLAGS)

board.o : graphics/board.c 
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< $(LIBFLAGS)

input.o : graphics/input.c 
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< $(LIBFLAGS)

pieces.o : graphics/pieces.c 
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< $(LIBFLAGS)

mvo :
	mv *.o OBJ

$(EXEC): $(OBJ) mvo
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@  OBJ/*.o $(LIBFLAGS)

clean :	clean_OBJ 
	rm -f $(EXEC)

clean_OBJ :
	rm -f OBJ/*.O

