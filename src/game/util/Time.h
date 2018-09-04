
// Time.h

#pragma once

#include <stdbool.h>

/* *** Definisi TYPE JAM <HH:MM:SS> *** */
typedef struct _Time Time;

struct _Time
{
	int HH; /* integer [0..23] */
	int MM; /* integer [0..59] */
	int SS; /* integer [0..59] */
};

/* *** Notasi Akses: selektor JAM *** */
#define Hour(J) (J).HH
#define Minute(J) (J).MM
#define Second(J) (J).SS

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
bool Time_Valid (int H, int M, int S);
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
void Time_Create (int HH, int MM, int SS, Time * self);
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */



/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long Time_HourToSecond (Time self);
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */

Time Time_SecondToHour (long N);
/* Mengirim  konversi detik ke JAM */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus:
   N1 = N mod 86400, baru N1 dikonversi menjadi JAM */

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
bool Time_Equal (Time J1, Time J2);
/* Mengirimkan true jika J1=J2, false jika tidak */
bool Time_NotEqual (Time J1, Time J2);
/* Mengirimkan true jika J1 tidak sama dengan J2 */
bool Time_LessThan (Time J1, Time J2);
/* Mengirimkan true jika J1<J2, false jika tidak */
bool Time_GreaterThan (Time J1, Time J2);
/* Mengirimkan true jika J1>J2, false jika tidak */
/* *** Operator aritmatika JAM *** */
Time Time_NextSecond (Time J);
/* Mengirim 1 detik setelah J dalam bentuk JAM */
Time Time_NextNSecond (Time J, int N);
/* Mengirim N detik setelah J dalam bentuk JAM */
Time Time_PrevSecond (Time J);
/* Mengirim 1 detik sebelum J dalam bentuk JAM */
Time Time_PrevNSecond (Time J, int N);
/* Mengirim N detik sebelum J dalam bentuk JAM */
/* *** Kelompok Operator Aritmetika *** */
long Time_Duration (Time JAw, Time JAkh);
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */


