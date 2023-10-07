/*partners: sauye2, cgwang3
 *The purpose of this mp is to create a code that solves a maze given a starting and end point with dimensions defined in a file.
 *The code will make use of a recursive function to go through available paths to find the single path that brings you to the end
 *while avoiding previously visited tiles or walls. In order to successfully implement this code, we will need to code the createMaze, 
 *destroyMaze, printMaze, and solveMazeDFS functions. By using the GDB, we were able to debug each part of the code that went wrong. 
 *Once everything was verified to be successful via the "./mp9 tests/maze#.txt" command, we used valgrind to confirm there was no
 *memory leakage and concluded that the code was successful.
 */

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    int i,j;                 //declare all variables used in create maze function
    int width, height;
    int startrow, startcol;
    int endrow, endcol;
    char ** cells;

// check to see if a file can be opened with fopen
FILE * fptr = fopen(fileName, "r");
    if (fptr == NULL) {
        return NULL;
    }
    maze_t * maze_ptr = (maze_t*)malloc(sizeof(maze_t));   //allocate memory size for maze

    // check to see if allocation failed or not
    if (maze_ptr == NULL) {
        return NULL;
    }
    fscanf(fptr, "%d %d\n",&width,&height);            //get dimensions out of file
    cells = (char **)malloc(height*sizeof(char *));

    for (i=0; i<height;i++) {
        cells[i] = (char *)malloc(width * sizeof(char));
    }
    for (i=0;i<height;i++) {
        // go through every column in this row
        for (j=0;j<width;j++) {
            // put the characters read from the file into the array cells
            fscanf(fptr, "%c", &cells[i][j]);

            // if the cell is currently at the start or end of maze, store the location into startcol and startrow
            if (cells[i][j] == START) {
                startrow = i;
                startcol = j;
            }
            if (cells[i][j] == END) {
                endrow=i;
                endcol=j;
            }
        }
        //put the newline into a throwaway variable
        char temp;
        fscanf(fptr, "%c", &temp);
    }

    // fill the struct with the local variables
    
    maze_ptr->width = width; 
    maze_ptr->height = height;
    maze_ptr->startRow = startrow;
    maze_ptr->startColumn = startcol;
    maze_ptr->endRow = endrow;
    maze_ptr->endColumn = endcol;
    maze_ptr->cells = cells;
    fclose(fptr);

    
    return maze_ptr;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    
   //free the rows in the cells, cells, and the maze it self to prevent leakage 
    int i;
    for(i=0;i<maze->height;i++){
        free(maze->cells[i]);
    }
    free(maze->cells);
    free(maze);
    
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    char ** printmaze = maze->cells;

    int i;
    for (i=0;i<maze->height;i++) {
        printf("%s\n",printmaze[i]);      // prints the characters in the cells
    }   
}
/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{

    // Your code here. Make sure to replace following line with your own code.
    if(row<0 || row>=maze->height || col<0 || col>=maze->width){
        return 0;
    }
    if(maze->cells[row][col]==END){
        return 1;
    }

    if(maze->cells[row][col] == PATH || maze->cells[row][col] == WALL){ // check if not a cell, so if its a wall or a path
        return 0;
    }

    if(maze->cells[row][col] !=START){             //you don't want to change "S" or start so set col,row as PATH if its not equal to S
        maze->cells[row][col]=PATH;    
    }
    
    if(solveMazeDFS(maze,col,row+1)){    //solve maze going down
        return 1;
    }

    if(solveMazeDFS(maze,col-1,row)){    //solve maze going left
        return 1;
    }

    if(solveMazeDFS(maze,col+1,row)){    //solve maze going right
        return 1;
    }

    if(solveMazeDFS(maze,col,row-1)){    //solve maze going up
    return 1;
    }

    if(maze->cells[row][col]!=START){          //you don't want to change "S" or start so set col,row as VISITED if its not equal to S
        maze->cells[row][col]=VISITED;
    }

    return 0;    //return false if maze is unsolvable
}
