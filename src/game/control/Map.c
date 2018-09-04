#include <assert.h>
#include <game/GameAsset.h>
#include <game/Profile.h>
#include <time.h>
#include <stdlib.h>
#include <game/util/Point.h>
#include <util/List.h>
#include <stdio.h>

#include "Map.h"

void Map_Create (Map* self, GameAsset* asset, Profile* prof)
{
	self->prof = prof;
	self->asset = asset;
	
	int cur_map = prof->loc_map_id;
	int boss_map_id = prof->loc_map_id_boss;
	
	self->data = asset->WholeMap.Area[prof->map_ids[cur_map]];
	
	// Sprinkle the medicine
	
	for (int i = 1; i <= 10; i++)
	{
		Point P = prof->loc_medicine[cur_map][i];
		Matrix_Elmt(self->data, Row(P), Col(P)) = 'M';
	}
	
	// Sprinkle the enemies
	
	if (prof->Lvl == 6)
	{
		if (cur_map == boss_map_id)
		{
			Point P = prof->loc_boss;
			Matrix_Elmt(self->data, Row(P), Col(P)) = 'B';
		}
	}
	else
	{
		for (int i = 1; i <= 10; i++)
		{
			Point P = prof->loc_enemy[cur_map][i];
			Matrix_Elmt(self->data, Row(P), Col(P)) = 'E';
		}
	}
}

int Map_Move (Map* self, int move)
{
	Profile* prof = self->prof;
	Point* loc = &prof->loc_point;
	GameAsset* asset=self->asset;
	int mapid=prof->loc_map_id;
	char OD;
	MapData WholeMap=asset->WholeMap;
	Graph G=WholeMap.AllAreaCombine;
	int Dest;
	char DestDoor;

	int row = Row(*loc);
	int col = Col(*loc);
	if (move == MAP_MOVE_U)
		row--;
	else if (move == MAP_MOVE_D)
		row++;
	else if (move == MAP_MOVE_R)
		col++;
	else if (move ==MAP_MOVE_L)
		col--;
	
	char ch = Matrix_Elmt(self->data, row, col);
	
	if ((col < 1) || (col > 80) || (row < 1) || (row > 24))
	{
		int i=0;
		int neff=Neff(G,mapid);
		bool f=false;
		if(col<1)
			OD='L';
		else if(col > 80)
			OD='R';
		if(row < 1)
			OD='U';
		else if(row > 24)
			OD='D';
		while(!f && i<neff)
		{
			if(OD==OrgDoor(Elmt(G,mapid,i)))
			{
				f=true;
				Dest=Destination(Elmt(G,mapid,i));
				DestDoor=DestDoor(Elmt(G,mapid,i));

			}
			i++;
		}
			Matrix Map_New= WholeMap.Area[prof->map_ids[Dest]];
		if(DestDoor=='L' || DestDoor=='R')
		{
			row=1;
			if(DestDoor=='L')
				col=1;
			else
				col=80;
			while(Matrix_Elmt(Map_New,row,col)!='.' && row < 24)
					row++;
		}
		else
		{
			col=1;
			if(DestDoor=='U')
				row=1;
			else
				row=24;
			while(Matrix_Elmt(Map_New,row,col)!='.' && col<80)
				col++;
		}
		self->data = Map_New;
		prof->loc_map_id=Dest;
		Row(*loc) = row;
		Col(*loc) = col; // ganti x y nya sama pintu masuk
		
		// Map bakal di re-create tiap ganti
		// self->data=Map_New;
		
		return MAP_STATE_CH_MAP;
	}
	else if (ch == '#')
	{
		// do nothing
	}
	else if (ch == 'M')
	{
		int i; 
		Row(*loc) = row;
		Col(*loc) = col;
		for(i=0;i<=10;i++)
		{
			if(Row(prof->loc_medicine[mapid][i])==Row(prof->loc_point) &&  Col(prof->loc_medicine[mapid][i])==Col(prof->loc_point)){
				Row(prof->loc_medicine[mapid][i])=0;
				Col(prof->loc_medicine[mapid][i])=0;
			}
		}
		prof->HP = self->asset->Player.idP[prof->Lvl].HP+ (prof->skill_ids[1]*10) + (prof->skill_ids[5]*20) + (prof->skill_ids[9]*30) + (prof->skill_ids[13]*40);
		
		Matrix_Elmt(self->data, row, col) = '.';
	}
	else if (ch == 'E')
	{
		int i; 
		
		for(i=0;i<=10;i++)
		{
			if(Row(prof->loc_enemy[mapid][i])==row &&  Col(prof->loc_enemy[mapid][i])==col)
				prof->cur_loc_enemy = &prof->loc_enemy[mapid][i];
		}

		prof->is_boss = false;
		return MAP_STATE_FIGHT;
	}
	else if (ch == 'B')
	{
		prof->is_boss = true;
		prof->cur_loc_enemy = &prof->loc_boss;
		
		return MAP_STATE_FIGHT;
	}
	else
	{
		Row(*loc) = row;
		Col(*loc) = col;
		return MAP_STATE_CH_LOC;
	}
	
	return MAP_STATE_NOTHING;
}

