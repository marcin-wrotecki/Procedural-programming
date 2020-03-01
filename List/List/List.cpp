
// Implementacja struktury listy z glowa
// Implementation of the list structure with head
#include <stdio.h>
#include "list.h"

int __cdecl Compare(const void * first, const void * second);


int main()
{
	ListItem list;
	list = *CreateList();


	LISTINFO * a = CreateElement(5);
	printf("Insert element in front: \n");

	InsertFront(&list, a);
	PrintList(list);

	LISTINFO *b = CreateElement(7);

	printf("Insert element in second place: \n");

	Insert(list.pNext, b);
	PrintList(list);

	LISTINFO *c = CreateElement(1);
	LISTINFO *d = CreateElement(2);
	LISTINFO *e = CreateElement(3);
	LISTINFO *f = CreateElement(4);
	printf("Insert 4 elements: \n");
	Insert(&list, c);
	Insert(&list, d);
	InsertFront(&list, e);
	Insert(list.pNext, f);
	PrintList(list);

	printf("Is 4 in the list? \n");
	ListItem** pPrev = (ListItem**)calloc(1, sizeof(ListItem*));
	if (!pPrev)
	{
		perror("Can't create element");
	}
	if (Find(&list, f, pPrev, Compare))
		printf("Yes\n");
	else
		printf("No\n");

	printf("Is 8 in the list? \n");
	if (Find(&list, CreateElement(8), pPrev, Compare))
		printf("Yes\n");
	else
		printf("No\n");


	printf("Sorted: \n");
	SortList(&list, Compare);
	PrintList(list);

	printf("Insert element in front:\n");

	InsertFront(&list, Front(&list)->pInfo);
	PrintList(list);

	printf("Remove 2 elements at the beginning: \n");
	RemoveFront(&list);
	RemoveFront(&list);
	PrintList(list);

	printf("Remove 4 elements from list: \n");
	Remove(list.pNext->pNext->pNext);
	PrintList(list);

	printf("Clear list: \n");
	FreeList(&list);
	PrintList(list);
	//PrintList( list );
	return 0;
}

int __cdecl Compare(const void * first, const void * second)
{
	if (((LISTINFO*)first)->nKey < ((LISTINFO*)second)->nKey) return -1;
	else if (((LISTINFO*)first)->nKey == ((LISTINFO*)second)->nKey) return 0;
	else return 1;
}