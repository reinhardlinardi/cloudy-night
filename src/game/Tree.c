#include "Tree.h"
#include <stdlib.h>
#include <stdio.h>

/* *** Konstruktor *** */
BinTree Tree (int Akar, BinTree L, BinTree R)
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
{
	BinTree P=AlokNode(Akar);
	if(P!=Nil)
	{
		Akar(P)=Akar;
		Left(P)=L;
		Right(P)=R;
	}
	return P;
}
void MakeTree (int Akar, BinTree L, BinTree R, BinTree *P)
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R 
		jika alokasi berhasil. P = Nil jika alokasi gagal. */
{
	*P=Tree(Akar,L,R);
}
		
/* Manajemen Memory */
addrNode AlokNode (int X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	addrNode P=(addrNode) malloc (sizeof(Node));
	if(P!=Nil)
	{
		Akar(P)=X;
		Left(P)=Nil;
		Right(P)=Nil;
	}
	return P;
}
void DealokNode (addrNode P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
{
	free(P);
}
/* *** Predikat-Predikat Penting *** */
bool IsTreeEmpty (BinTree P)
/* Mengirimkan true jika P adalah pohon biner kosong */
{
	return P==Nil;
}
bool IsTreeOneElmt (BinTree P)
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
{
	return (P!=Nil && Left(P)==Nil && Right(P)==Nil);
}
bool IsUnerLeft (BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
{
	return (Left(P)!=Nil && Right(P)==Nil);
}
bool IsUnerRight (BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
{
	return (Right(P)!=Nil && Left(P)==Nil);
}
bool IsBiner (BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/
{
	return (Right(P)!=Nil && Left(P)!=Nil); 
}
bool SearchTree (BinTree P, int X)
/* Mengirimkan true jika ada node dari P yang bernilai X */
{
	if(IsTreeEmpty(P))
	{
		return false; 
	}
	else
		if(Akar(P)==X)
			return true;
		else
			return (SearchTree(Left(P),X) || SearchTree(Right(P),X));
}

void AddChild(BinTree *P,int X, int Y, bool Kiri)
{
	if(X==Akar(*P))
	{
		addrNode T=AlokNode(Y);
		if(Kiri)
		{
			Left(*P)=T;
		}
		else
			Right(*P)=T;
	}
	else
	{
		if(SearchTree(Left(*P),X))
		{
			AddChild(&Left(*P),X,Y,Kiri);
		}
		else
		{
			AddChild(&Right(*P),X,Y,Kiri);
		}
		
	}
}

void PrintTreeA(BinTree P, int h, int x)
{
	if(IsTreeEmpty(P))
	{
	}
	else{
		
	for(int i=1;i<=x*h;i++)
	{
		printf(" ");
		}
	printf("%d\n",Akar(P));
	PrintTreeA(Left(P),h,x+1);
	PrintTreeA(Right(P),h,x+1);
	}
}
void PrintTree(BinTree P, int h)
{
	PrintTreeA(P,h,0);
}



void Generate_SkillTree(BinTree *P)
{
	int i;
	int j=1;
	bool f=true;
	*P=AlokNode(1);
	for(i=1;i<=7;i++)
	{
		j++;
		AddChild(P,i,j,f);
		j++;
		AddChild(P,i,j,!f);
	}
}

void Child(BinTree P,int X,int *L,int *R)
{
	if(X==Akar(P) && !IsTreeOneElmt(P))
	{
		*L=Akar(Left(P));
		*R=Akar(Right(P));
	}
	else if(X==Akar(P) && IsTreeOneElmt(P))
	{
		*L=0;
		*R=0;
	}
	else
	{
		if(SearchTree(Left(P),X))
		{
			Child(Left(P),X,L,R);
		}
		else
		{
			Child(Right(P),X,L,R);
		}
	}
}
