#pragma once
#ifndef PQUEUE_H
#define PQUEUE_H

#include "global.h"

typedef struct
{
	int nKey;
	double nPrior;
} PQItem;

typedef struct tagPQueue
{
	PQItem* PQItem;
	int PQSize;//max size  of queue
	int PQCurrentSize;//current number of elements
	 // after insert - update haystack 
}PQueue;


PQueue* PQInit( int );	  // Create priority queue (dynamic allocation) which size would be argument, set PQCurrentSize=0
int PQIsEmpty( PQueue* );//return PQCurrentSize
void PQEnqueue( PQueue*, int nKey, double nPrior );//Insert element [nKey,nPrior]
int PQDequeue( PQueue* ); // return element with the lowest priority
void PQClearQueue( PQueue* );//clear queue, doen't remove it 
void PQRelease( PQueue** );//  remove queue

#endif