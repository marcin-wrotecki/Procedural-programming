#include "sort.h"




void Przesianie( int* pTab, int l, int p );
void Sort( int*pTab, int l, int p );
void CopySerie( int* t, int* i, int* tmp, int* j, int nLast );
bool copy( int* t, int* i, int* tmp, int* j, int nLast );

void BubbleSort( int* pTab, int nSize )
{
	int temp;
	for( int i = 0; i < nSize; i++ )
	{
		for( int j = nSize - 1; j > i; j-- )
		{
			if( pTab[j - 1] > pTab[j] )
			{
				temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
			}
		}
	}
}

void InsertionSort( int* pTab, int nSize )
{
	int temp;
	int j;
	for( int i = 1; i < nSize; i++ )
	{
		temp = pTab[i];
		j = i - 1;
		while( temp < pTab[j] )
		{
			pTab[j + 1] = pTab[j--];
		}
		pTab[j + 1] = temp;
	}
}

void SelectSort( int* pTab, int nSize )
{
	int temp;
	int min;
	for( int i = 0; i < nSize - 1; i++ )
	{
		min = pTab[i];
		temp = i;
		for( int j = i + 1; j < nSize; j++ )
		{
			if( pTab[j] < min )
			{
				min = pTab[j];
				temp = j;
			}
		}

		pTab[temp] = pTab[i];
		pTab[i] = min;
	}


}

void MixedBubbleSort( int* pTab, int nSize )
{
	int temp;
	int l = 1;
	int k = nSize - 1;
	int p = nSize - 1;


	do
	{
		for( int j = p; j >= l; j-- )
		{
			if( pTab[j - 1] > pTab[j] )
			{
				temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}
		}
		l = k + 1;
		for( int j = l; j <= p; j++ )
		{
			if( pTab[j - 1] > pTab[j] )
			{
				temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}
		}

		p = k - 1;
	} while( l <= p );

}

void HalfInsertionSort( int* pTab, int nSize )
{
	int temp, l, p, m;
	for( int i = 1; i < nSize; i++ )
	{
		temp = pTab[i];
		l = 0;
		p = i - 1;
		while( l <= p )
		{
			m = (l + p) / 2;
			if( temp < pTab[m] )
				p = m - 1;
			else
				l = m + 1;
		}
		for( int j = i - 1; j >= l; j-- )
			pTab[j + 1] = pTab[j];
		pTab[l] = temp;
	}
}




void HeapSort( int* pTab, int nSize )
{
	int l = 0;
	int p = nSize - 1;
	int temp;
							 

	for( l = nSize / 2 ; l >= 0; l-- )
		Przesianie( pTab, l, p );

	for( p = nSize-1; p > 0; p-- )
	{
		temp = pTab[p];
		pTab[p] = pTab[0];
		pTab[0] = temp;
		Przesianie( pTab, 0, p-1 );
	}


}

void Przesianie( int* pTab, int l, int p )
{
	if( l == p ) return;
	int i = l;
	int j = 2 * i+1;
	int temp = pTab[i];
	while( j <= p )
	{
		if( j < p )
			if( pTab[j] < pTab[j + 1] ) j++;

		if( temp >= pTab[j] ) break;
		pTab[i] = pTab[j];
		i = j;
		j = 2 * i+1;
	}
	pTab[i] = temp;

}

void MergeSort( int* pTab, int* pTemp, int nSize, int l, int p )
{
	int middle = (l + p + 1) / 2;
	int i1, i2;


	if( middle - l > 1 ) MergeSort( pTab, pTemp, nSize, l, middle - 1 );
	if( p - middle > 0 ) MergeSort( pTab, pTemp, nSize, middle, p );
	i1 = l;
	i2 = middle;
	for( int i = l; i <= p; i++ )
		pTemp[i] = ((i1 == middle) || ((i2 <= p) && (pTab[i1] > pTab[i2]))) ? pTab[i2++] : pTab[i1++];
	for( int i = l; i <= p; i++ )
		pTab[i] = pTemp[i];
}


void QuickSort( int* pTab, int nSize )
{
	Sort( pTab, 0, nSize - 1 );
}

