#pragma once

#include <stdlib.h>

typedef struct {
	char Mem[25][81]; //biar bisa mulai dari indeks 1,1
    int NRowEff;
	int NColEff;
} Matrix;

#define Matrix_CoordX(M) (M).CoordX
#define Matrix_CoordY(M) (M).CoordY
#define Matrix_NRowEff(M) (M).NRowEff
#define Matrix_NColEff(M) (M).NColEff
#define Matrix_Elmt(M,i,j) (M).Mem[(i)][(j)]

void Matrix_CreateEmpty (int NR, int NC, Matrix * M);
/* I.S. : Sembarang
 * F.S. : Terdapat matriks kosong sebesar NR x NC
 */