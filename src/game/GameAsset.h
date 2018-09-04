#pragma once

#include <game/util/Matriks.h>
#include <game/util/Graph.h>

typedef struct _MapData MapData;
struct _MapData
{
	Graph AllAreaCombine;
	Matrix Area[13];
};

typedef struct _Stat Stat;
struct _Stat
{
	int Lvl;
	int HP;
	int Str;
	int Def;
};

typedef struct _StatP StatP;
struct _StatP
{
	Stat idP[7];
	int EXP[7];
};

typedef struct _StatE StatE;
struct _StatE
{
	char * Name;
	Stat idE;
	int Total_F;
	int Total_A;
	int Total_B;
};

typedef struct _GameAsset GameAsset;
struct _GameAsset
{
	MapData WholeMap;
	//BinTree SkillPlayer;
	StatP Player;
	StatE Enemy[7];
	StatE FinalBoss;
	char * Win;
	char * Lose;
	char * Credit;
};

void GameAsset_Create(GameAsset* self);
/* I.S : Sembarang
 * F.S. : Semua struktur data di atas yang akan digunakan untuk menyimpan
 * data dari file eksternal telah disiapkan */
 
//void ListAccessible(GameAsset self,List* Accessible);
/* I.S : Terdapat matriks untuk peta
 * F.S : Dikembalikan sebuah list of point accessible yang berisi
 * koordinat pada matriks yang menunjukkan koordinat yang dapat diakses
 * bukan '#' */
