/* File : player.h */
/* Tanggal : 5 November 2016 */
/* Definisi ADT Player */

#pragma once

#include <stdbool.h>
#include <util/String.h>
#include <game/util/Time.h>
#include <game/util/Point.h>
#include <game/GameAsset.h>
#include <util/List.h>

/* *** Definisi TYPE PLAYER <NAMA,LEVEL,HEALTH,STRENGTH,DEFENSE,EXPERIENCE> *** */
typedef struct _Profile
{
	String Name;
	int Lvl;
	int HP;
	int Str;
	int Def;
	int Exp;               /* Experience Point */
	
	int map_ids[7];        /* Matrix 2x3 of randomized map_id */
	
	int loc_map_id;
    Point loc_point;       /* Posisi Player */
    
    bool skill_ids[16];        /* ID Skill (boolean) */
	Point loc_enemy[7][11];    /* Enemy Location */
	Point loc_medicine[7][11];  /* Medicine Location */
	
	int loc_map_id_boss; /* Boss map id */
	Point loc_boss; /* Boss location */
	
	Time save_time;  /* Time waktu klik save */
	
	// Communications
	
	bool is_boss;
	Point* cur_loc_enemy;  // Index of active loc_enemy */
	
} Profile;


/* *** KONSTRUKTOR *** */

/* PLAYER baru, dengan NAMA = N, LEVEL = 1, HEALTH = , */
/* STRENGTH = , DEFENSE = , EXPERIENCE = , dan SKILLPLAYER = 0.  */

void
Profile_Create (Profile*    self,
                GameAsset*  asset);

