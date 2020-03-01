#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdlib.h>
#include<memory.h>

using namespace std;
#define MAXSTACK 20
typedef struct tagStack
{
	char cKey;
	tagStack* pNext;
}Stack;

Stack* InitStack();
void RemoveStack(Stack ** pStack);
void push(char c, Stack** pStack);
char pop(Stack** pStack);
char top(Stack* pStack);
void del(Stack** pStack);
int isEmpty(Stack* pStack);

//dodanie tych pStack pozwala na uoglnienie 
#endif