/*This code is designed to fill only the non zero elements
of a sparse matrix. We do this by implementing linked lists and
dealing with the tuples within the linked lists and by implementing
functions that ease with this
*/
#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

static sp_tuples_node *pointer;



sp_tuples * load_tuples(char* input_file)
{
  sp_tuples *tuple;
  int row=0;
  int col=0;
  FILE *text;

  tuple=(sp_tuples*)malloc(sizeof(sp_tuples));  //Allocating memory for the file
  text=fopen(input_file,"r"); //Opening the file in read mode

  if (text==NULL) {
    printf("invalid file %s\n", input_file);  //If the file is empty, then return NULL and tell the user that the file is invalid
    return NULL;
  } //if case ends

  fscanf(text,"%d %d",&row, &col);  //Taking input of row and column and adding it in the file

  tuple->m=row;
  tuple->n=col;
  tuple->nz=0;  //Setting values to the data members

  long long int i=0;
  for (i=0; i<(row*col); i++){
    int row_t, col_t;
    double val;
    if(fscanf(text,"%d %d %lf",&row_t, &col_t, &val)==3)  set_tuples(tuple, row_t, col_t, val); //Setting new tuples from the inputs of the user if the user inputs three values
    else  break;
  } //for loop i ends

  fclose(text); //Closing file

  return tuple;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
  sp_tuples_node *tuple;
  int count=0;

  count=mat_t->nz;  //Keeping track of all the non zero entries
  tuple=mat_t->tuples_head; // Setting the value of the head of the linked list

  int i=0;
  for (i=0; i<count; i++) {
    if(row==(tuple->row) && col==(tuple->col)){
      pointer=tuple;
      return tuple->value;
    } //if case ends

    else  tuple=tuple->next;  //Moving to the next tuple
  } //for loop ends

  return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  int count;
  sp_tuples_node **free_tuple, *temp_tuple, *tuple;

  count=mat_t->nz;
  free_tuple=&mat_t->tuples_head;
  tuple=*free_tuple;
  int i=0;

  if(value==0){
    for(i=0; i<count; i++) {
      if(row==tuple->row && col==tuple->col){
        tuple->value=0;
        temp_tuple=tuple;
        tuple=tuple->next;
        *free_tuple=tuple;
        free(temp_tuple);
        count--;
        mat_t->nz=count;
        return;
      } //if case ends
    free_tuple=&tuple->next;
    tuple=*free_tuple;
    } //for loop i ends
  } //else if ends

  else if(count==0){
    tuple=(sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    tuple->row=row;
    tuple->col=col;
    tuple->value=value;
    tuple->next=NULL;
    *free_tuple=tuple;
    count++;
    mat_t->nz=count; //Update nz
    return;
  } //else if ends

  else if(gv_tuples(mat_t, row, col)!=0){
    pointer->value=value;
  } //else if ends

  else if(tuple->row>row || (tuple->row==row && tuple->col>col)){
    temp_tuple=tuple;
    tuple=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    tuple->row=row;
    tuple->col=col;
    tuple->value=value;
    tuple->next=temp_tuple;
    *free_tuple=tuple;
    count++;
    mat_t->nz=count;
    return;
  } //else if ends

  else {
    for (i=0; i<count; i++){
      if(tuple->row>row){
        temp_tuple=tuple;
        tuple=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
        tuple->row=row;
        tuple->col=col;
        tuple->value=value;
        tuple->next=temp_tuple;
        *free_tuple=tuple;
        count++;
        mat_t->nz=count;
        return;
      } //if case ends

      else if(tuple->row==row){
        if(tuple->col<col){
          if(tuple->next!=NULL){
            free_tuple=&tuple->next;
            tuple=*free_tuple;
            continue;
          } //nested if ends
        } //if ends

        else{
          temp_tuple=tuple;
          tuple=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
          tuple->row=row;
          tuple->col=col;
          tuple->value=value;
          tuple->next=temp_tuple;
          *free_tuple=tuple;
          count++;
          mat_t->nz=count;
          return;
        } //else ends
      } //else if ends

      if(tuple->next==NULL) break;

      free_tuple=&tuple->next;
      tuple=*free_tuple;
    } //for loop inside else ends
    temp_tuple=tuple;
    tuple=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    tuple->row=row;
    tuple->col=col;
    tuple->value=value;
    tuple->next=NULL;
    temp_tuple->next=tuple;
    count++;
    mat_t->nz=count;
    return;
    tuple=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    tuple->row=row;
    tuple->col=col;
    tuple->value=value;
    tuple->next=NULL;
    *free_tuple=tuple;
    count++;
    mat_t->nz=count;
    return;
  } //else ends

  return;

}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
  FILE *text;
  sp_tuples_node *tuple;
  text=fopen(file_name, "w"); //Opening the file in write mode
  if(text==NULL){
    printf("invalid file %s\n", file_name); //If the file is empty, then return NULL and tell the user that the file is invalid
    return;
  } //if case ends

  int row=0, col=0, count=0;
  row=mat_t->m;
  col=mat_t->n;
  count=mat_t->nz;
  tuple=mat_t->tuples_head; //Initialising the values of the variables
  fprintf(text, "%d %d\n", row, col);
  int i=0;
  for(i=0; i<count; i++){
    fprintf(text, "%d %d %lf\n",tuple->row, tuple->col, tuple->value );
    tuple=tuple->next;  //Moving onto the next tuple
  } //for loop ends

  fclose(text); //Closing the file

  return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
  long int row=0, col=0;
  long int countA, countB;
  sp_tuples_node * tupleA, *tupleB;
  row=matA->m;
  col=matA->n;
  sp_tuples *tuple=NULL;
  if(row!=matB->m||col!= matB->n) return NULL;

  tuple=(sp_tuples*)malloc(sizeof(sp_tuples));  //Allocating memory to the tuple
  countA=matA->nz;
  tuple->nz=0;
  tuple->m=row;
  tuple->n=col;
  tupleA=matA->tuples_head;
  tupleB=matB->tuples_head;
  countB=matB->nz;  //Setting values to the members and to the variables
  long int i=0;

  for(i=0; i<countA; i++) {
    set_tuples(tuple, tupleA->row, tupleA->col, tupleA->value); //Setting a new tuple
    tupleA=tupleA->next;  //Moving to the next tuple
  } //for loop for tupleA ends

  for (i=0; i<countB; i++) {
    if(gv_tuples(tuple,tupleB->row, tupleB->col)) pointer->value=pointer->value+tupleB->value;  //Adding the values

    else  set_tuples(tuple, tupleB->row, tupleB->col, tupleB->value);

    tupleB=tupleB->next;  //Moving to the next tuple
  } //for loop for tupleB ends

  return tuple;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
  long int countA, countB;
  long int row, col;
  long int temp_col, rowA, colB;
  double val;
  sp_tuples_node *tupleA;
  sp_tuples_node *tupleB;
  sp_tuples_node *temp_tuple;
  sp_tuples *tuple=NULL;
  row= matB->m;
  rowA=matA->m;
  colB=matB->n;
  col= matA->n;
  if(row!=col)  return NULL;
  tuple=(sp_tuples*)malloc(sizeof(sp_tuples));
  tuple->nz=0;
  tuple->m=rowA;
  tuple->n=colB;
  countA=matA->nz;
  countB=matB->nz;
  tupleA= matA->tuples_head;
  tupleB= matB->tuples_head;
  temp_tuple = tupleB;
  long int i=0, j=0;
  for (i=0; i<countA; i++) {
    tupleB= temp_tuple;
    temp_col=tupleA->col;
    for (j=0; j<countB; j++) {
      if (temp_col==tupleB->row) {
        val=gv_tuples(tuple, tupleA->row, tupleB->col)+((tupleA->value) * (tupleB->value)); //Setting the value of val
        set_tuples(tuple, tupleA->row, tupleB->col, val); //Setting a new tuple
      } //if case ends

      else if(temp_col<tupleB->row)  break;

      tupleB=tupleB->next;  //Moving to the next tuple
    } //nested for loop ends

    tupleA=tupleA->next;  //Moving to the next tuple
  } //for loop ends

  return tuple;

}



void destroy_tuples(sp_tuples * mat_t){
  sp_tuples_node* tuple;
  sp_tuples_node* temp_tuple;
  int temp_nz;
  temp_nz=mat_t->nz;
  tuple=mat_t->tuples_head;
  long int i=0;
  for (i=0; i<temp_nz; i++) {
    if(tuple!=NULL){
      temp_tuple=tuple;
      tuple=tuple->next;  //Moving to the next tuple
      free(temp_tuple); //Freeing the memory of the current tuple
    } //if case ends
  } //for loop ends

  return;
}
