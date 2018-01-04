/**
  @file board.c
  @author David Lovato, dalovato
  This file will handle all the board printing and manipulations.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define DEFAULT_COLS 7

//static void printSuccess(int, int, int[][DEFAULT_COLS]);

/**
 * This function will initialize the board with the values given to it for the
 * number of rows and columns.  It will initialize it in the solved state, with
 * all the numbers in order from 1 to the highest number.
 * @param rows the number of rows
 * @param cols the number of columns
 * @param board[][cols] the empty array (5x7 default)
 */
void initBoard(int rows, int cols, int board[][cols]) {
  int current = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      board[i][j] = current;
      current++;
    }
  }
}

/**
 * This is an internal method for printing the board in blue when it
 * has been solved.
 * @param rows number of rows
 * @param cols number of cols
 * @param board[][cols] the array given
 */
static void printSuccess(int rows, int cols, int board[][cols]) {
  printf("\e[34m");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%3d ", board[i][j]);
    }
    printf("\n");
  }
  printf("\e[0m");
}

/**
 * This function will print the board initially as well as after every move.
 * It will print the board with all the numbers spaced by 3 spaces, and it will
 * print it blue if the board has been solved, meaning all the numbers are in
 * order from 1 to the highest number.
 * @param rows the number of rows
 * @param cols the number of columns
 * @param board[][cols] the empty array (5x7 default)
 */
void printBoard(int rows, int cols, int board[][cols]) {
  bool inOrder = true;
  int previous = board[0][0];
  int current = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      current = board[i][j];
      if (i == 0 && j == 0) {
        current = board[0][1];
      }
      if (current - previous != 1) {
        inOrder = false;
      }
      previous = board[i][j];
    }
  }
  if (inOrder) {
    printSuccess(rows, cols, board);
  } else {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        printf("%3d ", board[i][j]);
      }
      printf("\n");
    }
  }
}


/**
 * This function is used to find the row and column of a particular value in the
 * array, returning true upon finding the value and false if it's not there.
 * @param tile the value we are looking for
 * @param rows the number of rows
 * @param cols the number of columns
 * @param board[][cols] the initial array
 * @param *r the pointer to the row (pass-by-reference)
 * @param *c the pointer to the column (pass-by-reference)
 * @return bool of true, or returns false if the value is not found
 */
static bool findTile(int tile, int rows, int cols, int board[][cols], int *r, int *c) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (board[i][j] == tile) {
        *r = i;
        *c = j;
        return true;
      }
    }
  }
  return false;
}

/**
 * This function will move all the numbers in the column containing the
 * specified value up one place
 * @param tile the tile we are looking to move
 * @param rows the number of rows
 * @param cols the number of cols
 * @param board[][cols] the initial array
 * @return bool true if it can be done, false if not
 */
bool moveUp(int tile, int rows, int cols, int board[][cols]) {
  int r = rows;
  int c = cols;
  int *cp = &c;
  if (findTile(tile, rows, cols, board, &r, &c)) {
    int tileCol = *cp;
    int temp = board[0][tileCol];
    for (int i = 0; i < rows - 1; i++) {
      board[i][tileCol] = board[i + 1][tileCol];
    }
    board[rows - 1][tileCol] = temp;
    return true;
  } else {
    return false;
  }
}

/**
 * This function will move all the numbers in the column containing the
 * specified value down one place
 * @param tile the tile we are looking to move
 * @param rows the number of rows
 * @param cols the number of cols
 * @param board[][cols] the initial array
 * @return bool true if it can be done, false if not
 */
bool moveDown(int tile, int rows, int cols, int board[][cols]) {
  int r = rows;
  int c = cols;
  int *cp = &c;
  if (findTile(tile, rows, cols, board, &r, &c)) {
    int tileCol = *cp;
    int temp = board[rows - 1][tileCol];
    for (int i = rows - 1; i > 0; i--) {
      board[i][tileCol] = board[i - 1][tileCol];
    }
    board[0][tileCol] = temp;
    return true;
  } else {
    return false;
  }
}

/**
 * This function will move all the numbers in the row containing the
 * specified value right one place
 * @param tile the tile we are looking to move
 * @param rows the number of rows
 * @param cols the number of cols
 * @param board[][cols] the initial array
 * @return bool true if it can be done, false if not
 */
bool moveRight(int tile, int rows, int cols, int board[][cols]) {
  int r = rows;
  int c = cols;
  int *rp = &r;
  if (findTile(tile, rows, cols, board, &r, &c)) {
    int tileRow = *rp;
    int temp = board[tileRow][cols - 1];
    for (int i = cols - 1; i > 0; i--) {
      board[tileRow][i] = board[tileRow][i-1];
    }
    board[tileRow][0] = temp;
    return true;
  } else {
    return false;
  }
}

/**
 * This function will move all the numbers in the row containing the
 * specified value left one place
 * @param tile the tile we are looking to move
 * @param rows the number of rows
 * @param cols the number of cols
 * @param board[][cols] the initial array
 * @return bool true if it can be done, false if not
 */
bool moveLeft(int tile, int rows, int cols, int board[][cols]) {
  int r = rows;
  int c = cols;
  int *rp = &r;
  if (findTile(tile, rows, cols, board, &r, &c)) {
    int tileRow = *rp;
    int temp = board[tileRow][0];
    for (int i = 0; i < cols - 1; i++) {
      board[tileRow][i] = board[tileRow][i+1];
    }
    board[tileRow][cols - 1] = temp;
    return true;
  } else {
    return false;
  }
}
