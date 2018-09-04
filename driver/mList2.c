/* DRIVER LIST */

#include "List.h"
#include <stdio.h>

bool func_compare(void* mem, void* ptr)
{
	int* i = (int*) mem;
	int* p = (int*) ptr;
	return *i == *p; 
}

int main ()
{
	printf("###### DRIVER ADT LIST ######\n");
	
	List L;
	List_Create (&L,sizeof(int));
	printf("Test Create Empty: ");
	if (List_IsEmpty(&L))
	{
		printf("List is empty.\n");
	}
	printf("\n");
	
	
	int n,a,b;
	do
	{
		printf("--------- MENU ---------\n");
		printf("1. Add as First Element\n");
		printf("2. Add as Last Element\n");
		printf("3. Add after an Element\n");
		printf("4. Add before an Element\n");
		printf("5. Delete First Element\n");
		printf("6. Delete Last Element\n");
		printf("7. Delete Element\n");
		printf("8. Delete an Element after\n");
		printf("9. Delete an Element before\n");
		printf("10. Print List\n");
		printf("11. Exit\n");
		printf("\n");
		printf("Choose from the menu: ");
		scanf("%d", &n);
		switch (n)
		{
			case 1: //seg fault kalo 2x
			{
				printf("Insert element: ");
				scanf("%d", &a);
				ListElmt* elmt = ListElmt_Alloc(&L);
				ListElmt_Val(elmt, int) = a;
				List_InsertFirst(&L,elmt);
				
				printf("\n");
				break;
			}
			case 2: //udah bener
			{
				printf("Insert element: ");
				scanf("%d", &a);
				ListElmt* elmt = ListElmt_Alloc(&L);
				ListElmt_Val(elmt, int) = a;
				List_InsertLast(&L,elmt);
				
				printf("\n");
				break;
			}
			case 3: //udah bener
			{
				printf("Insert element: ");
				scanf("%d", &a);
				printf("After element: ");
				scanf("%d", &b);
				ListElmt* elmt = ListElmt_Alloc(&L);
				
				ListElmt* elmt_prec = List_Search (&L,func_compare, &b);

				ListElmt_Val(elmt, int) = a;
				List_InsertAfter(&L,elmt,elmt_prec);
				
				printf("\n");
				break;
			}
			case 4: //seg fault
			{
				printf("Insert element: ");
				scanf("%d", &a);
				printf("Before element: ");
				scanf("%d", &b);
				ListElmt* elmt = ListElmt_Alloc(&L);
				
				ListElmt* elmt_succ = List_Search (&L,func_compare, &b);

				ListElmt_Val(elmt, int) = a;
				List_InsertBefore(&L,elmt,elmt_succ);
				
				printf("\n");
				break;
			}
			case 5: //seg fault
			{
				ListElmt* elmt_var;
				List_DelFirst (&L,&elmt_var);
				printf("Element deleted: ");
				printf("%d\n",ListElmt_Val(elmt_var, int));
				ListElmt_Clean(&elmt_var);
				
				printf("\n");
				break;
			}
			case 6: //udah bener
			{
				ListElmt* elmt_var;
				List_DelLast (&L,&elmt_var);
				printf("Element deleted: ");
				printf("%d\n",ListElmt_Val(elmt_var, int));
				ListElmt_Clean(&elmt_var);
				
				printf("\n");
				break;
			}
			case 7: //seg fault
			{
				printf("Delete element: ");
				scanf("%d", &a);
				
				ListElmt* elmt = List_Search (&L,func_compare, &a);
				
				List_Del (&L,elmt);
				printf("Element deleted: ");
				printf("%d\n",ListElmt_Val(elmt, int));
				ListElmt_Clean(&elmt);
				
				printf("\n");
				break;
			}
			case 8: //udah bener
			{
				printf("Delete element after: ");
				scanf("%d", &a);
				
				ListElmt* elmt;
				ListElmt* elmt_prec = List_Search (&L,func_compare, &a);
				List_DelAfter (&L,&elmt,elmt_prec);
				printf("Element deleted: ");
				printf("%d\n",ListElmt_Val(elmt, int));
				ListElmt_Clean(&elmt);
				
				printf("\n");
				break;
			}
			case 9: //udah bener
			{
				printf("Delete element before: ");
				scanf("%d", &a);
				
				ListElmt* elmt;
				ListElmt* elmt_succ = List_Search (&L,func_compare, &a);
				List_DelBefore (&L,&elmt,elmt_succ);
				printf("Element deleted: ");
				printf("%d\n",ListElmt_Val(elmt, int));
				ListElmt_Clean(&elmt);
				
				printf("\n");
				break;
			}
			case 10: //udah benar
			{
				printf("Element List: ");
				ListElmt* elmt = List_First(&L);
				while (elmt != NULL)
				{
					printf ("%d ", ListElmt_Val(elmt, int));
					elmt = ListElmt_Next(elmt);
				}
				printf("\n");
				printf("\n");
				break;
			}
			case 11: //Exit
			{
				printf("Good bye!\n");
				break;
			}
			default:
			{
				printf("Choose correctly!\n");
			}
		}
	} while (n != 11);
	return 0;
}