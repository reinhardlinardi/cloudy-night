/* ADT Pohon Biner */
/* Implementasi dengan menggunakan pointer */
/* Penamaan type int, type addrNode, dan beberapa fungsi disesuikan 
   karena melibatkan modul list rekursif. */
#ifndef TREE_H
#define TREE_H

#define Nil NULL
#include <stdbool.h>
/* #define Nil NULL */ /* konstanta Nil sesuai pada modul listrek */

/* *** Definisi Type Pohon Biner *** */
/* type int sesuai pada modul listrek */
typedef struct tNode *addrNode;
typedef struct tNode { 
	int info;
	addrNode left;
	addrNode right;
} Node;

/* Definisi PohonBiner : */
/* Pohon Biner kosong : P = Nil */
typedef addrNode BinTree;
 
/* *** PROTOTYPE *** */

/* *** Selektor *** */
#define Akar(P) (P)->info
#define Left(P) (P)->left
#define Right(P) (P)->right

/* *** Konstruktor *** */
BinTree Tree (int Akar, BinTree L, BinTree R); 
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
void MakeTree (int Akar, BinTree L, BinTree R, BinTree *P);
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R 
		jika alokasi berhasil. P = Nil jika alokasi gagal. */
		
/* Manajemen Memory */
addrNode AlokNode (int X);
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokNode (addrNode P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */

/* *** Predikat-Predikat Penting *** */
bool IsTreeEmpty (BinTree P);
/* Mengirimkan true jika P adalah pohon biner kosong */
bool IsTreeOneElmt (BinTree P);
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
bool IsUnerLeft (BinTree P);
/* Mngirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
bool IsUnerRight (BinTree P);
/* Mngirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
bool IsBiner (BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/

bool SearchTree (BinTree P, int X);
// Mengirimkan true jika X ada dalam P
void PrintTree(BinTree, int h);
// Menampilkan Tree; 

void AddChild(BinTree *P, int X, int Y, bool Kiri);
// Menambah anak pada node dimana Akar(*P)==X jika Kiri=true maka akan ditambahkan pada kiri dari Node, jika false akan di kanan
void Generate_SkillTree(BinTree *P);
// Menghasilkan SkillTree yang sudah ditentukan.
void Child(BinTree P,int X,int * L, int * R);
// L akan berisi Anak kiri dari X dan R akan  berisi anak kanan dari X;

#endif
