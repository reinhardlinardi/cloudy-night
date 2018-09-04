/* File: mesinkarakter.h */
/* Definisi Mesin Karakter */

#ifndef __MESIN_KARAKTER_H_
#define __MESIN_KARAKTER_H_

#include <stdbool.h>
#include <signal.h>

#define END '@'
#define ENDLINE '\n'

/* State Mesin */
extern char CC;
extern bool EOP;

void START(char *filename);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita
          Jika CC != END maka EOP akan padam (false)
          Jika CC = END maka EOP akan menyala (true) */

void ADV();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = CC, CC != END
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = END
          Jika  CC = END maka EOP akan menyala (true) */

#endif
