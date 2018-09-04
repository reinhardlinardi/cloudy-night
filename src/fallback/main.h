#pragma once

#include <game/Profile.h>
#include <game/GameAsset.h>

extern GameAsset* Game_Asset;

void
Game_Save (int current_index);

int
Fallback_Main (void);
