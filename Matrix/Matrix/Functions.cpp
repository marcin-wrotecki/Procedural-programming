#include "matrix.h"

//#define _DEBUG_		  //show stages of calculations


void Complement(double** pTabOut, double** pTabIn, int nRow, int nCol, int nDim);
void ComplMatrix(double ** pTabD, double ** pTab, int nDim);  //functions which are using to count complement matrix from pTab


int CreateMatrix(double*** pTab, int nSize)
{
	double** p = *pTab = (double**)malloc(sizeof(double*)*nSize); 	 //allocation memory for rows
	 //**p means number of row - pointer which allows to move by rows
	if (!(*pTab))//*p number of column -  pointer which allows to move by rows
	{
		perror("ERROR-WRONG MEMORY ALLOCATION!!!");
		return 0;
	}

	for (int i = 0; i < nSize; i++, p++) // allocate memory for row
	{
		*p = (double*)malloc(sizeof(double)*nSize);
		if (!(*p))
		{
			perror("ERROR-WRONG MEMORY ALLOCATION!!!");
			return 0;
		}
		memset(*p, 0, sizeof(double)*nSize);
	}
	return 1;
}

int CreateVector(double** pTab, int nSize)
{
	*pTab = (double*)malloc(sizeof(double)*nSize);
	if (!(*pTab))
	{
		perror("ERROR-WRONG MEMORY ALLOCATION!!!");
		return 0;
	}
	memset(*pTab, 0, sizeof(double)*nSize);
	return 1;

}


void DeleteMatrix(double*** pTab, int nSize)// *** we want to get oryginal 
{
	double ** pRow = *pTab;
	for (int i = 0; i < nSize; i++, pRow++)
	{
		free(*pRow);// free each row
	}
	*pTab = NULL;

}

void InverseMatrix(double ** pInv, double** pTab, int nSize, double det)
{
	double** pMatrixD;//complement matrix


	if (!CreateMatrix(&pMatrixD, nSize))
	{
		perror("Can't create complement matrix");
	}

	ComplMatrix(pMatrixD, pTab, nSize);
	TransMatrix(pMatrixD, nSize);


	for (int i = 0; i < nSize; i++)
	{
		double* pColumn = *pMatrixD++;
		double* pColumn2 = *pInv++;
		for (int j = 0; j < nSize; j++)
		{
			*pColumn2++ = *pColumn++ / det;
		}


	}

}

double Det(double ** pTab, int nSize)
{
	int nCol = 0;//column for which we count determinent
	int nRow = 0;//row for which we count det 
	if (nSize == 1) return **pTab;//if matrix has one element -> it is it det
	else if (nSize == 2)
	{
#ifdef	_DEBUG_
		printf("\n");
		PrintMatrix(pTab, nSize);
#endif
		return **pTab * pTab[1][1] - pTab[0][1] * pTab[1][0]; //determinent of two dimension matrix
	}
	else
	{

		double det = 0;
		double* first = *pTab;//first element

		int m = 1;

		double** pTabO = NULL;	 //it is temporary array where it is saved matrix after detele specific row and column

		if (!CreateMatrix(&pTabO, nSize - 1))//nSize-1 - because we delete one column and row
		{
			perror("Can't create matrix (det function)\n");
		}

		for (int i = 0; i < nSize; i++)
		{
			Complement(pTabO, pTab, nRow, i, nSize);//create matrix after delete nRow and nCol
			det += *first++*Det(pTabO, nSize - 1)*m;
			m = -m;
		}

#ifdef	_DEBUG_
		printf("\n");
		PrintMatrix(pTab, nSize);
#endif

		DeleteMatrix(&pTabO, (nSize - 1));
		return det;
	}
}

void LayoutEqu(double ** pInv, double* pV, double* pRes, int nSize)
{

	for (int i = 0; i < nSize; i++, pRes++)
	{
		double* pColumn = *pInv++;//indicate first element of row
		double* pConstantTerms = pV;  //come back to beginning 
		for (int j = 0; j < nSize; j++)
		{
			*pRes += (*pColumn)*(*pConstantTerms); //multiply by element of column and constant terms
			pColumn++;
			pConstantTerms++;
		}

	}

}

