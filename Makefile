CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
OBJ = game.o tic_tac_toe.o 
EXEC = tic_tac_toe

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -DDEBUG
else
    CFLAGS += -DNDEBUG
endif

$(EXEC) : $(OBJ)
	$(CC) $^ -o $@

tic_tac_toe.o : tic_tac_toe.c  game.h ansi.h
	$(CC) $(CFLAGS) -c $< 

game.o: game.c game.h ansi.h
	$(CC) $(CFLAGS) -c $< 

.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJ)
