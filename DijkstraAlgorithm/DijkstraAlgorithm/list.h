#pragma once
#ifndef LIST_H
#define LIST_H

typedef struct
{
	int numberOfHome;
	double distance;
	double time;

}ListInfo;

#define LISTINFO ListInfo


typedef struct tagListItem
{
	LISTINFO* pInfo;
	tagListItem* pNext; // pointer on next element

}ListItem;


void InsertFront( ListItem* pList, LISTINFO* pInfo );  
void Insert( ListItem* pAfter, LISTINFO* pInfo );
void Remove( ListItem* pAfter ); // delete elements - take pointers
void RemoveFront( ListItem* pList );   // pop
ListItem* CreateList(); //create empty list
ListItem* Front( ListItem* pList );//top
void FreeList( ListItem* pList );//clear list - leave head
int isEmpty( ListItem* pList );
LISTINFO* CreateElement(  int numberOfHome,double distance, double time );//create element of list

#endif // !LIST_H