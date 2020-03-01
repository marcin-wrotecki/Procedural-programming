#include "stack.h"

using namespace std;


Stack* InitStack()
{
	return NULL;
}
void RemoveStack(Stack ** pStack)
{
	while ( !isEmpty(*pStack) )
		del(pStack);
	*pStack = NULL;
}


void push(char c, Stack** pStack)
{
	Stack* v = (Stack*)malloc(sizeof(Stack));//alokowanie pewnej ilosc bajtow - rozmiaru pudelka stack, malloca trzeba zrzutowac 
	//na to jakigo typ ma byc wskazni

	if ( v ) // if( v!=NULL)
	{
		memset( v, 0, sizeof(Stack) ); //jak dostac sie do pol struktury
		//(*v).cKey=c//operator kropka ma wiekszzy priorytet niz gwiazdka wiec musi byc w nawiasie
		v->cKey = c; //operator strzalki, bo v wskazuje, zamiast tego wyzej
		//dowiazanie
		v->pNext = *pStack;
		*pStack = v;
	}
	else
		perror("ERROR push: stack overflow");
}

char pop(Stack** pStack) // zdejmij i zwroc szczyt
{
	if ( !isEmpty(*pStack) ) {
		char c = top(*pStack);
		del(pStack);
		return c;
	}
	perror("ERROR pop: stack underflow");
	return 0;
}

char top(Stack* pStack)
{
	if ( !isEmpty(pStack) )
		return pStack->cKey; // wartosc szczytowa jest wskazywana przez pStack
	return 0;
}

void del(Stack** pStack) // usuwa szczyt ze stosu
{
	if ( !isEmpty(*pStack) )
	{
		Stack* p = *pStack; //pomocniczy wskaznik wskazujacy na element stosu
		*pStack = p->pNext; //pStack= pStack->pNext
		free(p); // nie gwaratuje NULL-a, zwolnienie pamieci
	}
	else
		perror("ERROR del: stack underflow");
}

int isEmpty(Stack* pStack)
{
	return !pStack;
}

/* implementacja niedynamiczna
#define MAXSTACK 20
char s[MAXSTACK] = { 0 };//stack
int nHead = 0; // wskaznik szczytu stosu -> pierwszy wolny w tablicy
void push(char c)
{
	if (nHead < MAXSTACK)
		s[nHead++] = c;
	else
		perror("ERROR push: stack overflow");
}
char pop() // zdejmij i zwroc szczyt
{
	if (!isEmpty()) {
		char c = top();
		del();
		return c;
	}
	perror("ERROR pop: stack underflow");
	return 0;
}
char top() 
{
	if (!isEmpty())
		return s[nHead - 1];
	return 0;
}
void del() 
{
	if (!isEmpty())
		nHead--;
	else
		perror("ERROR del: stack underflow");
}
int isEmpty() 
{
	return !nHead;
}
*/