void Sort( int*pTab, int l, int p )
{
	int i = l;
	int j = p;
	int temp = pTab[(l + p) / 2];
	int stemp;
	do
	{
		while( pTab[i] < temp ) i++;
		while( temp < pTab[j] ) j--;
		if( i <= j )
		{
			stemp = pTab[i];
			pTab[i] = pTab[j];
			pTab[j] = stemp;
			i++;
			j--;
		}
	} while( i <= j );
	if( l < j ) Sort( pTab, l, j );
	if( i < p ) Sort( pTab, i, p );

}

void NaturalSort( int* t, int nSize )
{
	int k = 0; // index of array number 2 
	int j = 0; // index of array number 1
	int i = 0; // index of main array
	int series = 0; // one serie -> array is sorted

	int* tmp1 = ( int* ) malloc( nSize * sizeof( int ) );
	int* tmp2 = ( int* ) malloc( nSize * sizeof( int ));

	do
	{

		j = 0; // set index of array on the first element
		k = 0;
		i = 0;


		while( i < nSize ) //Separation will end, when index = nSize-1
		{
			while( i < nSize - 1 && t[i] <= t[i + 1] ) // while elements are sorted, copy them from main array to array number 1
				tmp1[j++] = t[i++];
			tmp1[j++] = t[i++]; // Copy one element          1 3 7' 3 ...           1 < 3; 3 < 7; [[7]] < 3       

			while( i < nSize - 1 && t[i] <= t[i + 1] ) //copy to t number 2. 
				tmp2[k++] = t[i++];

			if( i < nSize )
				tmp2[k++] = t[i++];
		}


		int t1_len = j; // length array - first measuement Dlugosc tab pom 1.
		int t2_len = k; // length array - second measuement 
		
		series = 0;  // For each merge number of seriel will be diffrent, so we have to set 0. Set 0 for index of arrays
		j = 0;
		k = 0;
		i = 0;

		// move elements from temp array to main array
		while( ( j < t1_len ) && ( k < t2_len ) )
		{
			bool seriesEnd = false;
			while( !seriesEnd )
			{
				if( tmp1[j] <= tmp2[k] ) // compare elements .          1 4 7' 3 9 11' 5 8 10' 4 5 6'
				{
					seriesEnd = copy( t, &i, tmp1, &j, t1_len ); // copy while it is not the end of serie
					if( seriesEnd )
						CopySerie( t, &i, tmp2, &k, t2_len ); // when serie is ended, remaining elements should be in next serie
				}
				else
				{
					seriesEnd = copy( t, &i, tmp2, &k, t2_len );
					if( seriesEnd )
						CopySerie( t, &i, tmp1, &j, t1_len );
				}
			}
			series++; // Increment number of series each time when compare two series
		}

		while( j < t1_len ) // In case when one of array wil end, copy remaining serie to second array
		{				   //if series switch, to is possible that remain more than one serie in second array
			CopySerie( t, &i, tmp1, &j, t2_len );
			series++;
		}
		while( k < t2_len )
		{
			CopySerie( t, &i, tmp2, &k, t2_len );
			series++;
		}



	} while( series != 1 ); // series == 1 means that array is sorted	
	free( tmp1 );
	free( tmp2 );
}

void CopySerie( int* t, int* i, int* tmp, int* j, int nLast )
{
	bool end = false; // serie should contain at least one element 
	do
	{
		end = copy( t, i, tmp, j, nLast );
	} while( !end );
}

bool copy( int* t, int* i, int* tmp, int* j, int nLast )
{
	t[( *i )++] = tmp[( *j )++];
	if( *j == nLast )
		return true;
	return tmp[*j - 1] > tmp[*j]; 
}

/*void QuickSort( int*pTab, int nSize, int l, int p )
{						   
	int i = l;
	int j = p;
	int temp = pTab[(l + p) / 2];
	int stemp;
	do
	{
		while( pTab[i] < temp ) i++;
		while( temp < pTab[j] ) j--;
		if( i <= j )
		{
			stemp = pTab[i];
			pTab[i] = pTab[j];
			pTab[j] = stemp;
			i++;
			j--;
		}
	} while( i <= j );
	if( l < j ) QuickSort( pTab, nSize,l, j );
	if( i < p ) QuickSort( pTab,nSize, i, p );

}

*/


