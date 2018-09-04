#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Shuffle.h"

static void
_Shuffle_Swap (char *a, char *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void
_Shuffle_Randomize (char arr[], int n)
{
    srand ( time(NULL) );
 
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        _Shuffle_Swap(&arr[i], &arr[j]);
    }
}

Stack
Shuffle_MoveCreate (int a, int b, int f)
/* a = jumlah A
 * b = jumlah B
 * f = jumlah F
 */
{
	Stack S;
	Stack_Infotype Q;
	Queue_Infotype *cc;
	int i,j,n;
	
	n = a+b+f;
	cc = (Queue_Infotype *) malloc (n*sizeof(Queue_Infotype));
	i=0;
	for (j=1;j<=a;j++)
	{
		cc[i] = 'A';
		i++;
	}
	for (j=1;j<=b;j++)
	{
		cc[i] = 'B';
		i++;
	}
	for (j=1;j<=f;j++)
	{
		cc[i] = 'F';
		i++;
	}
	
	_Shuffle_Randomize(cc,n);
	
	Stack_CreateEmpty(&S);
	
	i=0;
	while (i<n)
	{
		Queue_CreateEmpty (&Q);
		j=0;
		while (j<4 && i<n)
		{
			Queue_Add(&Q,cc[i]);
			j++;
			i++;
		}
		Stack_Push(&S,Q);
	}
	return S;
}