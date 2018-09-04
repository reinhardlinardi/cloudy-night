#include "GameAsset.h"

#include <assert.h>
#include <game/util/Point.h>

void
GameAsset_Create (GameAsset*  self)
{
	// Kamus Lokal
	int i;
	
	// Algoritma
	for (i=1;i<=12;i++) //buat 12 map
	{
		Matrix_CreateEmpty(24,80,&(self->WholeMap.Area[i]));
	}
	
	for (i=1;i<=6;i++) //6 level player (jangan lupa ganti nanti)
	{
		(*self).Player.idP[i].Lvl = 0;
		(*self).Player.idP[i].HP = 0;
		(*self).Player.idP[i].Str = 0;
		(*self).Player.idP[i].Def = 0;
	}
	
	for (i=1;i<=6;i++) //6 jenis enemy (jangan lupa ganti nanti)
	{
		(*self).Enemy[i].idE.Lvl = 0;
		(*self).Enemy[i].idE.HP = 0;
		(*self).Enemy[i].idE.Str = 0;
		(*self).Enemy[i].idE.Def = 0;
		
		(*self).Enemy[i].Total_F = 0;
		(*self).Enemy[i].Total_A = 0;
		(*self).Enemy[i].Total_B = 0;
	}
	
	(*self).FinalBoss.idE.Lvl = 0;
	(*self).FinalBoss.idE.HP = 0;
	(*self).FinalBoss.idE.Str = 0;
	(*self).FinalBoss.idE.Def = 0;
	
	Graph_Create(&self->WholeMap.AllAreaCombine);
}
