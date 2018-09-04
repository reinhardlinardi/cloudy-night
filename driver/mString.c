#include<stdio.h>
#include "String.h"

char keyword[100];
char keykeyword[100];
char keykeykeyword[100];
String test,test2;

int main()
{
    printf("Input keyword : ");
    scanf("%s",keyword);
    
	printf("Input keyword 2 : ");
    scanf("%s",keykeyword);
	
	printf("Input keyword 3 : ");
    scanf("%s",keykeykeyword);
	
    String_Create(&test);
    String_AppendCStr(&test,keyword);
    
	String_CreateFromCStr(&test2,keykeyword);
	
    printf("\n");
    printf("Length of keyword: %d\n",(int)(test.len));
	printf("First character of keyword : %c\n",test.buf[0]);
	
	if(String_IsEqual(&test,&test2)) printf("Keyword 1 and 2 are equal\n");
	else printf("Keyword 1 and 2 are not equal\n");
	
	if(String_IsEqualCStr(&test,keykeykeyword)) printf("Keyword 1 and 3 are equal\n");
	else printf("Keyword 1 and 3 are not equal\n");
	
    String_Append(&test,&test2);
	printf("Append keyword 2 to keyword 1 : %s\n",String_Eject(&test));
	String_AppendCStr(&test,keykeykeyword);
	printf("Append keyword 3 to keyword 1 : %s\n",String_Eject(&test));
	String_AppendChar(&test,'?');
	printf("Append ? to keyword 1 : %s\n",String_Eject(&test));
	
    return 0;
}