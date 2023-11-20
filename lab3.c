#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "lab3.h"

extern int** sudoku_board;
int* worker_validation;

int** read_board_from_file(char* filename){
    FILE *fp = fopen(filename, "r");

    int** board = malloc(sizeof(int*) * 9);
    for(int i = 0; i < 9; i++){
        board[i] = malloc(sizeof(int) * 9);
        for (int j = 0; j < 9; j++){
            board[i][j] = 0;
        }
    }
    
    fclose(fp);
    return board;
}


int is_board_valid(){
    pthread_t* tid;  /* the thread identifiers */
    pthread_attr_t attr;
    param_struct* parameter;
    
    // replace this comment with your code
    
}
