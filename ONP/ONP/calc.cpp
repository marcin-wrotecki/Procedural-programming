
//Celem dzialania programu jest przeksztalcenie wprowadzonego rownania do postaci Odwrotnej Notacji Polskiego i wyliczenie go
//The purpose of this program is to convert equation to reverse Polish notation and solve it
#include "stack.h"
#include "dstack.h"

#define DOT '.'

double  GetNum(); //wczytanie liczby rzeczywistej
char    GetOper(); //wczytanie operatora
void	SkipSpaces(); //pomijanie spacji wiod¹cych
int		isOper( char c ); //czy jest operatorem
int		isDigit( char c ); //czy jest cyfra
int		prior( char cOper ); //priorytet
double	Eval( char oper, double arg1, double arg2 ); 
void readBrecket( Stack** pStack);

double	Calc();


int main( int argc, char* argv[] )
{
	printf( "Podaj dzialanie, ktore chcesz obliczyc: \n" );
	printf( "Wynik: %.4f \n", Calc() ); 
	
    return 0;
}


//=======================================
double  GetNum()
{
	char c;
	double res = 0; //result
	
	SkipSpaces();
	while( isDigit( c=getchar() ) )//(wczytanie znaku i sprawdzenie czy jest znakiem cyfry) // dopoki nie koniec liczby
		res = res * 10 + (c - '0');
	if( c == DOT )
	{
		double coef = 0.1;
		while ( isDigit( c=getchar() ) )
		{
			res = res + coef*(c - '0');
			coef *= 0.1;
		}
		//wczytanie czesci ulamkowej
	}
	ungetc(c, stdin);
	return res;

}
//=======================================
char    GetOper()
{
	SkipSpaces();
	return getchar();
}
//=======================================
void	SkipSpaces()
{
	char c;
	while ( ( c = getchar() ) == ' ' );
	ungetc(c, stdin);
	//ungetc()- umozliwa cofanie z powrotem do pliku znaków
}
//=======================================
int		isOper( char c )
{
	switch ( c )
	{
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '^': return 1;
	}
	return 0;
// sprawdza czy c jest znakiem operatora: + - * / ^
// switch
//	zwraca 0 lub 1
}
//=======================================
int		isDigit( char c )
{
	return ( c >= '0' ) && ( c <= '9');
	// sprawdza czy c jest liczb¹, jedna linijka- zwraca 1 gdy c jest znakiem cyfry lub 0 gdy nie

}
//=======================================
int		prior( char cOper )
{	 
	switch ( cOper )
	{
		//case '(': return 0;
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	}
	return 0;
	//switch
}
//=======================================
double	Eval( char oper, double arg1, double arg2 )
{
	switch ( oper )
	{
	case '+': return arg1 + arg2;
	case '-': return arg1 - arg2;
	case '*': return arg1 * arg2;
	case '/':
		if ( arg2 >= 1e-14 )
			return arg1 / arg2;
		perror("ERROR: division by 0!!!\n\n");
		return 0;

	case '^': return pow( arg1, arg2 );
	default:
		return 0;
	}

	//switch
}
void readBrecket( Stack** pStack )
{
	char c;
	while ( ( c = getchar() ) == '(' )// dopoki c- wskaznik zeby przekazac oryginal- jest nawiasem to wpisuje go na stos
		push( c, pStack );
	ungetc(c, stdin); // zwracanie do bufora
}
//=======================================
double	Calc() 
{
	DStack* pDStack = dInitStack(); // mozna tez to zdefiniowac w stack
	Stack* pStack = InitStack();

	char c; //inicjalizuje zero, zeby moc przeslac do funkcji readBrecket

	readBrecket( &pStack );

	dpush( GetNum(), &pDStack ); // jesli bedzie liczba to wpisze liczbe, a jesli minus to zero- zwrocenie do bufora w getnumie

	while ( isOper( c = GetOper() ) )
	{
		while ( prior(c) <= prior( top( pStack ) ) )
		{
			double arg = dpop( &pDStack );
			dpush( Eval(pop(&pStack), dpop( &pDStack ), arg ), &pDStack );	//po pobraniu arg pobiera argument, ktory znajduje sie nizej na stosie
		}
		push( c, &pStack );//wpisuje na stos operator

		readBrecket( &pStack );

		dpush( GetNum(), &pDStack );

		while ( ( c = getchar() ) == ')' )
		{
			while ( ( c = pop( &pStack ) ) != '(' )
			{
				//char cOper = pop( &pStack );	// pobiera operator i usuwa go ze szczytu

				double arg = dpop( &pDStack );		
				
				dpush( Eval( c, dpop( &pDStack ), arg ), &pDStack );
			}
//			pop( &pStack );//zdejmuje nawias otwierajacy ze stosu

		}
		ungetc(c, stdin);
	}
	
	while ( !isEmpty( pStack ) )
	{
		

		double arg = dpop( &pDStack );

		dpush( Eval( pop(&pStack), dpop( &pDStack ), arg ), &pDStack );
	}

	double res = dtop( pDStack ); // przed usunieciem stosu zapisuje jego szczyt

	RemoveStack( &pStack ); 
	dRemoveStack( &pDStack );


	return res;
}
	//ONP

//=======================================

//w domu zimplementowac funkcje stosu w stack.cpp oraz zaimlpementowac kolejno funkcje tutaj


/*void	Calc() // a razie zamienia do odwrotnej otacji polskiej
{	
	DStack* pStack = dInitStack(); // mozna tez to zdefiniowac w stack
	char c;

	printf("%0.2lf", GetNum());
	while (isOper(c = GetOper()))
	{
		while (prior(c) <= prior(dtop(pStack)))
		{
			putchar(dpop(&pStack));
			//sciagnac ze stosu i wypisaæ
		}

		dpush(c,&pStack);// nalezy przekazac wskaznik, jesli tego sie nie zrobi to nie zmieni sie wartosc pStack

		printf(" %0.2lf", GetNum());
	}
	
		while(!disEmpty(pStack))
			putchar(dpop(&pStack));
		printf("\n");
		dRemoveStack(&pStack);
	//ONP
	}*/