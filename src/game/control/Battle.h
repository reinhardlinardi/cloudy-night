/* Fight.c */

#pragma once

#include <game/GameAsset.h>
#include <game/Profile.h>
#include <game/Shuffle.h>
#include <stdio.h>
#include <game/util/Queue.h>
#include <game/util/Stack.h>
#include <stdbool.h>
#include <game/control/Level.h>

typedef struct _Battle Battle;

struct _Battle
{
	Profile*  profile;
    Queue player_moves;
    StatE profileen;
    Stack enemy_moves;
	Queue enemy_move;
};

void Battle_Create (Battle* self, Profile* prof, StatE enemy);

void Battle_Prepare (Battle * self);

void Battle_Add (Battle * self, char ch);
void Battle_Del (Battle * self);

bool
Battle_IsFull (Battle*  self);

bool
Battle_IsEmpty(Battle* self);

void
Battle_GetPlayerMove (Battle*  self,
                      char*    ch);

void
Battle_GetEnemyMove (Battle*  self,
                     char*    ch);

bool Battle_Act(Battle * self);
void Battle_Msg(Battle * self,bool BattleAct);
