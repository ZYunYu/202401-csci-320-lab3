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


// check rows
void* check_row(void* arg) {
    param_struct* params = (param_struct*)arg;
    int row = params->starting_row;
    int seen[10] = {0};

    for (int j = 0; j < 9; j++) {
        int num = sudoku_board[row][j];
        if (num < 1 || num > 9 || seen[num]) {
            return (void*)0;
        }
        seen[num] = 1;
    }
    return (void*)1;
}

// check columns
void* check_col(void* arg) {
    param_struct* params = (param_struct*)arg;
    int col = params->starting_col;
    int seen[10] = {0};

    for (int i = 0; i < 9; i++) {
        int num = sudoku_board[i][col];
        if (num < 1 || num > 9 || seen[num]) {
            return (void*)0;
        }
        seen[num] = 1;
    }
    return (void*)1;
}

// check cubes
void* check_cubes(void* arg) {
    param_struct* params = (param_struct*)arg;
    int startRow = params->starting_row;
    int startCol = params->starting_col;
    int seen[10] = {0};

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            int num = sudoku_board[i][j];
            if (num < 1 || num > 9 || seen[num]) {
                return (void*)0;
            }
            seen[num] = 1;
        }
    }
    return (void*)1;
}


// is_board_valid 
int is_board_valid(){
    int num_of_threads = 27; 
    pthread_t* tid = malloc(sizeof(pthread_t) * num_of_threads);
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    param_struct* params = malloc(sizeof(param_struct) * num_of_threads);

    for(int i = 0; i < 9; i++){
        params[i].starting_row = i;
        pthread_create(&tid[i], &attr, check_row, &params[i]);
    }

    for(int i = 0; i < 9; i++){
        params[i + 9].starting_col = i;
        pthread_create(&tid[i + 9], &attr, check_col, &params[i + 9]);
    }

    for(int i = 0; i < 9; i++){
        params[i + 18].starting_row = (i / 3) * 3;
        params[i + 18].starting_col = (i % 3) * 3;
        pthread_create(&tid[i + 18], &attr, check_cubes, &params[i + 18]);
    }

    int valid = 1;
    for (int i = 0; i < num_of_threads; i++) {
        void* result;
        pthread_join(tid[i], &result);
        if (result == (void*)0) {
            valid = 0;
            break;
        }
    }

    free(params);
    free(tid);
    pthread_attr_destroy(&attr);

    return valid;
}


    

