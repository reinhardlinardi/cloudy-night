
#pragma once
#include <stdbool.h>

typedef struct _Point Point;

struct _Point{
	
	int Row; /* absis   */
	int Col; /* ordinat */
};

/* *** Notasi Akses: Selektor POINT *** */
#define Row(P) (P).Row
#define Col(P) (P).Col
        
/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
Point Point_MakePOINT (int Row, int Col);
/* Membentuk sebuah POINT dari komponen-komponennya */

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void Point_BacaPOINT (Point * P);
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen Row dan Col dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
void Point_TulisPOINT (Point P);
/* Nilai P ditulis ke layar dengan format "(Row,Col)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya */
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(Row,Col)" */

/* *** Kelompok operasi relasional terhadap POINT *** */
bool Point_equal (Point P1, Point P2);
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
bool Point_notequal (Point P1, Point P2);
/* Mengirimkan true jika P1 tidak sama dengan P2 */

/* *** Kelompok menentukan di mana P berada *** */
bool Point_IsOrigin (Point P);
/* Menghasilkan true jika P adalah titik origin */
bool Point_IsOnSbX (Point P);
/* Menghasilkan true jika P terletak Pada sumbu Row */
bool Point_IsOnSbY (Point P);
/* Menghasilkan true jika P terletak pada sumbu Col */
int Point_Kuadran (Point P);
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
Point Point_NextX (Point P);
/* Mengirim salinan P dengan absis ditambah satu */
Point Point_NextY (Point P);
/* Mengirim salinan P dengan ordinat ditambah satu */
Point Point_PlusDelta (Point P, int deltaX, int deltaY);
/* Mengirim salinan P yang absisnya adalah Row(P) + deltaX dan ordinatnya adalah Col(P) + deltaY */
Point Point_MirrorOf (Point P, bool SbX);
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu Row */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Col */
int Point_Panjang (Point P1, Point P2);
/* Menghitung panjang garis yang dibentuk P1 dan P2 */
/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
/* Tuliskan spec fungsi yang lebih tepat. */
void Point_Geser (Point *P, int deltaX, int deltaY);
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
void Point_GeserKeSbX (Point *P);
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu Row dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu Row. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
void Point_GeserKeSbY (Point *P);
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Col dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Col. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
void Point_Mirror (Point *P, bool SbX);
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu Row */
/* Jika SbX false maka dicerminkan terhadap sumbu Col */
