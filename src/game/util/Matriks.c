#include "Matriks.h"
#include <assert.h>

void Matrix_CreateEmpty (int NR, int NC, Matrix * M)
{
	assert(M != NULL);
	assert(NR > 0);
	assert(NC > 0);
	
	Matrix_NRowEff(*M) = NR;
	Matrix_NColEff(*M) = NC;
}