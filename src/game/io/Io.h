#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>
#include <game/io/Mesinkarakter.h>
#include <game/io/Mesinkata.h>
#include <util/String.h>
#include <game/util/Time.h>
#include <game/util/Point.h>
#include <game/GameAsset.h>
#include <game/Profile.h>
#include <util/List.h>
#include <game/util/Graph.h>

void no_end_character();
/* I.S. ada signal segfault */
/* F.S. signal segfault dihandle */

void save_profile(Profile* profile,int max_profile,int update_index);
/* I.S. profile terdefinisi */
/* F.S. Semua data profile tersimpan dalam file eksternal */
    
void load_profile(Profile *profile,String name);
/* I.S. profile terdefinisi */
/* F.S. Semua data profile dengan nama name tersimpan dalam struktur data Profile */

void load_gameasset(GameAsset *gameasset);
/* I.S. gameasset terdefinisi */
/* F.S. Semua data profile tersimpan dalam struktur data GameAsset */

void load_enemymoves(GameAsset *gameasset);
/* I.S. gameasset terdefinisi */
/* F.S. Enemy moves tersimpan dalam struktur data GameAsset */

bool check_error_profile();
/* I.S. File eksternal profile terdefinisi, isi sembarang */
/* F.S. File eksternal profile tidak mengandung error dan siap dibaca */

bool check_error_gameasset();
/* I.S. File eksternal gameasset terdefinisi, isi sembarang */
/* F.S. File eksternal gameasset tidak mengandung error dan siap dibaca */

void load_all_profile(Profile *profile,int *number_of_profile);
/* I.S. File eksternal profile terdefinisi */
/* F.S. Semua profile terload ke profile */