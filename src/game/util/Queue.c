#include "Queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void Queue_Alokasi (QueueAddress *P, Queue_Infotype X)
{
	*P = (ElmtQueue*)malloc(sizeof(ElmtQueue));
	if (*P != Nil)
	{
		Queue_Info(*P) = X;
		Queue_Next(*P) = Nil;
	}
}
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void Queue_Dealokasi (QueueAddress  P)
{
	free(P);
}
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
bool Queue_IsEmpty (Queue Q)
{
	return (Queue_Head(Q) == Nil && Queue_Tail(Q) == Nil);
}
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
int Queue_NbElmt(Queue Q)
{
	QueueAddress P;
	int count = 0;

	if (Queue_IsEmpty(Q))
	{
		return 0;
	}
	else 
	{
		P = Queue_Head(Q);
		do
		{
			count++;
			P = Queue_Next(P);
		} while (P!=Nil);
		return count;
	}
}
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
/*** Kreator ***/
void Queue_CreateEmpty(Queue * Q)
{
	Queue_Head(*Q) = Nil;
	Queue_Tail(*Q) = Nil;
}
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Add/Delete ***/
void Queue_Add (Queue * Q, Queue_Infotype X)
{
	QueueAddress P,N;
	Queue_Alokasi(&P,X);
	if (P!=Nil)
	{
		if (Queue_IsEmpty(*Q))
		{
			Queue_Head(*Q) = P;
			Queue_Tail(*Q) = P;
		}
		else
		{
			N = Queue_Tail(*Q);
			Queue_Next(N) = P;
			Queue_Tail(*Q) = P;
		}
	}
}
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void Queue_DelFirst(Queue * Q, Queue_Infotype * X)
{
	QueueAddress P;
	P = Queue_Head(*Q);
	if (Queue_Head(*Q) == Queue_Tail(*Q)) /*element hanya 1*/
	{
		Queue_Tail(*Q) = Nil; /*jadi kosong*/
	}
	Queue_Head(*Q) = Queue_Next(Queue_Head(*Q));
	Queue_Next(P) = Nil;
	*X = Queue_Info(P);
	Queue_Dealokasi(P);
}
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */

void Queue_DelLast(Queue *Q, Queue_Infotype *X)
{
	assert(Q != NULL);
	if (Queue_IsEmpty(*Q))
	{
		/*
		printf("Queue kosong, tidak bisa delete move!\n");
		*/
	}
	else
	{
		QueueAddress Prec;
		Prec = Queue_Head(*Q);
		if (Queue_Head(*Q) == Queue_Tail(*Q))
		{
			Queue_DelFirst(Q,X);
		}
		else
		{
			while(Queue_Next(Prec)!=Queue_Tail(*Q))
			{
				Prec = Queue_Next(Prec);
			}
			*X = InfoTail(*Q);
			Queue_Next(Prec) = NULL;
			Queue_Dealokasi(Queue_Tail(*Q));
			Queue_Tail(*Q) = Prec;
		}
	}
}