void PrintMatrix(double** pTab, int nSize)
{

	for (int i = 0; i < nSize; i++)
	{
		double* pColumn = *pTab++;//it allows to switch columns in row

		for (int j = 0; j < nSize; j++, pColumn++)
		{
			printf("%lf\t", *pColumn);
		}

		printf("\n");
	}
}

void Complement(double** pTabOut, double** pTabIn, int nRow, int nCol, int nDim)
{

	for (int i = 0; i < nDim; i++, pTabIn++)
	{
		if (i == nRow) 	 //nRow - is row to delete
		{
			continue;
		}
		double* pColumn = *pTabIn;
		double* pColumn2 = *pTabOut++;

		for (int j = 0; j < nDim; j++, pColumn++)
		{
			if (j == nCol)		//nCol - is column to delete
			{
				continue;
			}
			*pColumn2++ = *pColumn; //set element from pTabIn to pTabOut

		}

	}
}

void ComplMatrix(double ** pTabD, double ** pTab, int nDim)
{

	double** pTempTab = NULL;//array where are saved matrix after delete specified column
	int m = 1;

	if (!CreateMatrix(&pTempTab, nDim - 1))//nDim -1 -> because we delete column and row
	{
		perror("Can't create temporary matrix (ComplMatrix function)\n");
	}


	for (int i = 0; i < nDim; i++, pTabD++)
	{

		double* pColumn = *pTabD;
		double m = (i % 2) ? -1 : 1;
		for (int j = 0; j < nDim; j++, pColumn++)
		{
			Complement(pTempTab, pTab, i, j, nDim);

#ifdef _DEBUG_
			printf("\nMatrix: \n");
			PrintMatrix(pTempTab, nDim - 1);
			printf("\n");
			printf("\nDeterminent : %f", Det(pTempTab, nDim - 1));
#endif
			*pColumn = Det(pTempTab, nDim - 1)*m;
			m = -m;

		}

	}


}

void TransMatrix(double ** pTab, int nDim)
{
	double** pRow = pTab;

	for (int i = 0; i < nDim - 1; i++)
	{
		double* pColumn = *pRow++ + i + 1;
		for (int j = i + 1; j < nDim; j++)
		{
			double  temp = *pColumn; //pTab[i][j]
			*pColumn++ = pTab[j][i];
			pTab[j][i] = temp;
		}
	}


}










/*	   old version of det function
double Det( double ** pTab, int nSize )
{
double** pTemp = NULL;//tablica pomocnicza, sa w niej zapisane macierze po wycieciu kolumny


  if( !CreateMatrix( &pTemp, nSize ) )
  {
	  perror( "Nie udalo sie utworzyc macierzy" );
  }

  pTemp = pTab;


  int nCol = 0;//kolumna wzgledem ktorej liczymy det
  if( nSize == 1 ) return **pTab;
  else if( nSize == 2 )
  {
#ifdef	_DEBUG_
		printf( "\n" );
		PrintMatrix( pTab, nSize );
#endif
		return pTab[0][0] * pTab[1][1] - pTab[0][1] * pTab[1][0];
	}
	else
	{
		double det = **pTab;
		double temp;




		for( int i = 1; i < nSize; i++ )
		{
			double** pRow = pTab;
			double first = **pRow;
			double* pColumn = *pRow;


			pColumn = *pRow;
			pColumn += i;
			if( first != 0 )temp = *pColumn / first;
			else
				temp = -1;

			for( int j = 0; j < nSize; j++ )
			{
				pColumn = *pRow + i;
				*pColumn -= first*temp;
				if( j != nSize - 1 )
				{
					pRow++;
					first = **pRow;
				}

			}
		}

		double** pTabO = NULL; if( !CreateMatrix( &pTabO, nSize - 1 ) )
		{
			perror( "Nie udalo sie utworzyc macierzy" );
		}

		Complement( pTabO, pTab, 0, 0, nSize );

#ifdef	_DEBUG_
		printf( "\n" );
		PrintMatrix( pTab, nSize );
#endif

		det = det*Det( pTabO, nSize - 1 );
		return det;
	}
}
  */