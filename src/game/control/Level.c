#include <stdio.h>
#include <game/Profile.h>
#include <game/GameAsset.h>
#include <ncurses.h>
#include "Level.h"


bool Level_IsDirty (Profile*    self,
                    GameAsset*  asset)
{
    if(self->Lvl == 0) {
        return true;
    }
    else
    {
        int exp = asset->Player.EXP[self->Lvl];
        
        if (self->Exp >= exp)
            return true;
        else
            return false;
    }

}

void Level_Change (Profile*  self, GameAsset* asset) {
    
    if(Level_IsDirty(self,asset))
	{
		
		
		self->Lvl++;
        self->Exp = 0;
		
		self->HP  = asset->Player.idP[self->Lvl].HP + (self->skill_ids[1]*10) + (self->skill_ids[5]*20) + (self->skill_ids[9]*30) + (self->skill_ids[13]*40);
		self->Str = asset->Player.idP[self->Lvl].Str;
		self->Def = asset->Player.idP[self->Lvl].Def;
    }
}
