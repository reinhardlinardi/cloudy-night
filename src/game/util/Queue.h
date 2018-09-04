/* File : queuelist.h */
/* Representasi queue dengan list berkait dengan first (HEAD) dan last (TAIL) */
#ifndef _QUEUELIST_H
#define _QUEUELIST_H
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
/* Konstanta */
#define Nil NULL

/* Deklarasi Queue_Infotype */
typedef char Queue_Infotype;

/* Queue dengan representasi berkait dengan pointer */
typedef struct tElmtQueue * QueueAddress;
typedef struct tElmtQueue { 
	Queue_Infotype Info;
	QueueAddress Next; 
} ElmtQueue; 

/* Type queue dengan ciri HEAD dan TAIL : */
typedef struct { 
	QueueAddress HEAD;  /* alamat penghapusan */
	QueueAddress TAIL;  /* alamat penambahan */
} Queue;

/* Selektor */
#define Queue_Head(Q) (Q).HEAD
#define Queue_Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).HEAD->Info
#define InfoTail(Q) (Q).TAIL->Info
#define Queue_Next(P) (P)->Next
#define Queue_Info(P) (P)->Info

/* Prototype manajemen memori */
void Queue_Alokasi (QueueAddress *P, Queue_Infotype X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void Queue_Dealokasi (QueueAddress  P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
bool Queue_IsEmpty (Queue Q);
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
int Queue_NbElmt(Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
/*** Kreator ***/
void Queue_CreateEmpty(Queue * Q);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Add/Delete ***/
void Queue_Add (Queue * Q, Queue_Infotype X);
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void Queue_DelFirst(Queue * Q, Queue_Infotype * X);
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
void Queue_DelLast(Queue *Q, Queue_Infotype *X);
#endif
