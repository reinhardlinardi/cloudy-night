#include <stdio.h>
#include "Point.h"

int main () {
	
	// Point_MakePOINT dan Point_BacaPOINT untuk input masukan 
	// Equal untuk cek apakah posisi player sama dengan enemy/medicine
	// Point_Geser, Point_NextX, Point_NextY untuk pergerakan player
	
	Point P;
	Point_BacaPOINT(&P);
	
	Point R; 
	Point_BacaPOINT(&R);
	
	printf("Point_equal : ");
	printf("%d\n",Point_equal(P,R));
	
	//Point digeser dengan delta x = -1, dan delta y = 0
	Point_Geser(&P,-1,0);
	printf("Point_Geser :\n");
	Point_TulisPOINT(P);
	printf("\n");
	
	// x Point Px adalah next x dari Point P
	Point Px = Point_NextX(P);
	printf("Point_NextY  :\n");
	Point_TulisPOINT(Px);
	printf("\n");
	
	// y Point Py adalah next y dari Point P
	Point Py = Point_NextY(P);
	printf("Point_NextY :\n");
	Point_TulisPOINT(Py);
	printf("\n");
	
	

	return 0;
}
