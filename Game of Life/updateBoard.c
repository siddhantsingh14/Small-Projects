/* This program is designed to simulate the game of life,
we have coded three functions that help in the game.
the first function helps calculating the number of live neighbours by checking all the elements around the current element.
If the surrounding element is on the board, then it checks if it live or dead.
To update the board, it copies the board into a temp board and then uses the rules to see if the element should be alive or dead.
To cehck if the board has changed or not, it copies it into a temporary board again, and then it updates the board again to see if there are any changes in the next
step or not */


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
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
	int count = 0;

	//test cases for the neighbours start
	for(int row_test=row-1; row_test<=row+1; row_test++){
			for(int col_test=col-1; col_test<=col+1; col_test++){
				if(row_test==row && col_test==col)	continue;	//if it is testing the location of actual position, then skip
				if ((row_test >= 0) && (row_test < boardRowSize)){
					if((col_test) >= 0 && (col_test < boardColSize)){
						if(board[(row_test*boardColSize) + col_test]==1)	count++;	//Incrementing the live neightbour count if element is 1
					}	//if condition for col_test ends
				}	//if condition for row_test ends
			}	//for loop col_test ends
	}	//for loop row_test ends

	return count;

}//fn countliveneighbour() ends




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
	int temp_board[boardRowSize*boardColSize];
	int neighbours = 0;
	for(int row_temp=0; row_temp<boardRowSize; row_temp++){
		for(int col_temp=0; col_temp<boardColSize; col_temp++){
			temp_board[(row_temp*boardColSize)+col_temp]=board[(row_temp*boardColSize)+col_temp]; //copying the game board into a temporary board
		}	//for loop for col_temp ends
	}	//for loop for row_temp ends

	for(int row=0; row<boardRowSize; row++){
		for(int col=0; col<boardColSize; col++){
			neighbours = countLiveNeighbor(temp_board, boardRowSize, boardColSize, row, col);
			if(temp_board[(row*boardColSize)+col]==1){
				switch (neighbours){
					case 2:{
						board[(row*boardColSize)+col] = 1;	//lives
						break;
					}	//case 2 live neighbours ends
					case 3:{
						board[(row*boardColSize)+col] = 1;	//lives
						break;
					}	//case 3 live neighbours ends
					default:{
						board[(row*boardColSize)+col] = 0;	//dies
					}	//case if more than 3 live neighbours or fewer than 2 live neighbours ends
				}	//switch case ends
			}	//if current element is 1 ends
			else{
				switch(neighbours){
					case 3:{
						board[(row*boardColSize)+col] = 1;	//becomes alive
						break;
					}	//case 3 live neighbours ends
					default: {
						board[(row*boardColSize)+col] = 0;	//stays dead
					}	//any other live/dead neighbours ends
				}	//switch case ends
			}// if current element is 0 ends
		}	//for loop for col_temp ends
	}	//for loop for row_temp ends

}	//fn updateboard() ends

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game boarfor (i = 0; i < boardRowSize; i++) {
		for (j = 0; j < boardColSize; j++) {
			if (board[i*boardColSize+j] != temp[i*boardColSize+j]){
				return 0;
			}
		}
	}d.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){
	int temp_board[boardRowSize*boardColSize];
	int flag = 1;
	for(int row_temp=0; row_temp<boardRowSize; row_temp++){
		for(int col_temp=0; col_temp<boardColSize; col_temp++){
			temp_board[(row_temp*boardColSize)+col_temp]=board[(row_temp*boardColSize)+col_temp]; //copying the game board into a temporary board
		}	//for loop for col_temp ends
	}	//for loop for row_temp ends

	updateBoard(temp_board, boardRowSize, boardColSize);

	for (int row = 0; row < boardRowSize; row++) {
		for (int col = 0; col < boardColSize; col++) {
			if (board[(row*boardColSize)+col] != temp_board[(row*boardColSize)+col])	flag=0;	//checking if the current board is the same
		}	//for loop for col ends
	}	//for loop for row ends

	return flag;
}	//fn alivestable() ends
