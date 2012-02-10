CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
EXEC=sudoku

all: $(EXEC)

$(EXEC): sudoku.o tools.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c %.h structures.h constants.h
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)

