#include "move.h"


#define PRINT

int move(int** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int * py, int** pRoot)
{

	switch (move)
	{
	case 0: *py -= 1; break;
	case 1: *py += 1; break;
	case 2: *px -= 1; break;
	case 3: *px += 1; break;
	default: printf("Wrong move\n");
	}


	if ((*px >= nCol) || (*px < 0) || (*py >= nRow) || (*py < 0))
	{
		*py = y;
		*px = x;
		return 0;
	}
	if (((pTab[*py][*px]) <= (nDepth)))
	{
		*py = y;
		*px = x;
		return 0;
	}

	if ((pRoot[*py][*px]))
	{
		*py = y;
		*px = x;
		return 0;
	}
	pRoot[*py][*px] = 1;

	return 1;
}

int root(int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest)
{

#ifdef PRINT
	printf("(%d,%d)->", x, y);
#endif

	pRoot[y][x] = 1;
	if (pRoot[y_dest][x_dest]) { return 1; } //a=1
	else
	{
		int xx = 0; //xx=x;
		int yy = 0; //yy=y;

		for (int i = UP; i <= RIGHT; i++)
		{
			if (!move(pTab, nRow, nCol, nDepth, i, x, y, &xx, &yy, pRoot))
			{
				continue;
			}
			if (root(pTab, nRow, nCol, nDepth, xx, yy, pRoot, x_dest, y_dest))
			{
				return 1; //return a
			}


		}

		pRoot[y][x] = 2;
		return 0;
	}


}

void setTab(char* sFile, int**pTab, int nRow, int nCol)
{
	FILE* fin;
	if ((fin = fopen(sFile, "r")) == NULL) //if file doesnt't be found - return null
	{
		perror("ERROR- CAN'T OPEN FILE");
	}

	int** pT = pTab;

	for (int i = 0; i < nRow; i++)
	{
		int* pColumn = *pT++;	 //after each incement of pM we should declare change of row
		for (int j = 0; j < nCol; j++, pColumn++)
		{
			fscanf(fin, "%ld", pColumn);
		}
	}
	fclose(fin);
}

void PrintTab(int** pTab, int nRow, int nCol)
{
	printf("\t");
	for (int i = 0; i < nCol; i++)
	{
		printf("%d:\t", i);
	}
	printf("\n");
	for (int i = 0; i < nRow; i++)
	{
		int* pColumn = *pTab++;//it allows to change column in this row
		printf("%d:\t", i);
		for (int j = 0; j < nCol; j++, pColumn++)
		{
			printf("%ld\t", *pColumn);
		}

		printf("\n");
	}
}


int CreateTab(int*** pTab, int nRow, int nCol)
{

	int** p = *pTab = (int**)calloc(nRow, sizeof(int*)); 	 //allocate memory for row

	if (!(*pTab))
	{
		perror("ERROR-WRONG MEMORY ALLOCATION!!!");
		return 0;
	}

	for (int i = 0; i < nCol; i++, p++) // move p and allocate memory for row
	{
		*p = (int*)calloc(nCol, sizeof(int));

		if (!(*p))
		{
			perror("ERROR-WRONG MEMORY ALLOCATION!!!");
			return 0;
		}
	}
	return 1;
}
