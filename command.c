/**
  @file command.c
  @author David Lovato, dalovato
  This file will take in commands from standard input or from
  a given configuration file and pass them to the board file for
  manipulating the board.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "board.h"

#define CMD_LENGTH 5
#define CMD_LIMIT 30
#define MAX_HISTORY 10

int histLen;
char history[MAX_HISTORY][CMD_LIMIT];

/**
 * This function will read and discard input up until the next line, looking for
 * the '\n' char.
 * @param stream file stream from config file or stdin.
 */
void skipLine(FILE *stream) {
  char ch;
  while ((ch = getc(stream)) != '\n') {
    //do nothing
  }
}

/**
 * This function will move the command stack up one place once it fills up to
 * 10 spots.
 * @param history[][CMD_LIMIT +   1] this is the current history array
 */
static void moveStack(char history[][CMD_LIMIT]) {
  char empty[CMD_LIMIT] = "";
  for (int i = 0; i < MAX_HISTORY; i++) {
    if (i == 0 || i == MAX_HISTORY - 1) {
      strcpy(history[i], empty);
    } else {
      strcpy(history[i - 1], history[i]);
    }
  }
}

/**
 * This function will read a given command up to 30 chars long and stores it in
 * cmd, disregarding the rest of the input if it's too long. The function returns
 * true if it successfully reads a line or returns false if it hits the end of file.
 * @param stream file stream from config file or stdin
 * @param cmd char array holding the command
 * @return bool of true or false if line is reading is successful or unsuccessful
 */
bool getCommand(FILE *stream, char cmd[CMD_LIMIT + 1]) {
  int i = 0;
  cmd[i] = getc(stream);
  while(cmd[i] != EOF) {
    //If I get a command longer than 30 chars I put a space here
    //so I can print invalid command in puzzle.c
    if (i == CMD_LIMIT) {
      cmd[i] = ' ';
    }
    if (i > CMD_LIMIT) {
      skipLine(stream);
      return true;
    }
    if (cmd[i] == '\n') {
      //This fills the array with spaces so we aren't parsing
      //any leftover characters in runCommand
      for (int j = i; j < CMD_LIMIT; j++) {
        cmd[j] = ' ';
      }
      return true;
    }
    i++;
    cmd[i] = getc(stream);
  }
  return false;
}

/**
 * This function will run the given command from getCommand. Returns true upon
 * a valid command and false otherwise.  Puzzle uses this function to execute
 * user commands or commands from the config file.
 * @param cmd the char command array
 * @param rows the number of rows
 * @param cols the number of cols
 * @param board the board of numbers
 * @return true or false depending upon success
 */
bool runCommand(char cmd[CMD_LIMIT], int rows, int cols, int board[][cols]) {
  char command[CMD_LENGTH];
  int tile;
  char left[] = "left";
  char right[] = "right";
  char up[] = "up";
  char down[] = "down";
  char undo[] = "undo";
  char quit[] = "quit";
  if (sscanf(cmd, "%s%d", command, &tile) == 1) {
    if (strcmp(command, undo) != 0 && strcmp(command, quit) != 0) {
      return false;
    }
  }
  if (strcmp(command, left) == 0) {
    if (moveLeft(tile, rows, cols, board)) {
      if (histLen == MAX_HISTORY - 1) {
        moveStack(history);
        sprintf(history[histLen], "%s %d", command, tile);
      } else {
        sprintf(history[histLen], "%s %d", command, tile);
        histLen++;
      }
      return true;
    } else {
      return false;
    }
  } else if (strcmp(command, right) == 0) {
    if (moveRight(tile, rows, cols, board)) {
      if (histLen == MAX_HISTORY - 1) {
        moveStack(history);
        sprintf(history[histLen], "%s %d", command, tile);
      } else {
        sprintf(history[histLen], "%s %d", command, tile);
        histLen++;
      }
      return true;
    } else {
      return false;
    }
  } else if (strcmp(command, down) == 0) {
    if (moveDown(tile, rows, cols, board)) {
      if (histLen == MAX_HISTORY - 1) {
        moveStack(history);
        sprintf(history[histLen], "%s %d", command, tile);
      } else {
        sprintf(history[histLen], "%s %d", command, tile);
        histLen++;
      }
      return true;
    } else {
      return false;
    }
  } else if (strcmp(command, up) == 0) {
    if (moveUp(tile, rows, cols, board)) {
      if (histLen == MAX_HISTORY - 1) {
        moveStack(history);
        sprintf(history[histLen], "%s %d", command, tile);
      } else {
        sprintf(history[histLen], "%s %d", command, tile);
        histLen++; 
      }
      return true;
    } else {
      return false;
    }
  } else if (strcmp(command, undo) == 0) {
    char undoCommand[CMD_LENGTH];
    histLen--;
    if (histLen < 0) {
      histLen++;
      return false;
    }
    char empty[] = "";
    sscanf(history[histLen], "%s%d", undoCommand, &tile);
    strcpy(history[histLen], empty);
    if (strcmp(undoCommand, left) == 0) {
      return moveRight(tile, rows, cols, board);
    } else if (strcmp(undoCommand, right) == 0) {
      return moveLeft(tile, rows, cols, board);
    } else if (strcmp(undoCommand, down) == 0) {  
      return moveUp(tile, rows, cols, board);
    } else {
      return moveDown(tile, rows, cols, board);
    }
  } else if (strcmp(command, quit) == 0) {
    exit(0);
  } else {
    return false;
  }
}
