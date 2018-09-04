// Time.c
 
#include <stdio.h>
#include "Time.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
bool Time_Valid (int H, int M, int S)
{
	return ((H >= 0 && H < 24) && (M >=0 && M < 60) && (S >=0 && S < 60));
			
}
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
void Time_Create (int HH, int MM, int SS, Time * T)
{

	Hour(*T) = HH;
	Minute(*T) = MM;
	Second(*T) = SS;

}
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */



/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long Time_HourToSecond (Time T)
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */
{
		
	return ((Hour(T)*3600) + (Minute(T)*60) + (Second(T))%86400);

}
	

Time Time_SecondToHour (long N)
/* Mengirim  konversi detik ke JAM */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus:
   N1 = N mod 86400, baru N1 dikonversi menjadi JAM */
{
		
		Time J;
		long N1;
		
		N1 = N%86400;
		Hour(J) = N1/3600;
		N1 = N1%3600;
		Minute(J) = N1/60;
		N1=N1%60;
		Second(J) = N1;
	
		return J;
}
/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
bool Time_Equal (Time T1, Time T2)
/* Mengirimkan true jika J1=J2, false jika tidak */
{
	return (Time_HourToSecond(T1) == Time_HourToSecond(T2));
}

bool Time_NotEqual (Time T1, Time T2)
/* Mengirimkan true jika J1 tidak sama dengan J2 */
{
	return (Time_HourToSecond(T1) != Time_HourToSecond(T2));
}

bool Time_LessThan (Time T1, Time T2)
/* Mengirimkan true jika J1<J2, false jika tidak */
{
	return (Time_HourToSecond(T1) < Time_HourToSecond(T2));

}

bool Time_GreaterThan (Time T1, Time T2)
/* Mengirimkan true jika J1>J2, false jika tidak */
{
	return (Time_HourToSecond(T1) > Time_HourToSecond(T2));
}


/* *** Operator aritmatika JAM *** */
Time Time_NextSecond (Time T)
/* Mengirim 1 detik setelah J dalam bentuk JAM */
{
	return (Time_SecondToHour(Time_HourToSecond(T)+1));
}


Time Time_NextNSecond (Time T, int N)
/* Mengirim N detik setelah J dalam bentuk JAM */
{
	return (Time_SecondToHour(Time_HourToSecond(T)+N));
}

Time Time_PrevSecond (Time T)
/* Mengirim 1 detik sebelum J dalam bentuk JAM */
{
	
		long det = Time_HourToSecond(T);
		det--;
		if(det <=0) det+=86400;
		
		return(Time_SecondToHour(det));
	}

Time time_PrevNSecond (Time T, int N)
/* Mengirim N detik sebelum J dalam bentuk JAM */
{
		
		long det = Time_HourToSecond(T);
		det-=N;
		if(det <=0) det+=86400;
		
		return(Time_SecondToHour(det));
}

/* *** Kelompok Operator Aritmetika *** */

long Time_Duration (Time JAw, Time JAkh)
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
{
		long saw, sakh;
		saw = Time_HourToSecond(JAw);
		sakh = Time_HourToSecond(JAkh);
		
		if (saw>sakh) sakh+=86400;
		return sakh-saw;
}
	
