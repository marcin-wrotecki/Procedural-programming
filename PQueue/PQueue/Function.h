#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <cstdlib>
#include "global.h"
typedef struct tagPQueue
{
	PQItem* PQItem;
	int PQSize;
	int PQCurrentSize;
	//pQueue//kolejka realizowana w postaci stogu//tablica w odpowiedniej funkcji ktora bedzie inicjalizowac te kolejke
	//int //PQSize // rozmiar kolejki priorytetowej
	//PQCurrentSize //aktualna ilosc elementow w kolejce - jednoczesnie indeks elementu to tablicy gdzie trzeba wstawic nowy element
	// po wstawieniu nalezy uaktualnic kopiec od dolu do gory
}PQueue;


PQueue* PQInit( int );	  //na bazie parametru okreslajacego maksymalny rozmiar kolejki ma stworzyc te kolejke
	// tworzy strukture PQueue dynamiczne, dla pQueue(pola) przydziela dynamicznie pamiec, przekazuje wartossc PQSize, ustawia
	//PQCurrentSize na zero
int PQIsEmpty( PQueue* );//zwraca wartosc 1 gdy jest pusta- zwraca po prostu PQCurrentSize 
void PQEnqueue( PQueue*, int nKey, int nPrior );//wk³ada element do kolejki priorytetowej o kluczu nKey i priorytecie nPrior
int PQDequeue( PQueue* ); // wyciaga z kolejki pierwszy element ktory ma najwyzszy (lub najnizszy- u nas najnizszy)
	//piorytet
void PQClearQueue( PQueue* );//ma wyczyscic kolejke, ale ca³a kolejka zostaje
void PQRelease( PQueue** );//  ca³kowicie usuwa kolejkê, ale zwraca w parametrze we/wy NULLL
void PQPrint( PQueue* );//drukuje w inorder

void DecreaseKey( PQueue*, int nKet, int nPrior ); //( nPrior < Item.nPrior );// jesli warunek nie jest spelniony to nic nie robic
	// jesli jednak jest zachowana jest ta nierownosc to wstawic ten nowy priorytet do funkcji i uaktualnic(w dol)
void IncreaseKey( PQueue*, int nKet, int nPrior );		 //  ( nPrior > Item.nPrior );//uaktualnia w gore dany element stogu

#endif