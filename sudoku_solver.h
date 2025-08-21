#ifndef SOLVER_H
#define SOLVER_H

const int GRID_SIZE = 5;

bool isValid(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num);
bool solveSudoku(int grid[GRID_SIZE][GRID_SIZE]);

#endif
