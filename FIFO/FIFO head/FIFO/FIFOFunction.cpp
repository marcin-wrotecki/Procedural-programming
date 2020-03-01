#include"global.h"



int QfCreate( QueueFIFO* pQueue) 
{
	
	QFIFOItem* tempQueue = ( QFIFOItem* ) calloc( 1, sizeof( QFIFOItem ) );
	if( !( tempQueue ) )
	{
		perror( "ERROR-WRONG MEMORY ALLOCATION!!!" );
		return 0;
	}
	pQueue->pHead = pQueue->pTail = tempQueue;

	return 1;
}
int QFEmpty( QueueFIFO* queue )	
{	
		return !( queue->pHead->pNext );
}
void QFEnqueue( QueueFIFO* queue, int x )
{
	QFIFOItem* tempQueue = ( QFIFOItem* ) calloc( 1, sizeof( QFIFOItem ) );	
	if( !( tempQueue ) )
	{
		perror( "ERROR-WRONG MEMORY ALLOCATION!!!" );
		
	}
	
	tempQueue->nKey = x;
	queue->pTail->pNext = tempQueue;
	queue->pTail = tempQueue;
	
}
int QFDequeue( QueueFIFO* queue ) 
{
	if( !QFEmpty( queue ) )
	{
		int a = queue->pHead->pNext->nKey;
		QFDel( queue );
		return a;
	}
	printf( " Queue is empty" );
	return 0;

}
void QFClear( QueueFIFO* queue ) 
{
	while( queue->pHead->pNext )
		QFDequeue( queue );
}
void QFRemove( QueueFIFO* queue )	
{
	free( queue->pHead->pNext );
	free( queue->pHead );
	queue->pHead = queue->pTail =NULL;
}
void QFDel( QueueFIFO* queue )
{
	if( !QFEmpty( queue ) )
	{
		QFIFOItem * v = queue->pHead;
		queue->pHead = queue->pHead->pNext;
		if( !( queue->pHead ) )queue->pTail = NULL;
		free( v );
	}
	else
		printf( "Queue is empty" );
}

void QFPrint( QueueFIFO q )
{

	if( !QFEmpty( &q ) )
	{
		int i = 0;
		q.pHead = q.pHead->pNext;
		while( q.pHead)
		{
			printf( "%d: %d\n", i++, q.pHead->nKey );
			q.pHead = q.pHead->pNext;
		}
	}
	else
		printf( "Queue is empty" );
}


