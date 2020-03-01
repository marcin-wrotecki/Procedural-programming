
//Implementacja kolejki priorytetowej w strukturze kopca
//Implementation of priority queue in the structure of heap

#include "Function.h"
#include <time.h>
#define MAXSIZE 10
#define RANDPRIOR 10
#define RANDKEY 20
int main()
{
	PQueue* pQueue = PQInit( MAXSIZE );

	for( int i = 0; i < MAXSIZE; i++ )
	{
		int nPrior = rand() % RANDPRIOR + 1;// priorytet od 1 do 10
		int nKey = rand() % RANDKEY + 1; // nkey od 1 do 20
		PQEnqueue( pQueue, nKey, nPrior );
		printf( "%d\t%d\n", nPrior, nKey );
	}

	PQPrint( pQueue );
	printf( "\n\n" );


	printf( "\Zdjeto: %d\n", PQDequeue( pQueue ) );// dwa razy zdejmuje
	printf( "Zdjeto: %d\n", PQDequeue( pQueue ) );
	PQPrint( pQueue );
	printf( "\n\n" );
	printf( "Zwiekszenie priorytetu 3 elementu: \n" );
	IncreaseKey( pQueue, 2, 20 );
	PQPrint( pQueue );
	printf( "Zmniejszenie priorytetu 2 elementu: \n" );
	DecreaseKey( pQueue, 1, 1 );
	PQPrint( pQueue );
	
	for( int i = 0; i < 3; i++ ) //3x enqueue - jeden error
	{
		int nPrior = rand() % RANDPRIOR + 1;
		int nKey = rand() % RANDKEY + 1;
		PQEnqueue( pQueue, nKey, nPrior );
		printf( "nKey: %d \t nPrior: %d\n", nKey, nPrior );
	}
	PQPrint( pQueue );
	printf( "\n\n" );
	
	printf( "\nZdjeto: %d\n", PQDequeue( pQueue ) ); //1x dequeue
	PQPrint( pQueue );
	printf( "\n\n" );
	
	for( int i = 0; i < 2; i++ ) // 2x enqueue- wyskoczy error
	{
		int nPrior = rand() % RANDPRIOR + 1;
		int nKey = rand() % RANDKEY + 1;
		PQEnqueue( pQueue, nKey, nPrior );
		printf( "nKey: %d \t nPrior: %d\n", nKey, nPrior );
	}
	PQPrint( pQueue );
	printf( "\n\n" );

	while( !PQIsEmpty( pQueue ) )
	{
		printf( "\nZdjeto: %d\n", PQDequeue( pQueue ) );
		PQPrint( pQueue );
	}
	

	PQRelease( &pQueue );
}
