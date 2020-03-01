#ifndef DATA_H
#define DATA_H

#include "DEFS.h"

int ReadData( Player*** pAllDraws, const char* sfileName );//filename is an argument from commandline
int AllocAddMem( Player*** pTab, int nCurrSize );//reallocation for bets, we should give the size of array
void FreeMem( Player*** pTab, int nDrawsNo ); // free memory
int SetSex( Player* p, char c );//if doesn't find sex - stop reading
int SetDate( Player* p, int d, int m, int y );	//check day, month and year (year should be >1930)
//if setSex and setDate return 0 - stop reading
int AllocAddBet( Bets** pTab, int nCurrSize );

#endif
