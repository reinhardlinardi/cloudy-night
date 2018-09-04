#include <stdio.h>
#include <stdlib.h>
#include <game/RandomMap.h>

#include "Profile.h"

void
Profile_Create (Profile*    self,
                GameAsset*  asset)
{
	self->Lvl = 0;
	self->HP  = -1;
	self->Str = 0;
	self->Def = 0;
	self->Exp = 0;
	
	RandomMap_FillInSlot (self);
	RandomMap_SprinkleWithLove (self, asset);
	
	for (int i = 1; i <= 15; i++)
		self->skill_ids[i] = false;
	
	
	// no last save time
	
	Hour(self->save_time)   = -1;
	Minute(self->save_time) = -1;
	Second(self->save_time) = -1;
	
	(*self).is_boss = false;
}