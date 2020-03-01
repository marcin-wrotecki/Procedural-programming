#ifndef LIST_H
#define LIST_H

#include "global.h"
#include <stdio.h>
#include <cstdlib>

typedef struct tagListItem
{
	LISTINFO* pInfo; 
	tagListItem* pNext; //pointer on the next element

}ListItem;

ListItem* Find( ListItem* pList, LISTINFO* p, ListItem** pPrev, int( *pfunction )( const void* a, const void* b ) );
void InsertFront( ListItem* pList,  LISTINFO* pInfo );  //insert at the beginning
void Insert( ListItem* pAfter,  LISTINFO* pInfo );//inset in the end
void Remove( ListItem* pAfter ); // delete elements - take pointers
void RemoveFront( ListItem* pList );   // pop
ListItem* CreateList(); //create empty list
ListItem* Front( ListItem* pList );//top
void FreeList( ListItem* pList );//clear list - leave head
int isEmpty( ListItem* pList );
void SortList( ListItem* pList, int ( _cdecl *pfunction)(const void* a, const void* b ));// sort list - ascending
void PrintList( ListItem list );
//void DelList( ListItem* pList );
LISTINFO* CreateElement( int nKey );


#endif // !LIST_H
