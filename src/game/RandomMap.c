#include <assert.h>
#include <game/util/Graph.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <game/Profile.h>

#include "RandomMap.h"


static void
_RandomMap_GenAccessible (const Matrix*  Mat,
                          List*          Accessible)
{
	assert (Accessible != NULL);
	
	// Kamus Lokal
	int r, c;
	
	// Algoritma
	List_Create (Accessible, sizeof (Point));
	
	for (r = 2; r <= 23; r++)
	{
		for (c = 2; c <= 79; c++)
		{
			if (Matrix_Elmt(*Mat, r, c) == '.')
			{
				Point P = Point_MakePOINT(r, c);
				
				ListElmt* elmt = ListElmt_Alloc (Accessible);
				ListElmt_Val(elmt, Point) = P;
				List_InsertLast (Accessible, elmt);
			}
		}
	}
}


// Engine

void
RandomMap_FillInSlot (Profile*  prof)
{
	// Kamus Lokal
	int tl, tc, tr, bl, bc, br;
	
	// Algoritma
	assert (prof != NULL);
	
	// 4 & 11
	srand(time(NULL));
	tl = (((rand() % 2) + 1) * 7 - 3);
	
	// 1 & 7
	srand(time(NULL));
	tc = (((rand() % 2) + 1) * 6 - 5);
	
	
	// 2 & 8
	srand(time(NULL));
	tr = (((rand() % 2) + 1) * 6 - 4);
	
	
	// 5 & 9
	srand(time(NULL));
	bl = (((rand() % 2) + 1) * 4 + 1);
	
	
	// 3 & 12
	srand(time(NULL));
	bc = (((rand() % 2) + 1) * 9 - 6);
	
	
	// 6 & 10
	srand(time(NULL));
	br = (((rand() % 2) + 1) * 4 + 2);
	
	// Profile
	
	prof->map_ids[1] = tl;
	prof->map_ids[2] = tc;
	prof->map_ids[3] = tr;
	prof->map_ids[4] = bl;
	prof->map_ids[5] = bc;
	prof->map_ids[6] = br;
}

void
RandomMap_SprinkleWithLove (Profile*    prof,
                            GameAsset*  asset)
{
	assert (prof != NULL);
	
	int i, j, k, pl, bs;
	pl = (rand() % 6) + 1;
	bs = (rand() % 6) + 1;
	
	for (i = 1; i <= 6; i++)
	{
		// For every map...
		
		Matrix* data = &asset->WholeMap.Area[prof->map_ids[i]];
		
		List Accessible;
		_RandomMap_GenAccessible (data, &Accessible);
		
		// Medicine
		
		for (j = 1; j <= 10; j++)
		{	
			srand(time(NULL));
			int x = rand() % List_Count(&Accessible);
			
			ListElmt* q = List_First(&Accessible);
			for (k = 0; k < x; k++)
			{
				q = ListElmt_Next(q);
			}
			
			List_Del(&Accessible, q);
			
			prof->loc_medicine[i][j] = ListElmt_Val(q,Point);
			ListElmt_Clean (&q);
		}
		
		// Enemy
		
		for (int j = 1; j <= 10; j++)
		{	
			srand(time(NULL));
			int cnt = List_Count(&Accessible);
			int x = rand() % cnt;
			
			ListElmt* q = List_First(&Accessible);
			for (k = 0; k < x; k++)
			{
				q = ListElmt_Next(q);
			}
			
			List_Del(&Accessible, q);
			
			prof->loc_enemy[i][j] = ListElmt_Val(q,Point);
			ListElmt_Clean (&q);
		}
		
		// Final Boss
		
		if (bs == i)
		{
			srand(time(NULL));
			int cnt = List_Count(&Accessible);
			int x = rand() % cnt;
			
			ListElmt* q = List_First(&Accessible);
			for (k = 0; k < x; k++)
			{
				q = ListElmt_Next(q);
			}
			
			// Write
			
			List_Del(&Accessible, q);
			
			prof->loc_map_id_boss = i;
			prof->loc_boss = ListElmt_Val(q,Point);
			ListElmt_Clean (&q);
		}
		
		// Player
		
		if (pl == i)
		{
			srand(time(NULL));
			int cnt = List_Count(&Accessible);
			int x = rand() % cnt;
			
			ListElmt* q = List_First(&Accessible);
			for (k = 0; k < x; k++)
			{
				q = ListElmt_Next(q);
			}
			
			// Write
			
			prof->loc_map_id = i;
			prof->loc_point = ListElmt_Val(q,Point);
		}
	}
}
