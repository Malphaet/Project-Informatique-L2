CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 


BIN=./bin
INC=./include
OBJ=./obj
SRC=./src
DOC=./doc

DOXY=$(DOC)/html/index.html

MAKE=$(CC) $(CFLAGS) -o $@ -c $< -lm -I$(INC)/
INCLUDES= $(INC)/tools.h $(INC)/structures.h $(INC)/constants.h
EXEC=$(BIN)/sudoku
OBJS=$(OBJ)/sudoku.o $(OBJ)/tools.o $(OBJ)/rules.o $(OBJ)/backtrack.o

all: doc $(EXEC)

doc: redo
	doxygen Doxyfile

redo:

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ)/sudoku.o: $(SRC)/sudoku.c $(INCLUDES)
	$(MAKE)

$(OBJ)/tools.o: $(SRC)/tools.c $(INCLUDES)
	$(MAKE)

$(OBJ)/rules.o: $(SRC)/rules.c $(INCLUDES)
	$(MAKE)

$(OBJ)/backtrack.o: $(SRC)/backtrack.c $(INCLUDES)
	$(MAKE)

clean: 
	rm -f $(OBJ)/*.o
	
cleaner: clean
	rm -f $(EXEC)
	rm -Rf $(DOC)/*

