/*partners: sauye2, cgwang3
 *The purpose of this mp is to create a code that solves a sudoku puzzle by implementing the use of recursive 
 *backtracking. The sudoku puzzle have nine 3x3 zones where a number between 1 to 9 cannot occur more than once 
 *in each 3x3 zone, row, or column of the grid. In this mp, our goal is to create five working functions. By using 
 *the GDB, we were able to debug each part of the code that went wrong. Once everything was verified to be successful 
 *via the "make sudoku#" command, we tested the code with an actual sudoku puzzle from a website and concluded that 
 *the code was successful.
 */

#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int j;                       //j=column
  for(j=0;j<9;j++){            //for loop with changing column checking if value is already in row
      if (val==sudoku[i][j])
      return 1;                //return 1 is val existed
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int i;                       //j=column
  for(i=0;i<9;i++){            //for loop with changing row checking if value is already in column
      if (val==sudoku[i][j])
      return 1;                //return 1 is val existed 
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  //we first check which row and column of the nine 3x3 box its in
  //we then check if it exists in the 3x3 box using for loops
  
  // BEG TODO
  int row;
  int col;
  if (0<=i && i <=2){             //i=row, j=column
    if (0<=j && j<=2)
        for (row=0;row<3;row++){
            for (col=0;col<3;col++){
                if(sudoku[row][col]==val)
                return 1;
            }
            }
  }
  if (0<=i && i <=2){             //i=row, j=column
    if (3<=j && j<=5)
        for (row=0;row<3;row++){
            for (col=3;col<6;col++){
                if(sudoku[row][col]==val)
                return 1;
            }
            }
  }
  if (0<=i && i <=2){             //i=row, j=column
    if (6<=j && j<=8)
        for (row=0;row<3;row++){
            for (col=6;col<9;col++){
                if(sudoku[row][col]==val)
                return 1;
            }
            }
  }
  /////////////////////////////////////////////////////////////////////
  if (3<=i && i <=5){             //i=row, j=column
    if (0<=j && j<=2)
        for (row=3;row<6;row++){
            for (col=0;col<3;col++){
                if(sudoku[row][col]==val)
                return 1;
            }
            }
  }
  if (3<=i && i <=5){             //i=row, j=column
    if (3<=j && j<=5)
        for (row=3;row<6;row++){
            for (col=3;col<6;col++){
                if(sudoku[row][col]==val)
                return 1;
            }
            }
  }
  if (3<=i && i <=5){             //i=row, j=column
    if (6<=j && j<=8)
        for (row=3;row<6;row++){
            for (col=6;col<9;col++){
                if(sudoku[row][col]==val)
                return 1;
            }
            }
  }
  ///////////////////////////////////////////////////////////////////
  if (6<=i && i <=8){             //i=row, j=column
    if (0<=j && j<=2)
        for (row=6;row<9;row++){
            for (col=0;col<3;col++){
                if(sudoku[row][col]==val)
                return 1;
            }
            }
  }
  if (6<=i && i <=8){             //i=row, j=column
    if (3<=j && j<=5)
        for (row=6;row<9;row++){
            for (col=3;col<6;col++){
                if(sudoku[row][col]==val)
                return 1;
            }
            }
  }
    if (6<=i && i <=8){             //i=row, j=column
    if (6<=j && j<=8)
        for (row=6;row<9;row++){
            for (col=6;col<9;col++){
                if(sudoku[row][col]==val)
                return 1;
            }
            }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val,i,sudoku)==1){ //if in row return false
    return 0;
}
  if (is_val_in_col(val,j,sudoku)==1){ //if in column return false
    return 0;
}
  if (is_val_in_3x3_zone(val,i,j,sudoku)==1){ //if in 3x3 return false
    return 0;
}
  else

  return 1;         //if not in a row, column, or a 3x3 box the value is valid
  // END TODO
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
int num;
int i,j;
int r,c;
for (r=0;r<9;r++){                             //check if all cells are assigned numbers
    for (c=0;c<9;c++){
       if(sudoku[r][c]!=0){                    //if all cells are filled, sudoku is finished so return 1 
           return 1;
       }
       else{                                   //if there are still unfilled cells, find an unfilled cell
            for (r=0;r<9;r++){                 //and load row and column values into i and j
                 for (c=0;c<9;c++){
                        if(sudoku[r][c]==0){
                        i=r;
                        j=c;
    }
}

            }
        }
    }
}
for (int num = 1; num <= 9; num++) {          //update values in the sudoku grid if grid is not fully filled
  if(is_val_valid(num,i,j,sudoku)==1){        //if value is valid according to function, update cell with value
        sudoku[i][j] = num;
        if(solve_sudoku(sudoku)){             //this is where the recursive exists by calling itself
            return 1;
        }
        sudoku[i][j] = 0;                     //if the value doesn't work, change cell back to unfilled
    }
}

  return 0;
  // END TODO.
}

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





