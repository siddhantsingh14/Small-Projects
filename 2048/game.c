#include "game.h"
/*
This program is designed to simulate the game 2048 by using 1D arrays
We accomplish this by by creating different movement functions for w,a,s,d
After each move, it is checked if it is a legal move, if it is not, then it will not execute
the move. If the same tiles are moved into one another, then they will add up.
The game goes on till there are no more legal moves left.
*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows=rows;
    mygame->cols=cols;
    mygame->score=0;
    for(int i=0; i<rows; i++){
      for(int j=0; j<cols; j++){
        mygame->cells[i*cols+j]=-1; //Setting cells to empty(-1)
      }
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any
	memory previously allocated is not lost in this function.
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
   (*_cur_game_ptr)->rows=new_rows;
   (*_cur_game_ptr)->cols=new_cols;
   (*_cur_game_ptr)->score=0;

   for (int i=0; i<new_rows; i++) {
       for (int j=0; j<new_cols; j++) {
           (*_cur_game_ptr)->cells[i*new_cols+j]=-1;  //Re-initializing cells to empty
       }
   }


	return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE

    if ((row<(cur_game->rows) && row>=0) && (col<(cur_game->cols) && col>=0)) //checking if the current point is within the board
      return &cur_game->cells[row*(cur_game->cols)+col]; //Returning the pointer to the corresponding point on the board

    else  return NULL;  //Returning NULL since position is out of bounds
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
    //YOUR CODE STARTS HERE
    int empty=0;
    int combine_row=0;
    int col=cur_game->cols;
    int row=cur_game->rows;
    int flag=0;

    for(int j=0; j<col; j++) {
         combine_row=-1; // Resetting the value of combine_row for each column
        for(int i=0; i<row; i++) {
            if(cur_game->cells[i*col+j]!=-1) {
                empty=i;
                int temp=i-1; //temp tells us where to begin checking where the empty cells are
                for(int temp_row=temp; temp_row>=0; temp_row--) {
                    if(cur_game->cells[(temp_row)*col+j]==-1)  empty=temp_row;  //Checking what is the last empty cell
                } //for loop temp_row ends

                if (empty!=i) {
                    cur_game->cells[empty*col+j]=cur_game->cells[i*col+j];  //copying the current element into the empty cell (sliding up)
                    cur_game->cells[i*col+j]=-1; //clearing the current cell
                    flag++;
                } //if case for checking empty and i ends

                if ((empty-1)!=combine_row){
                    if (cur_game->cells[(empty-1)*col+j]==cur_game->cells[empty*col+j]){  //checking if the top cell is the same as the current cell
                        cur_game->cells[(empty-1)*col+j]=2*cur_game->cells[empty*col+j];  //Adding the two sums into top cell
                        cur_game->cells[empty*col+j]=-1;  //clearing the current cell
                        combine_row=empty-1;
                        flag++;
                        cur_game->score+=cur_game->cells[(empty-1)*col+j]; //updating the score
                    } //if case to check same elements ends
                } //if case for checking if the combined row is the same as the empty row ends
            } //if case for checking non empty cells ends
        } //for loop row(i) ends
    } //for loop col(j) ends

    if (flag == 0)  return 0;

    return 1;
};  //fn() ends

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int empty=0;
    int combine_row=0;
    int col=cur_game->cols;
    int row=cur_game->rows;
    int flag=0;

    for(int j=0; j<col; j++) {
        combine_row=row+1; // Resetting the value of combine_row for each column
        for(int i=row-1; i>=0; i--) {
            if(cur_game->cells[i*col+j]!=-1) {
                empty=i;
                int temp=i+1; //temp tells us where to begin checking where the empty cells are
                for(int temp_row=temp; temp_row<row; temp_row++) {
                    if(cur_game->cells[(temp_row)*col+j]==-1)  empty=temp_row;  //Checking what is the last empty cell
                } //for loop temp_row ends

                if (empty!=i) {
                    cur_game->cells[empty*col+j]=cur_game->cells[i*col+j];  //copying the current element into the empty cell (sliding up)
                    cur_game->cells[i*col+j]=-1; //clearing the current cell
                    flag++;
                } //if case for checking empty and i ends

                if ((empty+1)!=combine_row){
                    if (cur_game->cells[(empty+1)*col+j]==cur_game->cells[empty*col+j]){  //checking if the top cell is the same as the current cell
                        cur_game->cells[(empty+1)*col+j]=2*cur_game->cells[empty*col+j];  //Adding the two sums into top cell
                        cur_game->cells[empty*col+j]=-1;  //clearing the current cell
                        combine_row=empty+1;
                        flag++;
                        cur_game->score+=cur_game->cells[(empty+1)*col+j]; //updating the score
                    } //if case to check same elements ends
                } //if case for checking if the combined row is the same as the empty row ends
            } //if case for checking non empty cells ends
        } //for loop row(i) ends
    } //for loop col(j) ends

    if (flag == 0)  return 0;

    return 1;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int empty=0;
    int combine_col=0;
    int col=cur_game->cols;
    int row=cur_game->rows;
    int flag=0;

    for(int i=0; i<row; i++) {
        combine_col=-1; // Resetting the value of combine_col for each column
        for(int j=0; j<col; j++) {
            if(cur_game->cells[i*col+j]!=-1) {
                empty=j;
                int temp=j-1; //temp tells us where to begin checking where the empty cells are
                for(int temp_col=temp; temp_col>=0; temp_col--) {
                    if(cur_game->cells[i*col+temp_col]==-1)  empty=temp_col;  //Checking what is the last empty cell
                } //for loop temp_col ends

                if (empty!=j) {
                    cur_game->cells[i*col+empty]=cur_game->cells[i*col+j];  //copying the current element into the empty cell (sliding up)
                    cur_game->cells[i*col+j]=-1; //clearing the current cell
                    flag++;
                } //if case for checking empty and j ends

                if ((empty-1)!=combine_col){
                    if (cur_game->cells[i*col+(empty-1)]==cur_game->cells[i*col+empty]){  //checking if the top cell is the same as the current cell
                        cur_game->cells[i*col+(empty-1)]=2*cur_game->cells[i*col+empty];  //Adding the two sums into top cell
                        cur_game->cells[i*col+empty]=-1;  //clearing the current cell
                        combine_col=empty-1;
                        flag++;
                        cur_game->score+=cur_game->cells[i*col+(empty-1)]; //updating the score
                    } //if case to check same elements ends
                } //if case for checking if the combined row is the same as the empty row ends
            } //if case for checking non empty cells ends
        } //for loop col(j) ends
    } //for loop row(i) ends

    if (flag == 0)  return 0;

    return 1;

};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int empty=0;
    int combine_col=0;
    int col=cur_game->cols;
    int row=cur_game->rows;
    int flag=0;

    for(int i=0; i<row; i++) {
        combine_col=col+1; // Resetting the value of combine_col for each column
        for(int j=col-1; j>=0; j--) {
            if(cur_game->cells[i*col+j]!=-1) {
                empty=j;
                int temp=j+1; //temp tells us where to begin checking where the empty cells are
                for(int temp_col=temp; temp_col<col; temp_col++) {
                    if(cur_game->cells[i*col+temp_col]==-1)  empty=temp_col;  //Checking what is the last empty cell
                } //for loop temp_col ends

                if (empty!=j) {
                    cur_game->cells[i*col+empty]=cur_game->cells[i*col+j];  //copying the current element into the empty cell (sliding up)
                    cur_game->cells[i*col+j]=-1; //clearing the current cell
                    flag++;
                } //if case for checking empty and j ends

                if ((empty+1)!=combine_col){
                    if (cur_game->cells[i*col+(empty+1)]==cur_game->cells[i*col+empty]){  //checking if the top cell is the same as the current cell
                        cur_game->cells[i*col+(empty+1)]=2*cur_game->cells[i*col+empty];  //Adding the two sums into top cell
                        cur_game->cells[i*col+empty]=-1;  //clearing the current cell
                        combine_col=empty+1;
                        flag++;
                        cur_game->score+=cur_game->cells[i*col+(empty+1)]; //updating the score
                    } //if case to check same elements ends
                } //if case for checking if the combined col is the same as the empty col ends
            } //if case for checking non empty cells ends
        } //for loop col(j) ends
    } //for loop row(i) ends

    if (flag == 0)  return 0;

    return 1;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    int count=0;
    int sameneighbor=0;
    int row=cur_game->rows;
    int col=cur_game->cols;
    int cases=1;

    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            int temp_i=0, temp_j=0;
            if(cur_game->cells[i*col+j] == -1) count++;  //Empty cell

            switch(cases){
              case 1:{  //Top neighbor
                temp_i=i-1;
                temp_j=j;
                if ((temp_i>=0 && temp_i<row) && (temp_j>=0 &&temp_j<col)) {
                    if (cur_game->cells[temp_i*col+temp_j]==cur_game->cells[i*col+j]) sameneighbor++; //If the current cell and the neighbor have same value
                } //outer if case ends
              } //case 1 ends

              case 2:{  //Left neighbor
                temp_i=i;
                temp_j=j-1;
                if ((temp_i>=0 && temp_i<row) && (temp_j>=0 &&temp_j<col)) {
                    if (cur_game->cells[temp_i*col+temp_j]==cur_game->cells[i*col+j]) sameneighbor++; //If the current cell and the neighbor have same value
                } //outer if case ends
              } //case 2 ends

              case 3:{  //Right neighbor
                temp_i=i;
                temp_j=j+1;
                if ((temp_i>=0 && temp_i<row) && (temp_j>=0 &&temp_j<col)) {
                    if (cur_game->cells[temp_i*col+temp_j]==cur_game->cells[i*col+j]) sameneighbor++; //If the current cell and the neighbor have same value
                } //outer if case ends
              } //case 3 ends

              case 4:{  //Bottom neighbor
                temp_i=i+1;
                temp_j=j;
                if ((temp_i>=0 && temp_i<row) && (temp_j>=0 &&temp_j<col)) {
                    if (cur_game->cells[temp_i*col+temp_j]==cur_game->cells[i*col+j]) sameneighbor++; //If the current cell and the neighbor have same value
                } //outer if case ends
              } //case 4 ends
            } //switch case ends
        } //for loop j ends
    } //for loop i ends

    if (count==0 && sameneighbor==0)  return 0; //There are no empty cells and no neighbors

    else  return 1; //The move is legal
} //fn() ends


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{

	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }


	//check for an empty cell
	int emptycheck = 0;
	int i;

	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}

    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;

	printf("\n\n\nscore:%d\n",cur_game->score);


	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char


    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }

	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char

    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;

    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}

		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		}

		remake_game(&cur_game,rows,cols);

		move_success = 1;

    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }




    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
		 print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
