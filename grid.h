#ifndef grid_h
#define grid_h

#define GRID_SIZE 4

void initGrid(int (*grid)[GRID_SIZE]);
void print(int (*grid)[GRID_SIZE]);
int isFull(int (*grid)[GRID_SIZE]);

void initGrid(int (*grid)[GRID_SIZE]) {
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            grid[i][j] = 0;
        }
    }
}

void print(int (*grid)[GRID_SIZE]) {
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            printf("%5d", grid[i][j]);
        }
        printf("\n");
    }
}

int isFull(int (*grid)[GRID_SIZE]) {
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(grid[i][j] == 0) return 0;
        }
    }
    return 1;
}

#endif
