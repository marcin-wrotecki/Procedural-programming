#ifndef MOVE_H
#define MOVE_H

#include <stdio.h>
#include <cstdio>
#include <stdlib.h>

enum  move { UP, DOWN, LEFT, RIGHT };

int move(int ** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int * py, int** pRoot);// function which make a movement - if movement was correct return 1 else 0
int root(int ** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest);
void setTab(char* sFile, int** pTab, int nRow, int nCol);
void PrintTab(int** pTab, int nRow, int nCol);
int CreateTab(int*** pTab, int nRow, int nCol);

#endif // !MOVE_H
