#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H


#include <stdlib.h>
#include "list.h"
#include "PQueue.h"
#include <stdio.h>
#include <memory.h>

#define PLACES 27
#define SPEED 5		//km/h
//distance between nodes [km]
typedef struct 
{
	ListItem* listOfNeighbours;
	int numberOfHome; // number of node
	int isItShop; // 1- yes 0 - no
	int amountOfNeighbours; 
	double distanceToShop;
	double time; // time [hour]
	int* way; 
	int nearestShop; //index of nearest shop
}Vertex;

double Dijkstra( Vertex* vertex, int nSize, int start);
void FreeMemory( Vertex* vertex, int nSize );
void DFS( Vertex* vertex, int v, int* visited );



#endif