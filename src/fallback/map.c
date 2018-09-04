#include <assert.h>
#include <stdio.h>

#include <game/Profile.h>
#include <game/GameAsset.h>
#include <game/control/Map.h>
#include <fallback/main.h>
#include <util/String.h>
#include <ncurses.h>

#include "map.h"

static void
_Game_ShowMap (Matrix*   map,
               Point     loc)
{
	assert (map != NULL);
	
	for (int r = 1; r <= 24; r++)
	{
		for (int c = 1; c <= 80; c++)
		{
			if ((r == Row(loc)) && (c == Col(loc)))
			{
				attron (A_BOLD | COLOR_PAIR(1));
				printw ("P");
				attroff (A_BOLD | COLOR_PAIR(1));
			}
			else
			{
				char ch = Matrix_Elmt(*map, r, c);
				
				switch (ch)
				{
				case '#':
					attron (A_BOLD | COLOR_PAIR(4));
					printw (" ");
					attroff (A_BOLD | COLOR_PAIR(4));
					break;
				
				case '.':
					printw (" ");
					break;

				case 'M':
					attron (A_BOLD | COLOR_PAIR(2));
					printw ("%c", ch);
					attroff (A_BOLD | COLOR_PAIR(2));
					break;
					
				case 'E':
					attron (A_BOLD | COLOR_PAIR(3));
					printw ("%c", ch);
					attroff (A_BOLD | COLOR_PAIR(3));
					break;
				case 'B':
					attron (A_BOLD | COLOR_PAIR(5) | A_BLINK);
					printw("%c", ch);
					attroff (A_BOLD | COLOR_PAIR(5) | A_BLINK);
					break;
				default:
					printw ("%c", ch);
				}
			}
		}
		
		printw ("\n");
	}
}

void
Game_Map (Profile *prof,int idx)
{
	Map map;
	Map_Create (&map, Game_Asset, prof);
	
	initscr ();
	start_color ();
	keypad (stdscr, TRUE);
	
	init_pair (1, COLOR_WHITE, COLOR_BLUE);
	init_pair (2, COLOR_WHITE, COLOR_GREEN);
	init_pair (3, COLOR_WHITE, COLOR_RED);
	init_pair (4, COLOR_BLACK, COLOR_WHITE);
	init_pair (5, COLOR_RED, COLOR_BLACK);

	bool loop = true;
	
	char* msg = NULL;
	int msg_n = 0;
	
	while (loop)
	{
		clear ();
		Point loc = prof->loc_point;

		_Game_ShowMap (&map.data, loc);
		printw ("\nName: %s (Level %d)\n", String_Peek (&prof->Name), prof->Lvl);
		printw ("HP  : %d\n", prof->HP);
		printw ("Str : %d\n", prof->Str);
		printw ("Def : %d\n", prof->Def);
		printw ("EXP : %d\n", prof->Exp);
		
		if (msg_n > 0)
		{
			msg_n--;
			printw ("\n%s\n", msg);
		}

		
		printw ("\nPress up, down, left, right to navigate.\n");
		printw ("Press F1 to save: ");
		
		refresh ();
		int ch = getch ();
		int move;
		
		switch (ch)
		{
		case KEY_UP:
			move = MAP_MOVE_U;
			break;
			
		case KEY_DOWN:
			move = MAP_MOVE_D;
			break;
			
		case KEY_LEFT:
			move = MAP_MOVE_L;
			break;
			
		case KEY_RIGHT:
			move = MAP_MOVE_R;
			break;
			
		case KEY_F(1):
			Game_Save(idx);
			
			msg = "Game has been saved.\n";
			msg_n = 5;
			break;
		}
		
		switch (Map_Move (&map, move))
		{
		case MAP_STATE_FIGHT:
			loop = false;
			break;
			
		case MAP_STATE_CH_MAP:
			Map_Create (&map, Game_Asset, prof);
			break;
		}
	}
	
	endwin ();
}
