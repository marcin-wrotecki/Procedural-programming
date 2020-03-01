#ifndef GLOBAL_H
#define GLOBAL_H

#include<stdio.h>
#include <stdlib.h>

typedef struct tagQueueFIFO
{
	int nKey;
	tagQueueFIFO* pNext;
}QFIFOItem;

typedef struct 
{
	QFIFOItem* pHead; // pointer indicates first element of queue
	QFIFOItem* pTail; // pointer indicates last element of queue

}QueueFIFO;



int QfCreate( QueueFIFO* q); // initialize queue, return 0 or 1  
int QFEmpty( QueueFIFO* q );	// return 0 when empty else 1
void QFEnqueue( QueueFIFO* q, int x );// insert element in the end
int QFDequeue( QueueFIFO* q ); //pop
void QFClear( QueueFIFO* q ); //clear queue (free memory), set pHead and pTail on null
void QFRemove( QueueFIFO* q );	//remove queue 
void QFDel( QueueFIFO* q );// delete first element
void QFPrint( QueueFIFO q );



#endif
