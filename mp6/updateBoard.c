/*partners: sauye2, cgwang3
 *The purpose of this code is to create a "Game of Life" simulation using a game board that is represented
 *by a one-dimensional array. In order to get this code to work, we have to implement a functional code into
 *the countLiveNeighbor, updateBoard, and aliveStable functions. By using the GDB, we were able to debug each
 *part of the code that went wrong. Once everything was verified to be successful via the "./test" command,
 *we tested the code with the life.dat test cases provided.
 */
 

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cell/s, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
int live = 0;
int testRow, testCol;
for(testRow=row-1;testRow<row+2;testRow++){ // rows from one below to one above
    if(testRow >= 0 && testRow <= boardRowSize-1) // check if the test row is in the array
        for(testCol=col-1;testCol<col+2;testCol++){ // columns from one below to one above
            if(testCol >= 0 && testCol <= boardColSize-1) // check if the test col is in the array
                if (testRow != row || testCol != col)        //if the cell isn't at (row,col)
                    if (board[boardColSize*testRow+testCol] == 1) //and if the cell is alive
                    live=live+1;                                     //increment the number of live neighbors
                    
        }
    }
return live;         //return number of live neighbors
}


/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {

int i,row,col;
int board2[boardRowSize*boardColSize];    //create a temporary array to store the values of the next step

for(row=0;row<boardRowSize;row++){
    for(col=0;col<boardColSize;col++){
    i=row*boardColSize+col;               //calculate the cell number we are checking
    int livecount = countLiveNeighbor(board,boardRowSize,boardColSize,row,col);    //calculate number of live neighbors
    if(livecount==3)                      //if there are 3 live neighbors, cell is alive
    board2[i]=1;
    else if(livecount<2 || livecount>3)    //if there are less than 2 or more than 3 live neighbors, cell is dead
    board2[i]=0;
    else{
        board2[i]=board[i];                //otherwise,cell stays the same as before
}
}
}
//load the values of all the cells in the temporary array to the gameboard
int j;
for (j=0; j<boardRowSize*boardColSize; j++){
    board[j]=board2[j];
}
}
/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  int i,row,col;
for(i=0;i<boardRowSize*boardColSize;i++){         //calculate the row and column of each cell we are checking
    row = (i)/boardColSize;
    col = (i) % boardColSize;
    int livecount = countLiveNeighbor(board,boardRowSize,boardColSize,row,col);    //calculate number of live neighbors
    if((livecount==3 || livecount==2) && board[i]==1)             //if number of live neighbors is 3 or 2, and the cell is alive, nothing changes
      continue;
    if(livecount!=3 && board[i]==0)                               //if the number of live neighbors is not 3 and the cell is dead, nothing changes
      continue;
    else
        return 0;                                                 //if these conditions are not true, alive cells have changed so return 0
 }
 return 1;                                                        //return 1 if the alive cells are the same for current and next step


}

				
			

