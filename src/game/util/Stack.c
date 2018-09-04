#include <stdio.h>
#include "Stack.h"

/* Prototype manajemen memori */
void Stack_Alokasi (StackAddress *P, Stack_Infotype X)
{
	*P = (ElmtStack*)malloc(sizeof(ElmtStack));
	if (*P != Nil)
	{
		Stack_Info(*P) = X;
		Stack_Next(*P) = Nil;
	}
}
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void Stack_Dealokasi (StackAddress P)
{
	free(P);
}
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */ 

/* ********* PROTOTYPE RE
PRESENTASI LOJIK STACK ***************/
bool Stack_IsEmpty (Stack S)
{
	return (Stack_Top(S) == Nil);
}
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
void Stack_CreateEmpty (Stack * S)
{
	Stack_Top(*S) = Nil;
}
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack S yang kosong */
void Stack_Push (Stack * S, Stack_Infotype X)
{
	StackAddress P,N;
	Stack_Alokasi(&P,X);
	if (P != Nil)
	{
		N = Stack_Top(*S);
		Stack_Top(*S) = P;
		Stack_Next(P) = N;
	}
}
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void Stack_Pop (Stack * S, Stack_Infotype * X)
{
	StackAddress P;
	P = Stack_Top(*S);
	Stack_Top(*S) = Stack_Next(P);
	Stack_Next(P) = Nil;
	*X = Stack_Info(P);
    Stack_Dealokasi(P);
}
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
