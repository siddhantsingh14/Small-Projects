/*
This code functions as a maze solver using a recursive depth-first search.
It solves the maze from start (S) to end (E) by only moving left, down, right, and up.
The code first prints the maze, and the solution maze following it. The *s represent the path of the solution.
Recursive backtracking is used in this program.
It allows us to check each direction and choose a correct path for the solution, if the path checked is wrong, backtracking allows us to undo that path
and check the next one.
*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

int case1=0;  //Setting case1 (First move) for solving the maze to 1 so no error with start is made


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
    maze_t *maze=(maze_t *)malloc(sizeof(maze_t));                //Assigning memory
    char ch;
    FILE *file;                                                   //Setting the start of the file
    file=fopen(fileName,"r") ;                                    //setting file as the formal parameter file in read mode
    if(file==NULL)  return NULL;                                  //If file doesnt exist, then returning NULL
    int height=0;
    int width=0;                                                  //Defining variables height and width
    fscanf(file,"%d %d",&height,&width);                          //Taking in the user input fpr height and width
    maze->height=height;
    maze->width=width;                                           //Assigning the value to the members of object maze
    maze->cells=malloc(sizeof(char*)*height);                    //Assigning memory for the cells in 1D
    int i=0;
    for(i=0; i<width; i++)  maze->cells[i]=malloc(sizeof(char)*width);  //Making a 2D array
    int h=0,w=0;
    for(h=0; h<height; h++){
      for(w=0; w<width; w++){
        ch=fgetc(file);                                         //Taking character by character user input
        if(ch=='\n') ch=fgetc(file);                            //If the inputted character is a new line, then take another input
        maze->cells[h][w]=ch;                                   //Store the user input into the cell 2D array
        if(ch==START){
          maze->startRow=h;
          maze->startColumn=w;                                  //If the User inputs "S", then it is the start and storing the START coordinates into the members of the object
        } //If case START ends
        if(ch==END){
          maze->endRow=h;
          maze->endColumn=w;                                   //If the User inputs "E", then it is the end and storing the END coordinates into the members of the object
        } //If case END ends
      } //for loop h ends
    } //for loop w ends
    return maze;                                               //Returning the maze
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
    // Your code here.
    int m=0;
    for(m=0; m<(maze->height); m++) free(maze->cells[m]);   //Freeing memory used by the object in column major order
    free(maze);                                             //Freeing the memory used by the object
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
    int h=0, w=0;
    for(h=0; h<(maze->height); h++){
      for(w=0; w<(maze->width); w++){
        if((h==maze->startRow) && (w==maze->startColumn)) printf("%c", START);  //Printing "S" if we are at the start of the maze
        else  printf("%c", maze->cells[h][w]);  //Printing the chracter as usual if it is not the start
      } //for loop j ends
      printf("\n"); //Printing a new line as soon as the complete column is printed
    } //for loop i ends
}

/*
 * solveMazeDFS -- recursively solves the maze using depth first search,
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
    if(row>=maze->height||row<0 || col>=maze->width||col<0)   return 0; //If coordinates are not on the maze, then return FALSE
    if(maze->cells[row][col]==WALL||maze->cells[row][col]==PATH||maze->cells[row][col]==VISITED||(maze->cells[row][col]==START && case1!=0))  return 0; //Returning FALSE if the maze is not empty
    case1=1;  //Setting case1 to 1 as first case (First move) has been made
    if((col==maze->endColumn) && (row==maze->endRow)) return 1; //Returning 1 if the END is reached
    if(maze->cells[row][col]!=START)    maze->cells[row][col] = PATH; //Setting the current coordinates as the solution path

    if(solveMazeDFS(maze, col-1, row))  return 1; //Looking left for an empty cell

    if(solveMazeDFS(maze, col, row+1))  return 1; //Looking down for an empty cell

    if(solveMazeDFS(maze, col, row-1))  return 1; //Looking up for an empty cell

    if(solveMazeDFS(maze, col+1, row))  return 1; //Looking right for an empty cell

    if(maze->cells[row][col]!=START)  maze->cells[row][col]=VISITED;  //Assigning VISITED to the current cell and unmarking PATH
    return 0; //Returning 0

}
