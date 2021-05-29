#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"

void play();
void insertRandomNumber(int (*grid)[GRID_SIZE]);
int isSolved(int (*grid)[GRID_SIZE]);
int canMove(int (*grid)[GRID_SIZE]);
char selectDirection(int (*grid)[GRID_SIZE]);
int makeMove(int (*grid)[GRID_SIZE], char dir);
int merge(int (*grid)[GRID_SIZE]);
int move(int (*grid)[GRID_SIZE]);
void rotate(int (*grid)[GRID_SIZE]);


void play() {
    int grid[GRID_SIZE][GRID_SIZE];
    
    initGrid(grid);
    insertRandomNumber(grid);
    
    while (!isSolved(grid) && canMove(grid)) {
        print(grid);
        int moved;
        do {
            char dir = selectDirection(grid);
            moved = makeMove(grid, dir);
            if (!moved) printf("Nothing moved. Select another direction.\n");
        } while (!moved);
        if (!isSolved(grid)) insertRandomNumber(grid);
    }
    
    if (isSolved(grid)) {
        printf("Congratulations! You won! :)\n");
        print(grid);
    } else {
        printf("I am sorry. You lost. :(\n");
        print(grid);
    }
}

void insertRandomNumber(int (*grid)[GRID_SIZE]) {
    srand(time(0));
    int num = ((rand() % 2) + 1) * 2;
    int row, col;
    do {
        row = rand() % GRID_SIZE;
        col = rand() % GRID_SIZE;
    } while (grid[row][col] != 0);
    grid[row][col] = num;
}

int isSolved(int (*grid)[GRID_SIZE]) {
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(grid[i][j] == 2048) return 1;
        }
    }
    return 0;
}

int canMove(int (*grid)[GRID_SIZE]) {
    if (!isFull(grid)) return 1;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (i < GRID_SIZE - 1 && grid[i][j] == grid[i+1][j]) return 1;
            if (j < GRID_SIZE - 1 && grid[i][j] == grid[i][j+1]) return 1;
        }
    }
    return 0;
}

char selectDirection(int (*grid)[GRID_SIZE]) {
    int valid;
    char dir;
    do {
        printf("Select direction (w, a, s, d): ");
        fflush(stdin);
        scanf("%c", &dir);
        valid = dir == 'w' || dir == 'a' || dir == 's' || dir == 'd';
        if (!valid) printf("Invalid value. Select again.\n");
    } while (!valid);
    return dir;
}

int makeMove(int (*grid)[GRID_SIZE], char dir) {
    int rotations = 0;
    
    if (dir == 'w') rotations = 3;
    else if (dir == 'd') rotations = 2;
    else if (dir == 's') rotations = 1;
    else if (dir == 'a') rotations = 0;
    
    for (int i = 0; i < rotations; i++) rotate(grid);
    
    int merged = merge(grid);
    int moved = move(grid);
    
    for (int i = 0; i < (4 - rotations) % 4; i++) rotate(grid);
    
    return merged || moved;
}

int merge(int (*grid)[GRID_SIZE]) {
    int merged = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        int positionToMerge = -1;
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != 0) {
                if (positionToMerge == -1) {
                    positionToMerge = j;
                } else if (grid[i][j] == grid[i][positionToMerge]) {
                    grid[i][positionToMerge] *= 2;
                    grid[i][j] = 0;
                    positionToMerge = -1;
                    merged = 1;
                } else {
                    positionToMerge = j;
                }
            }
        }
    }
    return merged;
}

int move(int (*grid)[GRID_SIZE]) {
    int moved = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        int pos = -1;
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != 0) {
                pos++;
                if (pos != j) {
                    grid[i][pos] = grid[i][j];
                    grid[i][j] = 0;
                    moved = 1;
                }
            }
        }
    }
    return moved;
}

void rotate(int (*grid)[GRID_SIZE]) {
    int newGrid[GRID_SIZE][GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            newGrid[i][j] = grid[GRID_SIZE-j-1][i];
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            grid[i][j] = newGrid[i][j];
}

#endif
