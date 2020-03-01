#ifndef DSTACK_H
#define DSTACK_H


#include <iostream>
#include <stdlib.h>
#include<memory.h>

using namespace std;
#define MAXSTACK 20

typedef struct dtagStack
{
	double dKey;
	struct dtagStack* pNext;
}DStack;

DStack* dInitStack();
void dRemoveStack(DStack ** pStack);
void dpush(double val, DStack** pStack);
double dpop(DStack** pStack);
double dtop(DStack* pStack);
void ddel(DStack** pStack);
int disEmpty(DStack* pStack);

//dodanie tych pStack pozwala na uoglnienie 
#endif
