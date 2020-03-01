
// Implementacja kolejki FIFO z glowa przy uzyciu wskaznikow
// Implementation of FIFO queue with head using the pointers


#include<stdio.h>
#include"global.h"


int main()
{

	QueueFIFO queue;

	if( !QfCreate( &queue ) )
	{
		perror( "ERROR-WRONG MEMORY ALLOCATION" );
	}
	


	if( QFEmpty( &queue ) )
		printf( "Queue is empty\n" );

	printf( "Adding 4 elements\n" );
	QFEnqueue( &queue, 5 );
	QFEnqueue( &queue, 6 );
	QFEnqueue( &queue, 7 );
	QFEnqueue( &queue, 8 );
	QFPrint( queue );

	printf( "Dequeue element: %d\n", QFDequeue( &queue ) );
	printf( "Dequeue element: %d\n", QFDequeue( &queue ) );
	printf( "First element: %d\n",queue.pHead->pNext->nKey );

	QFPrint( queue );

	printf( "Remove first element: \n" );
	QFDel( &queue );
	QFPrint( queue );

	printf( "Clear queue\n" );
	QFClear( &queue );
	
	if( QFEmpty( &queue ) )
		printf( "Queue is empty\n" );
	printf( "Removing queue\n" );
	QFRemove( &queue );
}