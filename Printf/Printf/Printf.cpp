// Printf.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdio.h>
#include <stdarg.h>

int Printf(const char* sFormat, ...); 
int PrintfV(const char* sFormat, va_list arg_list);
void outDec(int);
void outNum( int);
void outDouble (double);
void outChar(char );
void outStr(char* pStr);


int main()
{
	int n = -0;
	char c = '$';
	double x = 1200000000.12345556;
	double y = -.12;
	double z = -1.5;
	const char* str = "to jest string";


	Printf("%s\n%f\n%c\nn=%d \n\\% /\ny=%f\n\nz=%f", str, x, c, n, y, z);

	return 0;
   
}

int Printf(const char* sFormat, ...)
{
	//initialize variable arguments
	
	// set the pointer at the beggining of the arg list
	// and get the first argument from the args list
	
	// wywolanie funkcji przetwarzajacej res = printf()
	// reset variable arguments
	va_list args;
	va_start(args, sFormat);
	int res = PrintfV(sFormat, args);
	va_end(args);
	return res;

}
int PrintfV(const char* sFormat, va_list arg_list)
{
	char c; // nasz napis wejsciowy przetwarzamy do jego konca- trafienia na znak 0 

	while (c = *sFormat++) // wyciagniecie spod wskaznia i przesuniecie, moge go przesuwac bo wskaznik jest przekazywany jako kopia oryginalu
	{
		switch (c)
		{
		case '%': switch (c = *sFormat++)
				{
					case 'c': outChar(va_arg(arg_list, char)); break;
					case 's': outStr(va_arg(arg_list, char*)); break;
					case 'd': outDec(va_arg(arg_list, int)); break;
					case 'f': outDouble(va_arg(arg_list, double)); break;
					default: outChar('%'); outChar(c); break;
				}
				 break;		//przypadek po procencie
		case '`': c = '\''; // bez breaka bo sie nie wypisze
		default: outChar(c); //w pozostalych przypadkach wypisac znak c
		}
		
		
	}
	return 0;
}
void outDec(int x)
{
	if (x < 0)
	{
		outChar('-');
		x = -x;
	}
	else if (!x)
	{
		outChar('0');
		return; 
	}
		outNum(x);


}
void outNum( int x)
{
	if (x > 0)
	{
		outNum(x / 10);
		outChar(x % 10 + '0');// bo podajemy w ASCII wiec aby by³a liczba musimy dodac to
	}
}
void outDouble(double x)
{
	if (x < 0)
	{
		outChar('-');
		x = -x;
	}
	else if (!x)
	{
		outChar('0');
	}
	
	
		double mantysa = x - (int)x;
		outNum((int)x);
		outChar('.');
		mantysa *= 1e9;
		
		int temp = (int)mantysa;
		while(!(temp%10))
		{
			temp = temp / 10;
		}
		outNum((temp));
		
	


}
void outChar(char c)
{
	putchar(c);
}
void outStr(char* pStr)
{
	while (*pStr)
	{
		outChar(*pStr++);
	}
}

//Zadanie:
//
//implementacja uproszczonej funckji printf : %c- jeden znak, %d- calkowita, %f- double , %s- lancuch znakow
//oraz zamienia ` (klawisz ~)  na ' (klawisz ")
//
//zdefiniuj funkcje Printf() i PrintfV(), pierwszy parametr to staly lancuch znakowy

//Zdefiniuj funkcje :
//outDec() - znakowo wypisuje liczbe calkowita
//outNum() - wypisuje znakowo liczbe >0
//outDouble() - wypisuje znakowo liczbe double
//outChar() - wypisuje znak
//outStr() - wypisuje znakowo string
//kazda z nich to void i nalezy w nich zdefiniowac odpowiednie parametry