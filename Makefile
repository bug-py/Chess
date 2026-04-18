BIN = ./bin/
SRC =./src/
OBJ= ./obj/
HEADER =./include/
FLAG=-Werror -Wextra  -I $(HEADER)
.PHONY : all clean

all : $(OBJ)main.o $(OBJ)vector.o $(OBJ)board.o
	gcc $(FLAG) $^ -o $(BIN)chess.exe

$(OBJ)main.o: $(SRC)main.c
	gcc $(FLAG) -c  $< -o $@
$(OBJ)vector.o : $(SRC)vector.c $(HEADER)vector.h 
	gcc $(FLAG) -c  $< -o $@
$(OBJ)board.o : $(SRC)board.c $(HEADER)logique/board.h 
	gcc $(FLAG) -c  $< -o $@
clean :
	rm -r $(OBJ)*.o
	rm -r $(BIN)*.exe