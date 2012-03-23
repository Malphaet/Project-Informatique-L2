CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
EXEC=sudoku

BIN=./bin
INC=./include
OBJ=./obj
SRC=./Programs
DOC=./Doc

MAKE=$(CC) $(CFLAGS) -o $@ -c $< -lm -I$(INC)/
INCLUDES= $(INC)/tools.h $(INC)/structures.h $(INC)/constants.h

all: $(EXEC)

$(EXEC): $(OBJ)/sudoku.o $(OBJ)/tools.o $(OBJ)/rules.o
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ)/sudoku.o: $(SRC)/sudoku.c $(INCLUDES)
	$(MAKE)

$(OBJ)/tools.o: $(SRC)/tools.c $(INCLUDES)
	$(MAKE)

$(OBJ)/rules.o: $(SRC)/rules.c $(INCLUDES)
	$(MAKE)

clean: 
	rm -f $(OBJ)/*.o
	
cleaner: clean
	rm -f $(BIN)/$(EXEC)
	rm -Rf ../Doc/*

