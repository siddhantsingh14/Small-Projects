#include "sudoku.h"

/*In this code, we are simulating sudoku.
  We are doing this by chhecking if a value has been entered in the row, the column
  Or the smaller 3x3 matrix inside the bigger 9x9 matrix. We are also checking if the matrix is full
  before try to enter more values. We solve the matrix by a recursion method. If recrusion fails, then we use the backtrack method
  to continue solving it
*/

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
  int ret = 0;  //Initialising return value
  assert(i>=0 && i<9);
  for(int j = 0; j < 9; j++){
      if (val == sudoku[i][j]) ret=1; //if value is in row, then returns 1
  } //for loop ends

  return ret;

} //fn() in_row ends

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
  int ret=0;  //Initialising return value
  assert(j>=0 && j<9);
  for (int i = 0; i < 9; i++){
      if (val == sudoku[i][j])  ret=1;  //if value is in column, then returns 1
  } //for loop ends

  return ret;

} //fn() in_col ends

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]){

  assert(i>=0 && i<9);

  int row=0;
  int col=0;
  int ret=0;
  //determining intial positions
  row = 3*(i/3);
  col = 3*(j/3);

  for (int row_temp = row; row_temp < row + 3; row_temp++){
      for (int col_temp = col; col_temp < col + 3; col_temp++){
          if (val == sudoku[row_temp][col_temp])  ret=1;  //if val is in the current position, then return 1
      } //nested for loop ends
  } //for loop ends
  return ret;

} //fn() 3x3 ends

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  int ret=1;
  //Initialising case values
  int case_row = is_val_in_row(val, i, sudoku);
  int case_col = is_val_in_col(val, j, sudoku);
  int case_matrix = is_val_in_3x3_zone(val, i, j, sudoku);

  if (case_row || case_col || case_matrix) ret=0; //if any case fails, then return 0

  return ret;

} //fn() val_valid ends

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  int i=0;
  int j=0;
  int check_val=1;

  //checking if sudoku is filled with values
  for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
          if(sudoku[i][j] == 0) check_val=0;  //if there is any empty cell, then continue to solve
      } //nested for loops ends
  } //for loops ends

  if (check_val == 1) return 1; //if sudoku is full, then return 1

  else{
      int flag = 0;
      for (i = 0; i < 9; i++){
          for (j = 0; j < 9; j++){
              if(sudoku[i][j] == 0){
                  flag = 1; //setting coordinate for empty cell
                  break;
              } //if case ends
          } //nested for loop ends
          if (flag) break;  //if the cell is empty, break out of the main loop
      } //for loop ends
  } //else case ends

  for (int value = 1; value <= 9; value++) {
      if (is_val_valid(value, i, j, sudoku)) {
          sudoku[i][j] = value; //fill in the empty cells
          if (solve_sudoku(sudoku)) return 1; //if recursion works, then return 1
          else sudoku[i][j] = 0; //if recursion fails, then backtrack
      } //if case ends
  } //for loop ends

  return 0;

} //fn() solve_sudoku ends

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
