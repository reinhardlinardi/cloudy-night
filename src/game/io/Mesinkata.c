#include <stdio.h>
#include "Mesinkata.h"

bool EndKata;
Kata CKata;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
I.S. : CC sembarang
F.S. : CC ≠ BLANK atau CC = END */
{
	/* Kamus Lokal */
	/* Algoritma */
	while ((CC == ENDLINE) && (CC != END)) ADV();
	/* CC != BLANK or CC = END */
}

void STARTKATA(char* filename)
/* I.S. : CC sembarang
F.S. : EndKata = true, dan CC = END;
atau EndKata = false, CKata adalah kata yang sudah
diakuisisi,
CC karakter pertama sesudah karakter terakhir kata */
{
	/* Kamus Lokal */
	/* Algoritma*/
	START(filename);
	IgnoreBlank();
	
	if (CC == END)	EndKata = true;
	else /* CC != END */
	{
		EndKata = false;
		SalinKata();
	}
}

void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
CC adalah karakter pertama dari kata berikutnya,
mungkin END
Proses : Akuisisi kata menggunakan procedure SalinKata */
{
	/* Kamus Lokal */
	/* Algoritma*/
	IgnoreBlank();
	
	if (CC == END) EndKata = true;
	else /* CC != END */
	{
		SalinKata();
		IgnoreBlank();
	}
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
I.S. : CC adalah karakter pertama dari kata
F.S. : CKata berisi kata yang sudah diakuisisi;
CC = BLANK atau CC = END;
CC adalah karakter sesudah karakter terakhir yang
diakuisisi */
{
	/* Kamus Lokal */
	int i = 0; /* inisialisasi */
	int j;
	
	for(j=0;j<CKata.len;j++) CKata.c[j]='\0';
	
	/* Algoritma*/
	while(1)
	{
		CKata.c[i] = CC;
		ADV();
		
		if ((CC == END) || (CC == ENDLINE)) break;
		else i++;
	}
	
	/* CC = END or CC = BLANK */
	CKata.len = ++i;
}
