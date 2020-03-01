#include "dstack.h"
using namespace std;


DStack* dInitStack()
{
	return NULL;
}

void dRemoveStack(DStack ** pStack)
{
	while ( !disEmpty( *pStack ) )
		ddel(pStack);
	*pStack = NULL;
}


void dpush(double val, DStack** pStack)
{
	DStack* v = (DStack*)malloc(sizeof(DStack));//alokowanie pewnej ilosc bajtow - rozmiaru pudelka stack, malloca trzeba zrzutowac 
											 //na to jakigo typ ma byc wskazni

	if ( v ) // if( v!=NULL)
	{
		memset( v, 0, sizeof(DStack) ); //jak dostac sie do pol struktury
									 //(*v).cKey=c//operator kropka ma wiekszzy priorytet niz gwiazdka wiec musi byc w nawiasie
		v->dKey = val; //operator strzalki, bo v wskazuje, zamiast tego wyzej
					 //dowiazanie
		v->pNext = *pStack;
		*pStack = v;
	}
	else
		perror("ERROR push: stack overflow");
}

double dpop (DStack** pStack) // zdejmij i zwroc szczyt
{

	if ( !disEmpty(*pStack) ) {
		double c = dtop(*pStack);
		ddel(pStack);
		return c;
	}
	else 
	{
		perror("ERROR pop: stack underflow");
		return 0;
	}
}

double dtop(DStack* pStack)
{
	if ( !disEmpty(pStack) )
		return pStack->dKey; // wartosc szczytowa jest wskazywana przez pStack
	return 0;
}

void ddel(DStack** pStack) // usuwa szczyt ze stosu
{
	if ( !disEmpty(*pStack) )
	{
		DStack* p = *pStack; //pomocniczy wskaznik wskazujacy na element stosu
		*pStack = p->pNext; //pStack= pStack->pNext
		free(p); // nie gwaratuje NULL-a, zwolnienie pamieci
	}
	else
		perror("ERROR del: stack underflow");
}

int disEmpty(DStack* pStack)
{
	return !pStack;
}
