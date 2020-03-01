//Celem dzialania programu jest przeanalizowanie tekstowego pliku wejsciowego, a nastepnie wyliczenie wyznacznika macierzy, macierzy odwrotnej (przy uzyciu macierzy transponowanej, a nastepnie jej rozwiazanie.
//The purpose of this program is to analyze text input file and calculate the determinant of matrix, create inverted matrix (using transported matrix) and find a solution to it

#include "matrix.h"
#include <stdio.h>


#define FILENAME argv[1]  //argv[1]-allows to open from console
#define _DEBUGMAIN_	   //show result of specified function



void ReadData(FILE* fin, double** pMatrix, double * b, int nDim);// Read data from file (which was opened earlier) and save it in variable, fin - fie, pMatrix - pointer on matrix, b  - constant terms ,  nDim - dimension of matrix  

int main(int argc, const char* argv[])
{
	if (argc != 2)
	{
		printf("Please, give the filename containing matrix\n");
		return -1;
	}
	FILE* fin;


	if ((fin = fopen(FILENAME, "r")) == NULL) //if file doesn't find - return NULLA
	{
		perror("ERROR- can't open file");
	}

	int nDim;//dimension of matrix

	fscanf(fin, "%d", &nDim);// set nDim from file

#ifdef _DEBUGMAIN_


	printf("Dimensions of matrix: \n");
	printf("%dx%d\n", nDim, nDim);
#endif

	double** pMatrix = NULL;
	double* pConstantTerms = NULL;
	double det;	//determinent

	if (!CreateVector(&pConstantTerms, nDim))
	{
		perror("Can't open array containing constant terms");
	}

	if (!CreateMatrix(&pMatrix, nDim))
	{
		perror("Failed to create matrix");
	}

	ReadData(fin, pMatrix, pConstantTerms, nDim);

#ifdef _DEBUGMAIN_
	printf("ORYGINAL MATRIX: \n");
	PrintMatrix(pMatrix, nDim);


	printf("\nConstant terms: \n");
	for (int i = 0; i < nDim; i++)
	{
		printf("[%d] = %f\n", i, pConstantTerms[i]);
	}
#endif

	det = Det(pMatrix, nDim);	//set determinent

#ifdef _DEBUGMAIN_
	printf("\n");
	printf("Determinent: %f\n", det);
#endif

	double** pInv = NULL;	 //array with invirtible matrix
	if (det < 1e-12)//can't create invertible matrix when det = 0 (1e-12 because of double type)
	{
		if (!CreateMatrix(&pInv, nDim))
		{
			perror("Can't create matrix pInv\n");
		}
		InverseMatrix(pInv, pMatrix, nDim, det);

#ifdef _DEBUGMAIN_
		printf("\nINVERTIBLE MATRIX: \n");
		PrintMatrix(pInv, nDim);
#endif

		double* pRes = NULL;//vector with solutions

		if (!CreateVector(&pRes, nDim))
		{
			perror("Can't create vector with solutions\n");
		}

		LayoutEqu(pInv, pConstantTerms, pRes, nDim);

#ifdef _DEBUGMAIN_	
		printf("\nSOLUTIONS: \n");

		for (int i = 0; i < nDim; i++)
		{
			printf("x[%d] = %f\n", i, pRes[i]);
		}
#endif


	}
	else
	{
		printf("Invertible matrix doesn't exists, because determinent is equal to 0\n");
	}



	DeleteMatrix(&pMatrix, nDim);
	DeleteMatrix(&pInv, nDim);
	free(pConstantTerms);

	fclose(fin);
	return 0;
}

void ReadData(FILE* fin, double** pMatrix, double * b, int nDim)
{
	double** pM = pMatrix;
	double* pF = b;

	for (int i = 0; i < nDim; i++, pM++, pF++)
	{
		double* pColumn = *pM;	 //come back to first column of row
		for (int j = 0; j < nDim; j++, pColumn++)
		{
			fscanf(fin, "%lf", pColumn);

		}

		fscanf(fin, "%lf", pF);
	}

}
