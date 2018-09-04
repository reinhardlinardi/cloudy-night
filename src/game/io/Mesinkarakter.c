/* File: mesinkarakter.c */
/* Implementasi Mesin Karakter */

#include <stdio.h>
#include <signal.h>
#include "Mesinkarakter.h"

char CC;
char prev_CC;
bool EOP;

static FILE * pita;
static int retval;

void START(char *filename) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != END maka EOP akan padam (false).
          Jika CC = END maka EOP akan menyala (true) */

	/* Algoritma */
	pita = fopen(filename,"r");
	ADV(pita);
}

void ADV() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela =
          CC, CC != END
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = END.
		  Jika  CC = END maka EOP akan menyala (true) */

	/* Algoritma */
	prev_CC=CC;
	
	retval = fscanf(pita,"%c",&CC);
	
	//Send segmentation fault signal if blank line detected
	if((prev_CC == CC) && (CC == '\n')) raise(SIGSEGV);
	
	EOP = (CC == END);
	if (EOP) {
		fclose(pita);
	}
}