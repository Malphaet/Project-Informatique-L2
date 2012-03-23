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

all: $(DOXY) $(EXEC)

$(DOXY):
	doxygen Doxyfile

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
	rm -Rf $(DOC)/*

