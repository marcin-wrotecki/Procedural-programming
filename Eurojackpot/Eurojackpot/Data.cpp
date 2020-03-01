#include "Data.h"

int ReadData( Player*** pAllDraws, const char* sFileName )
{
	FILE* fin;

	if( ( fin = fopen( sFileName, "r" ) ) == NULL ) //if file was't found, return NULL
	{
		perror( "ERROR- CAN'T FIND FILE" );
		return 0;
	}
	int amountOfPlayers = 0;
	int maxSize = 0;

	Player* pTemp=NULL;

	char c = getc( fin ); //it is use to read chars from file, which was open by fopen function


	while( !feof( fin ) || c == '*' ) // while it is not the end of the file, variable c is a new player
	{
		if( amountOfPlayers == maxSize ) // if run of memory, allocate new players
		{
			maxSize += AllocAddMem( pAllDraws, amountOfPlayers );
			if( amountOfPlayers == maxSize )  break; // if can't allocate new memory - break;
		}
		
		pTemp = ( Player* ) calloc( 1, sizeof( Player ) );
		if( !pTemp )
		{
			perror( "WRONG MEMORY ALLOCATION- PLAYER" );
		}
		char sex;
		int day;
		int month;
		int year;

		//!!!
		fscanf( fin, "%s%s %c %4c%2c%2c%3c %2c%2c%8c%16c %d%*c%d%*c%d%s", pTemp->surname,  pTemp ->name, &sex,  pTemp ->accoutNumber.swift.bank,  pTemp ->accoutNumber.swift.country, pTemp ->accoutNumber.swift.localization, pTemp ->accoutNumber.swift.branch, pTemp ->accoutNumber.iban.country,  pTemp ->accoutNumber.iban.nrbdesignfirst, pTemp ->accoutNumber.iban.accnumber, pTemp ->accoutNumber.iban.nrcountry, &day, &month, &year,  pTemp ->PESEL );
		/* 
		Example input
		Banaszak   Lolita f    BPHKPLPKXXX   PL61123400110011000012300678     16/12/2016 01234567890
			1 10 23 30 38   1 5
			9 24 26 33 40   2 3
			8 14 26 33 47   2 7
			7 12 15 16 50   8 9
			6 14 20 27 28   4 10
		*/
		
		if( !SetSex( pTemp, sex ) )break; // if it is impossible to set up sex, it is an error so stop reading
		if( !SetDate( pTemp, day, month, year ) )break; // like above

		while( !( feof( fin ) ) && ( c = getc( fin ) ) != '*' ) // read chars
		{
			
			ungetc( c, fin ); // return C to buffer if it is not *

			
			
			if( !( ( pTemp )->amountOfBets%ALLOCBET )  && !AllocAddBet( &(pTemp->pBet), ( pTemp )->amountOfBets ) )
					perror( "Can't allocate memory for bets" );
			

			Bets* temp = &( pTemp->pBet[pTemp->amountOfBets++] );

			int* mainBet = temp->mainBet = ( int* ) calloc( MAXBETS, sizeof( int ) );
			int* extraBet = temp->extraBet = ( int* ) calloc( MAXEXTRABETS, sizeof( int ) );

			if( !mainBet || !extraBet )
			{
				perror( "ERROR-WRONG MEMORY ALLOCATION" );
				return 0;
			}

			for( int i = 0; i < MAXBETS; i++ )
				fscanf( fin, "%d", mainBet++ );
			for( int i = 0; i <  MAXEXTRABETS ; i++ )
				fscanf( fin, "%d", extraBet++ );
			
			fscanf( fin, "\n" );
			
		}
		
		(*pAllDraws)[amountOfPlayers] = pTemp;
		amountOfPlayers++;
		( pTemp )++; //next value from array
		
	}
	

	if( !amountOfPlayers )
	{
		printf( "No chars found" );
		return 0;
	}

	fclose( fin );
	return amountOfPlayers;
}

int AllocAddMem( Player*** pTab, int nCurrSize )
{
	Player** pTemp= ( Player** ) realloc( *pTab, ( nCurrSize + ALLOCPLAYER ) * sizeof( Player* ) );
	if( pTemp )
	{
		*pTab = pTemp;
		memset( *pTab+nCurrSize, 0, ALLOCPLAYER * sizeof( Player* ) );
		return ALLOCPLAYER; // if ALLOCPLAYER = 0, don't do anything
	}
	perror( "Can't allocate memory for players" );
	return 0;
}

int AllocAddBet( Bets** pTab, int nCurrSize )
{
	Bets* pTemp = ( Bets* ) realloc( *pTab, ( nCurrSize + ALLOCBET ) * sizeof( Bets ) );

	if( !pTemp)
	{
		perror( "ERROR-WRONG MEMORY ALLOCATION!!!" );
		return 0;
	}
	*pTab = pTemp;
	memset( ( *pTab + nCurrSize ), 0, sizeof( Bets )*ALLOCBET );
	return 1;
}

void FreeMem( Player*** pTab, int nDrawsNo )
{
	for( int i = 0; i < nDrawsNo; i++ )
	{
		Player* p = ( *pTab )[i];
		Bets* b = p->pBet;
		for( int j = 0; j < p->amountOfBets; j++,b++ )
		{
			free( b->mainBet++ );
			free( b->extraBet++ );
		}
		free( p->pBet );
		free( p );
	}
	free( *pTab );
}

int SetSex( Player* p, char c )
{
	switch( c )
	{
	case 'm':
	case 'M': p->sex = MALE; return 1;
	case 'f':
	case 'F': p->sex = FEMALE; return 1;
	default: return 0;
	}
}

int SetDate( Player* p, int d, int m, int y )
{
	if( !( ( d < 1 ) || ( d > 31 ) || ( m < 1 ) || ( m > 12 ) || ( y < 1930 ) ) )
	{
		p->BetDate.numberOfDay = d; // to print date
		p->BetDate.year = y;

		tm rTime;
		rTime.tm_year = y - 1900; //year since 1900
		rTime.tm_mon = m - 1; // month from range 0 - 11
		rTime.tm_mday = d - 1; // day from range 0 - 30

		// nullify other parameters
		rTime.tm_hour = 0;
		rTime.tm_min = 0;
		rTime.tm_sec = 0;
		mktime( &rTime );

		switch( rTime.tm_wday ) // 0 - Monday, 6 - Sunday
		{
		case 0: p->BetDate.day = MON; break;
		case 1: p->BetDate.day = TUE; break;
		case 2: p->BetDate.day = WED; break;
		case 3: p->BetDate.day = THU; break;
		case 4: p->BetDate.day = FRI; break;
		case 5: p->BetDate.day = SAT; break;
		case 6: p->BetDate.day = SUN; break;
		}

		switch( m )
		{
		case 1:  p->BetDate.month = JAN; break;
		case 2:  p->BetDate.month = FEB; break;
		case 3:  p->BetDate.month = MAR; break;
		case 4:  p->BetDate.month = APR; break;
		case 5:  p->BetDate.month = MAY; break;
		case 6:  p->BetDate.month = JUN; break;
		case 7:  p->BetDate.month = JUL; break;
		case 8:  p->BetDate.month = AUG; break;
		case 9:  p->BetDate.month = SEP; break;
		case 10:  p->BetDate.month = OCT; break;
		case 11:  p->BetDate.month = NOV; break;
		case 12:  p->BetDate.month = DEC; break;
		}

		return 1;
	}
	return 0;

}
