#ifndef FIFO_H
#define FIFO_H

#include<stdio.h>
#include <stdlib.h>
#include "global.h"

typedef struct
{

	QFIFOITEM* nKey;
	int nHead;// index of the first item - nHead
	int nTail;// index of the first empty item (one after last) - nTail
	int CurrentQueueSize;
	int MaxQueueSize;

}QueueFIFO;


int QfCreate( QueueFIFO* q, int nSize ); // initialize queue, return 0 or 1  
int QFEmpty( QueueFIFO* q );	// return 0 when empty else 1
void QFEnqueue( QueueFIFO* q, QFIFOITEM x );// insert element in the end
int QFDequeue( QueueFIFO* q ); //pop
void QFClear( QueueFIFO* q ); //clear queue (free memory), set pHead and pTail on null
void QFRemove( QueueFIFO* q );	//remove queue 
void QFDel( QueueFIFO* q );// delete first element
void QFPrint( QueueFIFO q );
QFIFOITEM* CreateElement( int nKey );
#endif