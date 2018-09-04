#include <stdio.h>
#include "Graph.h"

void Graph_Create(Graph *G)
// I.S Graph Sembarang
// F.S Terbentuk Graph Kosong
{
	int i;
	for(i=IdxMin;i<=IdxMax;i++)
	{
		Neff(*G,i)=0;
	}
}

void AddAdj(Graph *G, int Org, char OrgDoor, int Destination, char DestDoor)
// I.S Graph Sembarang
// F.S Data dimasukkan pada *G.TabNode([i]).AdjList
{
	DestDoor(Elmt(*G,Org,Neff(*G,Org)))=DestDoor;
	OrgDoor(Elmt(*G,Org,Neff(*G,Org)))=OrgDoor;
	Destination(Elmt(*G,Org,Neff(*G,Org)))=Destination;
	Neff(*G,Org)++;
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