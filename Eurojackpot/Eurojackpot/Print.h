#ifndef PRINT_H
#define PRINT_H

#include "DEFS.h"


void PrintResults( int* pNums50, int* pNums10, Player** pDraws, int nDrawsNo );
void PrintSex( FILE* fout, Player* p );	  
void PrintDate( FILE* fout, Player* p );
void PrintBets( FILE* fout, Bets* pBets );
void PrintNumber( FILE* fout, const char*, int );


#endif