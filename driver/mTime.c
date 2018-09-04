// mTime.c //

#include <stdio.h>
#include "Time.h"


int main () {

	long max = 0;
	long min = 999999999;
	Time J1, J2;
	int h1, m1, h2, m2, s1,s2;

	scanf("%d %d %d",&h1,&m1,&s1);
	scanf("%d %d %d",&h2,&m2,&s2);
	
	Time_Create(h1,m1,s1,&J1);
	Time_Create(h2,m2,s2,&J2);
	

	if (Time_Equal(J1,J2)){
		if (Time_HourToSecond(J1) > max) 
			max = Time_HourToSecond(J1);
		if (Time_HourToSecond(J2) < min) 
			min = Time_HourToSecond(J2);
	}
	else { 
		if (Time_LessThan(J1,J2)) {
			
			if (Time_HourToSecond(J1) < min) 
				min = Time_HourToSecond(J1);
			if (Time_HourToSecond(J2) > max) 
				max = Time_HourToSecond(J2);
			printf("Durasi (seconds) : %ld\n",Time_Duration(J1,J2));	
		}
		else {
			
			if (Time_HourToSecond(J1) > max) 
				max = Time_HourToSecond(J1);
			if (Time_HourToSecond(J2) < min) 
				min = Time_HourToSecond(J2);
			printf("Durasi (seconds) : %ld\n",Time_Duration(J2,J1));	
		}
	}
		
	Time Ja = (Time_SecondToHour(min));
	printf("%d : ",Hour(Ja));
	printf("%d : ",Minute(Ja));
	printf("%d\n",Second(Ja));
	
	Time Jb = (Time_SecondToHour(max));
	printf("%d : ",Hour(Jb));
	printf("%d : ",Minute(Jb));
	printf("%d\n",Second(Jb));
	
	
	return 0;
}
