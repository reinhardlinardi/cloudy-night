/* File : stacklist.h */
#ifndef _STACKLIST_H
#define _STACKLIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "Queue.h"
/* Konstanta */
#define Nil NULL

/* Deklarasi Stack_Infotype */
typedef Queue Stack_Infotype;

/* Stack dengan representasi berkait dengan pointer */
typedef struct tElmtStack * StackAddress;
typedef struct tElmtStack { 
	Stack_Infotype Info;
	StackAddress Next; 
} ElmtStack; 

/* Type stack dengan ciri TOP : */
typedef struct { 
	StackAddress TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* Selektor */
#define Stack_Top(S) (S).TOP
#define Stack_InfoTop(S) (S).TOP->Info 
#define Stack_Next(P) (P)->Next
#define Stack_Info(P) (P)->Info

/* Prototype manajemen memori */
void Stack_Alokasi (StackAddress *P, Stack_Infotype X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void Stack_Dealokasi (StackAddress P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */ 

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
bool Stack_IsEmpty (Stack S);
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
void Stack_CreateEmpty (Stack * S);
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack S yang kosong */
void Stack_Push (Stack * S, Stack_Infotype X);
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void Stack_Pop (Stack * S, Stack_Infotype * X);
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */

#endif
