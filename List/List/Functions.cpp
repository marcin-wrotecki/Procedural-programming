#include"list.h"




ListItem* CreateList()
{
	ListItem* p = (ListItem *)calloc(1, sizeof(ListItem));
	LISTINFO* n = (LISTINFO*)calloc(1, sizeof(LISTINFO));
	if (p && n)
	{

		p->pInfo = n;
		p->pNext = NULL;
		return p;

	}
	printf("Can't create list");
	return NULL;
}

void InsertFront(ListItem* pList, LISTINFO* pInfo)
{
	Insert(pList, pInfo);
}

void Insert(ListItem* pAfter, LISTINFO* pInfo)
{

	ListItem* p = (ListItem*)calloc(1, sizeof(ListItem));
	if (p)
	{
		p->pNext = pAfter->pNext;
		p->pInfo = pInfo;
		pAfter->pNext = p;
	}
	else
		perror("Can't insert element");
}

ListItem* Front(ListItem* pList)
{
	return pList->pNext;
}


void Remove(ListItem* pAfter)
{
	if (pAfter->pNext)
	{
		ListItem* p = pAfter->pNext;
		pAfter->pNext = p->pNext;
		free(p);
		// free 
	}
	else
		perror("Can't remove element");
}

void RemoveFront(ListItem* pList)
{
	Remove(pList);
}



void FreeList(ListItem* pList)
{
	while (!isEmpty(pList))
	{
		RemoveFront(pList);
	}
}

int isEmpty(ListItem* pList)
{

	return !(pList->pNext);

}

void SortList(ListItem* pList, int(__cdecl *pfunction)(const void* a, const void* b))
{
	ListItem* pStart = pList;

	while (pStart->pNext)
	{

		ListItem* pPrevMin = pStart;
		ListItem* p = pStart->pNext;

		while (p->pNext)
		{
			if (pfunction(pPrevMin->pNext->pInfo, p->pNext->pInfo) == 1)
			{
				pPrevMin = p;
			}
			p = p->pNext;

		}
		if (pPrevMin != pStart)
		{
			p = pPrevMin->pNext;
			pPrevMin->pNext = pPrevMin->pNext->pNext;
			p->pNext = pStart->pNext;
			pStart->pNext = p;


		}

		pStart = pStart->pNext;

	}


}



ListItem* Find(ListItem* pList, LISTINFO* pFind, ListItem** pPrev, int(_cdecl *pFCompare)(const void* a, const void* b))
{

	*pPrev = pList;// set previous element as first 
	while ((*pPrev)->pNext)// while next element exists
	{
		if (!pFCompare((const void*)pFind, (const void*)((*pPrev)->pNext->pInfo)))// compare pNext with element which is searched
			return (*pPrev)->pNext;//if found return previous
		*pPrev = (*pPrev)->pNext;// next element
	}
	return *pPrev = NULL;// if doesn't found - return NULL

}




LISTINFO* CreateElement(int nKey)
{
	LISTINFO* n = (LISTINFO*)malloc(sizeof(LISTINFO));
	if (n)
	{
		n->nKey = nKey;
		return n;
	}
	else
		perror("Can't create element");
	return 0;
}

/*
void DelList(ListItem* pList)
{
	FreeList( pList );
	pList->pInfo=NULL;
}
*/
void PrintList(ListItem list)
{
	ListItem *p = list.pNext;
	if (isEmpty(&list))
		printf("List is empty");
	else
	{
		while (p)
		{
			printf("%d ", *(p->pInfo));
			p = p->pNext;
		}
	}
	printf("\n");
}
