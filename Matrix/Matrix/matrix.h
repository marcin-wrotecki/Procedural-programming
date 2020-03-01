#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

int CreateMatrix(double*** pTab, int nSize); // 0 - error 1 - ok  
int CreateVector(double** pTab, int nSize);//creat array of constant terms 
void DeleteMatrix(double*** pTab, int nSize);	//set pointer pTab on NULL
void InverseMatrix(double ** pInv, double** pTab, int nSize, double det);	// pTab- matrix, det-determinant
double Det(double ** pTab, int nSize); // it returns determinant of pTab
void LayoutEqu(double ** pInv, double* pV, double* pRes, int nSize);// pInv-invertible matrix, pV-vector of contanst terms, pRes-solution vector
void PrintMatrix(double** pTab, int nSize);

void TransMatrix(double ** pTab, int nDim); //transform pTab in transition matrix   



#endif
