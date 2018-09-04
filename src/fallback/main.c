#include <assert.h>
#include <stdio.h>

#include <game/Asset.h>
#include <game/io/Io.h>
#include <game/control/Level.h>
#include <fallback/anim.h>
#include <fallback/map.h>
#include <fallback/level.h>
#include <fallback/battle.h>
#include <util/String.h>
#include <ncurses.h>

#include "main.h"

Profile all_profile[21]; //array of profile
int profile_counter; //banyaknya profile yang ada
int profile_index; //current index in all_profile
int scr_max;
Profile* Game_Profile;
GameAsset* Game_Asset = NULL;

bool new_game_selected = false;
bool profile_loaded = false;

bool is_profile_exist(String test_name,int *idx) // check if profile with profile name test_name exists
{
	int i; //iterator
	
	for(i=1;i<=profile_counter;i++)
	{
		if(String_IsEqual(&test_name,&all_profile[i].Name)) //return index if found
		{
			*idx = i;
			return true;
		}
	}
	
	return false;
}

static void
_Game_New (void)
{
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	
	WINDOW *win=newwin(4,60,8,(scr_max-60)/2);
	
	refresh();
	box(win,0,0);
	wbkgd(win,COLOR_PAIR(1));
	String s;
	char name[21];
	wrefresh(win);	

	new_game_selected = true;
	
	mvwprintw (win,1,1,"Name? (max. 20 char, without spaces)");
	mvwprintw(win,2,1,">");
	mvwscanw (win,2,2,"%20s", name);
	String_CreateFromCStr(&s,name);	

	wclear(win);
	box(win,0,0);
	wrefresh(win);	
	
	if(!is_profile_exist(s,&profile_index)) //if profile does not exists create new profile
	{
		if(profile_index!=0) printf("Unload previous profile: %s.\n",String_Peek(&(all_profile[profile_index].Name)));
		
		profile_counter++;
		Profile_Create(&all_profile[profile_counter],Game_Asset);
		String_CreateFromCStr(&(all_profile[profile_counter].Name), name);
		
		mvwprintw (win,1,1,"Profile is created: %s.", name);
		
		profile_index = profile_counter;
		profile_loaded = true;
		
		mvwprintw(win,2,1,"Welcome, %s!",String_Peek(&(all_profile[profile_index].Name)));
	}
	else {
		mvwprintw(win,1,1,"Profile name already exists.");
	}
	wrefresh(win);
	getch();
	wclear(win);
	delwin(win);
	refresh();
}

static void
_Game_Start (int current_index)
{
	if(profile_loaded)
	{
		// Enter GAME
		bool loop = true;
		
		while (loop)
		{
			if(all_profile[current_index].HP == 0)
			{
				loop = false;
				clear();
				printw("\n%s\n",(*Game_Asset).Lose);
				printw("Press Enter to Continue:");
				getch();
				//_Print_Logo();
				
				Level_Credits ();
			}
			else if(all_profile[current_index].is_boss && all_profile[current_index].HP > 0)
			{
				loop = false;
				clear();
				printw("\n%s\n",(*Game_Asset).Win);
				printw("Press Enter to Continue:");
				getch();
				Game_Save(current_index);
				
				//_Print_Logo();
				
				Level_Credits ();
			}
			else
			{
				if (Level_IsDirty (&all_profile[current_index], Game_Asset))
					Game_Level (&all_profile[current_index]);
				
				Game_Map (&all_profile[current_index],profile_index);
				Game_Battle (&all_profile[current_index]);
			}
		}
	}
	else
	{

		WINDOW *win=newwin(3,60,8,(scr_max-60)/2);
		init_pair(1,COLOR_WHITE,COLOR_RED);
		wbkgd(win,COLOR_PAIR(1));
		box(win,0,0);
		mvwprintw (win,1,1,"No profile is loaded.");
		refresh();
		wrefresh(win);
		getch();
		wclear(win);
		delwin(win);
		refresh();
	}
}

