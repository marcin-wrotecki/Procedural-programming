
//Celem dzialania programu jest posortowanie tablicy na rozne sposoby i pomiar czasu sortowania
//The purpose of this program is to sort arrays in diffrent ways and to measure the time of sorting

#include "sort.h"

//#define MAXSTACK 10000
#define PRINT 50
//#define _DEBUG_

void InitTab(int** pTab, int nSize);
void PrintTab(int* pTab, int nSize);
void CopyTab(int** source, int** destination, int nSize);
int CreateTab(int** pTab, int nSize);


typedef void(*pFunction)(int*, int);


int main(int argc, char* argv[])
{

	pFunction pFSort[] = { BubbleSort, InsertionSort,SelectSort, MixedBubbleSort,HalfInsertionSort,HeapSort,QuickSort };
	const char* sortName[] = { "BubbleSort", "InsertionSort", "SelectSort", "MixedBubbleSort", "HalfInsertionSort", "HeapSort", "QuickSort", "MergeSort","NaturalSort" };

	clock_t cTime;

	if (argc != 2)
	{
		printf("Please, give the number of elements to sort");
		return -1;
	}
	int nSize = atoi(argv[1]);



	//printf( "Give the size of array: " );
	//scanf( "%d", &nSize );

	if (nSize < 0)
	{
		perror("WRONG ARRAY SIZE");
	}

#define MAXSTACK nSize

	int* pTab = NULL;
	if (!CreateTab(&pTab, MAXSTACK))
	{
		perror("Can't create matrix");
	}

	InitTab(&pTab, MAXSTACK);

#ifdef _DEBUG_
	printf("ORYGINAL: \n");
	PrintTab(pTab, PRINT);
#endif

	int* pTabCpy = NULL;

	if (!CreateTab(&pTabCpy, MAXSTACK))
	{
		perror("Can't create matrix pTabCpy");
	}


	int amountOfSortFunction = sizeof(pFSort) / sizeof(pFunction);//calculate size of array pFunction
	int i;

	for (i = 0; i < amountOfSortFunction; i++)
	{
		CopyTab(&pTab, &pTabCpy, MAXSTACK);
		cTime = clock();	//begin counting of time
		(pFSort[i](pTabCpy, MAXSTACK));
		printf("%s : %.0f ms\n", sortName[i], (double)((clock() - cTime)));

#ifdef _DEBUG_		
		PrintTab(pTabCpy, PRINT);
#endif
	}



	int* pTempTab = NULL;//this is array which task is help to use MergeSort
	int left = 0;
	int right = MAXSTACK - 1;//index of last element in array  

	if (!CreateTab(&pTempTab, MAXSTACK))
	{
		perror("Can't create matrix pTempTab");
	}

	CopyTab(&pTab, &pTabCpy, MAXSTACK);
	CopyTab(&pTab, &pTempTab, MAXSTACK);

	cTime = clock();
	MergeSort(pTabCpy, pTempTab, MAXSTACK, left, right);
	printf("%s : %.0f ms\n", sortName[i], (double)((clock() - cTime)));

	CopyTab(&pTab, &pTabCpy, MAXSTACK);
	cTime = clock();
	NaturalSort(pTabCpy, MAXSTACK);
	printf("%s : %.0f ms\n", sortName[i + 1], (double)((clock() - cTime)));

#ifdef _DEBUG_		
	PrintTab(pTabCpy, PRINT);
#endif

	free(pTempTab);
	free(pTab);
	free(pTabCpy);
	return 0;
}

int CreateTab(int** pTab, int nSize)
{
	*pTab = (int*)malloc(sizeof(int)*nSize);

	if (!(*pTab))
	{
		perror("ERROR-WRONG MEMORY ALLOCATION!!!");
		return 0;
	}
	memset(*pTab, 0, sizeof(int)*nSize);
	return 1;
}


void InitTab(int** pTab, int nSize)
{
	srand(time(NULL));
	for (int i = 0; i < nSize; i++)
		*(*pTab + i) = rand() % MAXSTACK;
}

void PrintTab(int* pTab, int nSize)
{
	if (!pTab) printf("Array is empty!\n");
	else
	{
		for (int i = 0; i < nSize; i++)
		{
			printf("%d\t ", *pTab++);
			if (!((i + 1) % 10))printf("\n");
		}
	}
}

void CopyTab(int** source, int** destination, int nSize)
{
	memcpy(*destination, *source, sizeof(int)*nSize);
}


