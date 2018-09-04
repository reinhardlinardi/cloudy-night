#include "game/util/Graph.h"
#include "stdio.h"

void PrintGraph(Graph G);

int main(){
	Graph G;
	Graph_Create(&G);
	int x;
	
	do
	{
		puts("1. Add Adjacent (Graph, GraphOrigin, OriginDoor, GraphDestination, DestinationDoor)");
		puts("2. PrintGraph");
		puts("3. Exit");
		scanf("%d",&x);
		if(x==1)
		{
			char a,c;
			int d,b;
			printf("Graph Origin: ");
			scanf("%d",&d);
			printf("Origin Door: ");
			scanf(" %c",&a);
			printf("Destination: ");
			scanf("%d",&b);
			printf("OriginDoor: ");
			scanf(" %c",&c);
			AddAdj(&G,d,a,b,c);
		}
		else  if(x==2)
		{
			PrintGraph(G);
		}
		
	}while(x!=3);
	return 0;
}

void PrintGraph(Graph G)
{
	printf("\n");
	int i,j;
	for(i=IdxMin;i<=IdxMax;i++)
	{
		if(Neff(G,i)!=0){
		printf("%d: ",i);
		for(j=0;j<Neff(G,i);j++)
			printf("%d.%c-%d.%c",i,OrgDoor(Elmt(G,i,j)),Destination(Elmt(G,i,j)),DestDoor(Elmt(G,i,j)));
		printf("\n");
		}
		
	}
	printf("\n\n");
}
