BIN = ./bin/
SRC =./src/
OBJ= ./obj/
HEADER =./include/
FLAG=-Werror -Wextra  -I $(HEADER)
.PHONY : all clean

all : $(OBJ)main.o
	gcc $(FLAG) $^ -o $(BIN)chess.exe

$(OBJ)main.o: $(SRC)main.c
	gcc $(FLAG) -c  $< -o $@

clean :
	rm -r $(OBJ)*.o
	rm -r $(BIN)*.exe