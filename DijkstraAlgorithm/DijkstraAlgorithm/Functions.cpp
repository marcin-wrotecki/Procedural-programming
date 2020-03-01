#include "global.h"
#include "PQueue.h"


void DFS(Vertex* vertex, int indexOfVertex, int* visited) // go through graph - calculate time to neghbours
{
	visited[indexOfVertex] = 1; //set 1 when vertex was visited
	ListItem* pList = vertex[indexOfVertex].listOfNeighbours;  //choose neighbour
	while (pList)		// while exist any neighbour
	{
		pList->pInfo->time = pList->pInfo->distance / SPEED; // calculate time 
		if (!visited[pList->pInfo->numberOfHome]) // if doesn't visited
			DFS(vertex, pList->pInfo->numberOfHome, visited); //go in next vertex
		pList = pList->pNext;// switch to next neghbour
	}

}


double Dijkstra(Vertex* vertex, int nSize, int start)
{
	PQueue* pQueue = PQInit(nSize); // initialize priority Queue (the lowest priority first!) 
	if (!pQueue)
	{
		perror("Can't initialize priority queue");
		return -1;
	}


	double* cTab = (double*)calloc(1, nSize * sizeof(double)); //c- min time to go to the destination
	int* pTab = (int*)calloc(nSize, sizeof(int)); //initialize array  of previous records on the path from v vertex
	if (!pTab || !cTab)
	{
		perror("ERROR: WRONG MEMORY ALLOCATION\n");
		return -1;
	}




	for (int i = 0; i < nSize; i++) //set max Value in cost array
	{
		cTab[i] = INT_MAX; // //set time=max Value
		pTab[i] = -1; //array to create way
	}

	vertex[start].way = pTab;

	PQEnqueue(pQueue, start, 0);
	cTab[start] = 0; // vertex has 0 distance to itself
	double len = 0; // distance to the nearest shop 

	while (!(PQIsEmpty(pQueue)))
	{
		int k = PQDequeue(pQueue);// pop neighbour from queue
		if (vertex[k].isItShop) // if it is shop - it is not neccesary to look for way 
		{
			vertex[start].nearestShop = k; // if condition is fulfiled -> k is the nearest shop
			PQRelease(&pQueue);
			len = cTab[k];
			break;
		}

		else
		{
			ListItem* neighbourList = vertex[k].listOfNeighbours; //list of neighbout
			while (neighbourList)
			{
				int neighbour = neighbourList->pInfo->numberOfHome;// set neighbour 

				if (cTab[k] + neighbourList->pInfo->distance < cTab[neighbour]) // check if distance to him is lower than cost from array/whole 
					//cTab[k] - distance to neighbour, which was dequeue from queue, from vertex neighbourList
				{
					cTab[neighbour] = cTab[k] + neighbourList->pInfo->distance;
					vertex[start].way[neighbour] = k;
					PQEnqueue(pQueue, neighbour, cTab[neighbour]); //cTab[neigbour] - priorty equal distance to this neighnour
				}
				neighbourList = neighbourList->pNext; //indicate next neighbout
			}
		}
	}
	free(cTab);
	return len;
}


void FreeMemory(Vertex* vertex, int nSize)
{
	for (int i = 0; i < nSize; i++)
	{
		FreeList(vertex[i].listOfNeighbours);
		free(vertex[i].way);
	}
	free(vertex);
	vertex = NULL;
}
