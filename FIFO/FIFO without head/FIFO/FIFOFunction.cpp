#include"global.h"



int QfCreate( QueueFIFO* pQueue) 
{
	pQueue->pHead =	pQueue->pTail = NULL;
	return 1;
}
int QFEmpty( QueueFIFO* queue )	
{
	return !( queue->pHead );
}
void QFEnqueue( QueueFIFO* queue, int x )
{
	QFIFOItem* tempQueue = ( QFIFOItem* ) calloc( 1, sizeof( QFIFOItem ) );	
	if( !tempQueue )
	{
		perror( "ERROR-WRONG MEMORY ALLOCATION!!!" );
	}
	if( QFEmpty( queue ) )
	{
		queue->pHead = tempQueue;
	}
	else
	{
		queue->pTail->pNext = tempQueue;
	}
	queue->pTail = tempQueue;
	queue->pTail->nKey = x;
	queue->pTail->pNext = NULL;
	
	
}
int QFDequeue( QueueFIFO* queue ) 
{
	if( !QFEmpty( queue ) )
	{
		int a = queue->pHead->nKey;
		QFDel( queue );
		return a;
	}
	printf( "Queue is empty" );
	return 0;

}
void QFClear( QueueFIFO* queue ) 
{
	while( queue->pHead )
		QFDequeue( queue );
	
}
void QFRemove( QueueFIFO* queue )	
{
	free( queue->pHead );
	queue->pHead = NULL;
	queue->pTail = NULL;
}
void QFDel( QueueFIFO* queue )
{
	if( !QFEmpty( queue ) )
	{
		QFIFOItem * v= queue->pHead;
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
		while((q.pHead) )
		{
			printf( "%d: %d\n", i++, q.pHead->nKey );
			q.pHead = q.pHead->pNext;
		}
	}
	else
		printf( "Queue is empty" );
}