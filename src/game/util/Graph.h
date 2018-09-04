#ifndef GRAPH_H
#define GRAPH_H


#define IdxMin 1
#define IdxMax 20

struct ElAdj{
	char OrgDoor;
	int Destination;
	char DestDoor;
};

struct Node{
	struct ElAdj AdjList[100];
	int Neff;
};

typedef struct {
	struct Node TabNode[IdxMax+1];
}Graph;

#define OrgDoor(P) (P).OrgDoor
#define Destination(P) (P).Destination
#define DestDoor(P) (P).DestDoor
#define Neff(P,i) (P).TabNode[(i)].Neff
#define Elmt(G,i,j) ((G).TabNode[(i)]).AdjList[(j)]

void Graph_Create(Graph *G);
// I.S Graph Sembarang
// F.S Terbentuk Graph Kosong s

void AddAdj(Graph *G, int Org, char OrgDoor, int Destination, char DestDoor);
// I.S Graph Sembarang
// F.S Data dimasukkan pada *G.TabNode([i]).AdjList

void PrintGraph(Graph G);
// I.S Graph Sembarang
// F.S Graph dicetak

#endif