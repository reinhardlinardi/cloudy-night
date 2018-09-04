#pragma once

typedef struct _Map Map;

struct _Map
{
	Profile*  prof;
	GameAsset*  asset;
	Matrix  data;
};

#define MAP_MOVE_U  (1)
#define MAP_MOVE_D  (2)
#define MAP_MOVE_L  (3)
#define MAP_MOVE_R  (4)

#define MAP_STATE_CH_MAP (5)// Ganti Map
#define MAP_STATE_CH_LOC (6)// Ganti Posisi
#define MAP_STATE_FIGHT (7)// Masuk mode fight
#define MAP_STATE_NOTHING (8) // Tidak melakukan apa-apa
// Konstruktor

void Map_Create (Map* self, GameAsset* asset, Profile* prof);
/* I.S : Terdapat matriks posisi Player
 * F.S : Mengirim data ke grafik posisi Player, mengacak posisi enemy,
 * posisi medicine, dan posisi final boss jika Player sudah memenuhi
 * prasyarat */
 
int Map_Move (Map* self, int move);
/* I.S : Terdapat area di layar dan masukan dari user
 * F.S : Player berpindah tempat sesuai dengan input user, Player
 * dapat berpindah ke area lain, masuk ke scene fight, atau pun
 * bertambah HP hingga penuh */
