/**
  @file puzzle.c
  @author David Lovato, dalovato
  This file is the main file of the program, linking the board and command files.
  The main purpose of this program is to make and solve puzzles, which are just arrays
  of numbers, from 1 to [end].
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "board.h"
#include "command.h"

#define DEFAULT_ROWS 5
#define DEFAULT_COLS 7
#define CMD_LIMIT 30

static void takeUserInput(int rows, int cols, int board[][DEFAULT_COLS], char cmd[CMD_LIMIT + 1]);

int main(int argc, char *argv[]) {
  int rows = DEFAULT_ROWS;
  int cols = DEFAULT_COLS;

  int board[rows][cols];
  char cmd[CMD_LIMIT + 1];
  
  if (argc > 2) {
    fprintf(stderr, "usage: puzzle [config-file]\n");
    exit(1);
  }
  
  if (argc == 2) {
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
      fprintf(stderr, "Can't open config file: config.txt\nusage: puzzle [config-file]\n");
      exit(1);
    }
    fscanf(fp, "%d%d", &rows, &cols);
    skipLine(fp);
    initBoard(rows, cols, board);
    while (getCommand(fp, cmd)) {
      if (isspace(cmd[CMD_LIMIT])) {
        fprintf(stderr, "Invalid configuration\n");
        exit(1);
      } else if (runCommand(cmd, rows, cols, board)) {
        //do nothing
      } else {
        fprintf(stderr, "Invalid configuration\n");
        exit(1);
      }
    }
    printBoard(rows, cols, board);
    printf("\n> ");
    takeUserInput(rows, cols, board, cmd);
  } else {
    initBoard(rows, cols, board);
    printBoard(rows, cols, board);
    printf("\n> ");
    takeUserInput(rows, cols, board, cmd);
  }
  return 0;
}

static void takeUserInput(int rows, int cols, int board[][cols], char cmd[CMD_LIMIT + 1]) {
  while (getCommand(stdin, cmd)) {
    if (isspace(cmd[CMD_LIMIT])) {
      printf("\nInvalid command\n\n> ");
    } else if (runCommand(cmd, rows, cols, board)) {
      printf("\n");
      printBoard(rows, cols, board);
      printf("\n> ");
    } else {
      printf("\nInvalid command\n\n> ");
    }
  }
}
