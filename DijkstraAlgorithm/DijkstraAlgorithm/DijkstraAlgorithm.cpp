
//Celem dzialania programu jest przeanalizowanie tekstowego pliku wejsciowego, znalezienie najkrotszej drogi z domu do sklepu poprzez uzycie kolejki priorytetowej w formie kopca oraz algorytmu Dijkstry, a nastepnie wydruk odleglosci, czasu oraz sciezki do pliku wyjsciowego
//Struktura pliku: numer budynku, czy jest to sklep ( 1 - tak, 0 - nie), liczba sasiadow, numer sasiada, odleglosc

//The purpose of this program is to analyze text input file, find the shortest route to the shop from home using the priority queue in the structure of heap and Dijkstra algorithm and print results in output file ( wyniki.txt)
//Structure of the input file: number of the building, is it a shop ( 1-yes, 0 - no), number of the neigbouring building, number of the neighbouring building, distance to this building, ...

#include "global.h" 
#include "list.h"


int ReadFile(Vertex** vertex, FILE* fin);
void PrintResults(Vertex* node, int nSize);
void PrintWays(FILE* fout, Vertex* pVertex, int nSize);
int AllocAddLines(Vertex** vertex, int nCurrSize);

#define REALLOC 3
#define RESULTS "result.txt" //name of result file



int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Second argument should be name of file!\n");
		return 0;
	}

	FILE* fin = fopen(argv[1], "r");
	if (!fin)
	{
		perror("Can't find file!\n");
		return 0;
	}


	Vertex* pVertex = NULL; //Array which contain structures which are vertexes of graph


	int amountOfReadedPlace = ReadFile(&pVertex, fin);
	if (!amountOfReadedPlace)
	{
		perror("Can't read any data\n");
		return 0;
	}



	int* visited = (int*)calloc(amountOfReadedPlace, sizeof(int));

	if (!visited)
	{
		perror("ERROR: WRONG MEMORY ALLOCATION \n");
		return 0;
	}

	DFS(pVertex, 0, visited);



	PrintResults(pVertex, amountOfReadedPlace);
	FreeMemory(pVertex, amountOfReadedPlace);

	return 0;
}




int ReadFile(Vertex** vertex, FILE* fin)
{
	int amountOfReadedPlace = 0;
	char c;

	while (!feof(fin))
	{

		if (!(amountOfReadedPlace%REALLOC) && !AllocAddLines(vertex, amountOfReadedPlace)) //realocate dynamic memory - allotws to read 3 next line from input file
		{
			perror("Can't reallocate array!");
			return -1;
		}


		Vertex* pVertex = &((*vertex)[amountOfReadedPlace]);//pointer on vertex which we analyze

		fscanf(fin, "%d %d %d", &pVertex->numberOfHome, &pVertex->isItShop, &pVertex->amountOfNeighbours);
		// write in number of neighbout and information if is it shop
		ListItem* tmp = CreateList(); // create empty list

		while (!feof(fin) && ((c = fgetc(fin)) != '\n')) //while it is not end of file or new line char - write in others information
			if (c >= '0' && c <= '9')
			{
				ungetc(c, fin);
				LISTINFO* pItem = CreateElement(0, 0, 0);
				fscanf(fin, "%d", &pItem->numberOfHome);
				fscanf(fin, "%lf", &pItem->distance);
				pItem->time = 0;// liczenie nastepuje w dfs
				tmp->pInfo->distance = 0;
				tmp->pInfo->numberOfHome = amountOfReadedPlace;
				tmp->pInfo->time = 0;
				//because tmp sets up on pInfo -> first element is always 0 (list with head), so value of head I set value of this vertex 
				Insert(tmp, pItem); // set up pItem at the beginning of the list			}
			}
		pVertex->listOfNeighbours = tmp;
		amountOfReadedPlace++;
	}

	fclose(fin);
	return amountOfReadedPlace;
}

void PrintResults(Vertex* pVertex, int nSize)
{
	FILE* fout = NULL;
	if (!(fout = fopen(RESULTS, "wt"))) // if file doesn't exit - create it 
	{
		fputs(RESULTS, fout);
	}

	for (int i = 0; i < nSize; i++)
	{
		pVertex[i].distanceToShop = Dijkstra(pVertex, nSize, i); // looking for the shortest way 
		pVertex[i].time = pVertex[i].distanceToShop / SPEED;
		if (!(pVertex[i].isItShop))
		{
			int minutes = (int)(pVertex[i].time * 60); // minutes
			int seconds = (int)((pVertex[i].time * 60 - minutes) * 60); // seconds
			fprintf(fout, "\nFor vertex, whose index is %d, distance to the nearest shop is: %.1lf. To reach it, you need %d minutes and %d secunds. Index of that shop is %d. \n", i, pVertex[i].distanceToShop, minutes, seconds, pVertex[i].nearestShop);
		}
		else
			fprintf(fout, "\nSHOP, whose index is: %d. \n", i);

	}

	PrintWays(fout, pVertex, nSize);
	fclose(fout);
}

void PrintWays(FILE* fout, Vertex* pVertex, int nSize)
{
	for (int i = 0; i < nSize; i++)
	{
		if (!(pVertex[i].isItShop))
		{
			int* route = (int*)calloc(nSize, sizeof(int));
			if (!route)
			{
				perror("WRONG MEMORY ALLOCATION");
			}

			int tmp = pVertex[i].nearestShop;
			int p = 1;
			route[0] = tmp; // it is necessary to set it here
			while (p < nSize && route[p - 1] != i)// copy array
			{
				route[p] = tmp;
				tmp = pVertex[i].way[tmp];
				p++;
			}


			for (int k = 0; k < p / 2; k++)//reserves array with way
			{
				int temp = route[p - k - 1];
				route[p - k - 1] = route[k];
				route[k] = temp;
			}
			pVertex[i].way = route;

			fprintf(fout, "\n");

			fprintf(fout, "\n Way to home number: %d\n", i);
			int m = 0;
			while (pVertex[i].way[m] != pVertex[i].nearestShop)
				fprintf(fout, "%d -> ", pVertex[i].way[m++]);
			fprintf(fout, "%d ", pVertex[i].way[m]);
		}
	}
}





int AllocAddLines(Vertex** vertex, int nCurrSize)
{
	Vertex* tmp = (Vertex*)realloc(*vertex, sizeof(Vertex)*(nCurrSize + REALLOC)); //array contains node of strcture
	if (!tmp)
	{
		perror("ERROR: WRONG MEMORY ALLOCATION");
		return 0;
	}
	*vertex = tmp;
	memset((*vertex + nCurrSize), 0, sizeof(Vertex) * REALLOC); //set 0 in array
	return REALLOC;
}