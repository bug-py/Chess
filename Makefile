BIN = ./bin/
SRC =./src/
OBJ= ./obj/
HEADER =./include/
FLAG=-Werror -Wextra  -I $(HEADER)
.PHONY : all clean

all : $(BIN)chess.exe
	
$(BIN)chess.exe:  $(OBJ)main.o $(OBJ)vector.o $(OBJ)board.o $(OBJ)piece.o $(OBJ)move.o $(OBJ)dynamic_array.o $(OBJ)alloc.o
	gcc $(FLAG) $^ -o $(BIN)chess.exe
$(OBJ)main.o: $(SRC)main.c
	gcc $(FLAG) -c  $< -o $@
$(OBJ)vector.o : $(SRC)vector.c $(HEADER)vector.h 
	gcc $(FLAG) -c  $< -o $@
$(OBJ)board.o : $(SRC)board.c $(HEADER)logique/board.h 
	gcc $(FLAG) -c  $< -o $@
$(OBJ)piece.o : $(SRC)piece.c $(HEADER)logique/piece.h 
	gcc $(FLAG) -c  $< -o $@
$(OBJ)move.o : $(SRC)move.c $(HEADER)logique/move.h 
	gcc $(FLAG) -c  $< -o $@
$(OBJ)dynamic_array.o : $(SRC)dynamic_array.c $(HEADER)structdata/dynamic_array.h 
	gcc $(FLAG) -c  $< -o $@
$(OBJ)alloc.o : $(SRC)alloc.c $(HEADER)structdata/alloc.h 
	gcc $(FLAG) -c  $< -o $@
clean :
	rm -r $(OBJ)*.o
	rm -r $(BIN)*.exe