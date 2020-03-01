#include"FIFO.h"


int QfCreate( QueueFIFO* pQueue, int nSize ) 
{
	pQueue->nKey = ( QFIFOITEM* ) calloc( nSize, sizeof( QFIFOITEM ) );
	if( !( pQueue ) )
	{
		perror( "ERROR-WRONG MEMORY ALLOCATION!!!" );
		return 0;
	}
	
	pQueue->MaxQueueSize = nSize;
	pQueue->CurrentQueueSize = 0;
	pQueue->nHead = 0;
	pQueue->nTail = 0;
	
	return 1;
}
int QFEmpty( QueueFIFO* queue )	
{
	return !( queue->CurrentQueueSize );
}
void QFEnqueue( QueueFIFO* queue, QFIFOITEM x )
{	
	
	if( queue->MaxQueueSize == queue->CurrentQueueSize )
	{
		printf( "Can't add element" );
	}
	else{
		
		queue->nKey[queue->nTail] = x;
		queue->nTail= (queue->nTail+1)% queue->MaxQueueSize;
		queue->CurrentQueueSize++;
		
	}
}
int QFDequeue( QueueFIFO* queue ) 
{
	if( !QFEmpty( queue ) )
	{
		QFIFOITEM a = queue->nKey[queue->nHead];
		QFDel( queue );
		return a.nKey;
	}
	printf( "Queue is empty\n" );
	return 0;
		
} 
void QFClear( QueueFIFO* queue ) 
{
		
		while( queue->CurrentQueueSize )
			QFDel( queue );
		queue->nHead = 0;
		queue->nTail = 0;
		
	
}
void QFRemove( QueueFIFO* queue )	
{
	if( !QFEmpty( queue ) )
	{
		QFClear( queue );
		free( queue->nKey );
		queue = NULL;
		
	}
}
void QFDel( QueueFIFO* queue )
{
	if( !QFEmpty(queue) )
	{
		queue->nKey[queue->nHead].nKey=NULL;
		queue->nHead = ( queue->nHead + 1 ) % queue->MaxQueueSize;
		queue->CurrentQueueSize--;
		
	}
	else
		printf( "Queue is empty" );
}

void QFPrint( QueueFIFO q )
{
	if( !QFEmpty( &q ) )
	{
		int j = 0;
		int temp = q.nTail;
		if (temp <= q.nHead) temp = q.nHead + q.CurrentQueueSize;
		for( int i =q.nHead; i < temp; i++ )
		{
			printf( "%d: %d\n",j++,  q.nKey[i]  );
			if ((i+1) == q.MaxQueueSize)
			{
				i = 0;
				temp %= q.MaxQueueSize;
			}
		}
	}
}


QFIFOITEM* CreateElement( int nKey )
{
	QFIFOITEM* n = ( QFIFOITEM* ) malloc( sizeof( QFIFOITEM ) );
	if( n )
	{
		n->nKey = nKey;
		return n;
	}
	else
		perror( "Can't creat element" );
	return 0;
}