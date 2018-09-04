// Irene Edria Devina //
// 13515038 //
// 2 September 2016 //
// point.c //
#include <stdio.h>
#include <math.h>
#include "Point.h"

Point Point_MakePOINT (int X, int Y) {
	
	Point P;
		Row(P)= X;
		Col(P) = Y;
	return P;
}

void Point_BacaPOINT (Point * P)
{
	
	int absis, ordinat;
	
	scanf("%d %d", &absis, &ordinat);
	
	*P = Point_MakePOINT(absis,ordinat);
	

}

void Point_TulisPOINT (Point P) {
	
	printf ("(%d,%d)", Row(P), Col(P));
}

bool Point_equal (Point P1, Point P2)
{
	return ((Row(P1) == Row(P2)) && (Col(P1) == Col(P2)));
}

bool Point_notequal (Point P1, Point P2) {
	
	return ((Row(P1) != Row(P2)) || (Col(P1) != Col(P2)));
}

bool Point_IsOrigin (Point P){
	
	return ((Row(P) == 0) && (Col(P) == 0));
}

bool Point_IsOnSbX (Point P) {
	
	return (Col(P) == 0);
}

bool Point_IsOnSbY (Point P) {
	
	return (Row(P) == 0);
}

int Point_Kuadran (Point P) // Prekondisi : P bukan titik origin //
{
	int result;
	if ((Row(P) > 0) && (Col(P) > 0))
		result = 1;
	else if ((Row(P) < 0) && (Col(P) > 0))
		result = 2;
	else if ((Row(P) < 0) && (Col(P) < 0))
		result = 3;
	else
		result = 4;
	
	return result;
}

Point Point_NextX (Point P) {
	
	Point result;
		Row(result) = Row(P) + 1;
		Col(result) = Col(P);
	return result;
	
}

Point Point_NextY (Point P) {
	
	Point result;
		Col(result) = Col(P) + 1;
		Row(result) = Row(P);
	return result;
}

Point Point_PlusDelta (Point P, int deltaX, int deltaY) {

	Point result;
		Row(result) = Row(P) + deltaX;
		Col(result) = Col(P) + deltaY;
	return result;
}

Point Point_MirrorOf (Point P, bool SbX)
{
	Point result;
		if (SbX) {
			Row(result) = Row(P);
			Col(result) = -Col(P);
		}
		else {
			Col(result) = Col(P);
			Row(result) = -Row(P);
		}
	return result;
}

int Point_Panjang (Point P1, Point P2) {
	
	
	return sqrt(pow(Row(P2)-Row(P1),2) + pow(Col(P2) - Col(P1),2));
}

void Point_Geser (Point *P, int deltaX, int deltaY) {
	
	*P = Point_PlusDelta (*P, deltaX, deltaY);
}

void Point_GeserKeSbX (Point *P)
{
	Col(*P)=0;
}

void Point_GeserKeSbY (Point *P)
{
	Row(*P)=0;
}

void Point_Mirror (Point *P, bool SbX)
{
	*P = Point_MirrorOf(*P, SbX);
}