static void
_Game_Load (void)
{
	int in;
	int i;
	if(profile_counter==0)
	{
		WINDOW *win=newwin(3,60,8,(scr_max-60)/2);
		init_pair(1,COLOR_WHITE,COLOR_RED);
		wbkgd(win,COLOR_PAIR(1));
		mvwprintw(win,1,1,"\nNo profile available.\n");
		refresh();
		wrefresh(win);
		getch();
		wclear(win);
		delwin(win);
	}
	else
	{
		WINDOW *win=newwin(profile_counter+4,60,8,(scr_max-60)/2);
		box(win,0,0);
		int hl=1;
		do{
		mvwprintw(win,1,1,"Select your profile :");
		
		for(i=1;i<=profile_counter;i++)
		{
			if(hl==i)
				wattron(win,A_REVERSE);
			mvwprintw(win,i+1,1,"%d. %s",i,String_Peek(&(all_profile[i].Name)));
			if(hl==i)
				wattroff(win,A_REVERSE);
		}
		if(hl==0)
			wattron(win,A_REVERSE);
			mvwprintw(win,profile_counter+2,1,"0. Exit");
		if(hl==0)
			wattroff(win,A_REVERSE);

		refresh();
		wrefresh(win);

		in = getch();
		switch(in){
			case KEY_UP :
				hl--;
				break;
			case KEY_DOWN :
				hl++;
				break; 
		}
		if(hl>profile_counter)
			hl=0; 
		else if(hl<0)
			hl=profile_counter;

		}while(in!='\n');
		wclear(win); 
		Anim_Frame();
		wresize(win,3,60);
		box(win,0,0);
		in=hl;
		if(in>=1 && in<=profile_counter)
		{
			if(profile_index == in) mvwprintw(win,1,1,"Profile %s has been loaded.",String_Peek(&(all_profile[profile_index].Name)));
			else mvwprintw(win,1,1,"Profile loaded : %s.",String_Peek(&(all_profile[in].Name)));
			
			profile_loaded = true;
			profile_index = in;
			refresh();
			//_Print_Logo();
			wrefresh(win);
			getch();

		}
		wclear(win); 
		delwin(win);
	}
}

void
_Game_Menu (void)
{
	int ch;
	int i;
	initscr();
	start_color();
	init_pair (8, COLOR_WHITE, COLOR_BLACK);
	init_pair (9, COLOR_GREEN, COLOR_BLACK);
	keypad(stdscr,TRUE);
	cbreak();
	scr_max=getmaxx(stdscr);
	
	// ANIM INIT
	Anim_Init ();
	
	bool loop = true;
	int hl=1; 
	
	while (loop)
	{
		do{
			Anim_Frame ();
			//_Print_Logo();
			
			refresh();
			WINDOW *inp=newwin(7,21,25,(scr_max-20)/2);
			box(inp,0,0);
			mvwprintw (inp,1,8,"Menu:");
			for(i=1;i<=4;i++)
			{
				if(i==hl)
					wattron(inp,A_REVERSE);
				switch(i){
				case 1 :
					mvwprintw (inp,2,6,"%s", Asset_Menu_New);
					break;
				case 2 :
					mvwprintw (inp,3,5,"%s", Asset_Menu_Start);
					break;
				case 3 :
					mvwprintw (inp,4,6,"%s", Asset_Menu_Load);
					break;
				case 4 :
					mvwprintw (inp,5,6,"%s", Asset_Menu_Exit);	
				}
				if(i==hl)
					wattroff(inp,A_REVERSE);
			}
			wrefresh(inp);	
			curs_set(0);
			
			bool loop = true;
			timeout (50);
			
			while (loop)
			{
				loop = false;
				ch = getch();
				switch(ch)
				{
					case KEY_UP:
						hl--; 
						break;
					case KEY_DOWN: 
						hl++;
						break;
					case ERR:
						loop = true;
						Anim_Frame ();
						overwrite (inp, stdscr);
						refresh ();
						break;
				}
			}
			
			timeout (-1);

			if(hl>4)
				hl-=4;
			else if(hl<1)
				hl+=4;
		}while(ch!='\n');
	switch(hl){
		case 1 : 
			_Game_New();
			break;
		case 2 :
			_Game_Start(profile_index);
			break; 
		case 3 :
			_Game_Load();
			break;	
		default :
			loop=false;
			break;

	} 
	}
	endwin();
}

void
Game_Save (int current_index)
{
	//Save game
	save_profile(Game_Profile,profile_counter,current_index);
}

int
Fallback_Main (void)
{
	Game_Asset = (GameAsset*) malloc (sizeof (GameAsset));
	GameAsset_Create(Game_Asset);
	
	Game_Profile = all_profile; //point to array of profile
	load_all_profile(Game_Profile,&profile_counter); //load all profile
	profile_index = 0; //no current profile
	
	load_gameasset(Game_Asset);
	load_enemymoves(Game_Asset);
	
	_Game_Menu ();
	
	return 0;
}