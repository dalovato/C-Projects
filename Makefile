# We're using the default rules for make, but we're using
# these variables to get them to do exactly what we want.
CC = gcc
CFLAGS = -Wall -std=c99
puzzle: board.o command.o
puzzle.o: board.h command.h
command.o: board.h
clean:
	rm -f puzzle puzzle.o
	rm -f command command.o
	rm -f board board.o
	rm -f output.txt
