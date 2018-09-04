#include <game/Profile.h>
#include <game/GameAsset.h>
#include <game/control/Battle.h>
#include <fallback/main.h>
#include <ncurses.h>
StatE
_Game_GetEnemy (Profile *prof)
{
	if (prof->is_boss)
	{
		return Game_Asset->FinalBoss;
	}
	else
	{
		int r = rand() % 2 + (*prof).Lvl;
		return Game_Asset->Enemy[r];
	}
}

void
Game_Battle (Profile *prof)
{
	int hpemax,hmex;
	int hpmax=Game_Asset->Player.idP[prof->Lvl].HP+ (prof->skill_ids[1]*10) + (prof->skill_ids[5]*20) + (prof->skill_ids[9]*30) + (prof->skill_ids[13]*40);
	clear();
	initscr();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_GREEN, COLOR_GREEN);
	init_pair(3, COLOR_RED, COLOR_RED);

	char kmap[10]={'.','A','B','F'};
	int cn=4;
	int hl=1;
	if(prof->skill_ids[4])
		{
			kmap[cn]='W';
			cn++;
		}
	if(prof->skill_ids[5])
		{
			kmap[cn]='X';
			cn++;
		}
	if(prof->skill_ids[6])
		{
			kmap[cn]='Y';
			cn++;
		}
	if(prof->skill_ids[7])
		{
			kmap[cn]='Z';
			cn++;
		}
	kmap[cn]='D';	
	
	keypad(stdscr,TRUE);
	Battle batt;
	Battle_Create (&batt, prof, _Game_GetEnemy (prof));
	
	hpemax=batt.profileen.idE.HP;

	bool noin=false;
	bool empt=false;
	bool loop = true;
	bool msg = false;
	char m[4], n[4];
	
	Battle_Prepare (&batt);
	Battle_GetEnemyMove (&batt, m);
	
	while (loop)
	{	
		refresh();
		WINDOW *title = newwin(1,73,0,0);
		WINDOW *player = newwin(8,32,1,1);
		WINDOW *enemy = newwin(8,32,1,40);
		WINDOW *batlog = newwin(4,32,9,0);
		WINDOW *batin= newwin(8,32,13,0);
		WINDOW *message=newwin(1,23,19,0);
		int in;
		int i;
		wbkgd(title, COLOR_PAIR(1));
		int hmx=prof->HP*30/hpmax;
		hmex=batt.profileen.idE.HP*30/hpemax;
		wattron(title,A_BOLD);
		mvwprintw (title,0,31,"Battle Mode");
		wattroff(title,A_BOLD);

		box(player,0,0);
		box(enemy,0,0);

		mvwprintw (player,1,1,"Name: %s (Level %d)", String_Peek (&prof->Name), prof->Lvl);
		
		wattron(player,COLOR_PAIR(2));
		for(int i=1;i<=hmx;i++)
		{
			mvwprintw(player,2,i," ");
		}
		wattroff(player,COLOR_PAIR(2));	

		wattron(enemy,COLOR_PAIR(3));
		for(int i=1;i<=hmex;i++)
		{
			mvwprintw(enemy,2,i," ");
		}
		wattroff(enemy,COLOR_PAIR(3));	

		mvwprintw (player,3,1,"HP  : %d", prof->HP);
		mvwprintw (player,4,1,"Str : %d", prof->Str);
		mvwprintw (player,5,1,"Def : %d", prof->Def);
		
		mvwprintw (enemy,1,1,"Name: %s", batt.profileen.Name);
		mvwprintw (enemy,3,1,"HP  : %d", batt.profileen.idE.HP);
		mvwprintw (enemy,4,1,"Str : %d", batt.profileen.idE.Str);
		mvwprintw (enemy,5,1,"Def : %d", batt.profileen.idE.Def);
		
		// Prepare battle
		Battle_GetPlayerMove (&batt, n);
		
		mvwprintw (batlog,0,0,"Enemy Moves  : %c %c %c %c", m[0], m[1], m[2], m[3]);
		mvwprintw (batlog,1,0,"Player Moves : %c %c %c %c", n[0], n[1], n[2], n[3]);
		

		if(Battle_IsFull(&batt))
		{
			mvwprintw(batlog,2,0,"Press Enter to execute.");
		}


		

		if(empt)
		{
			mvwprintw(batlog,2,0,"Can't delete moves, it's empty!");
			empt=false;
		}
		wattron(batin,A_BOLD);
		wprintw (batin,"Battle Input:\n");
		wattroff(batin,A_BOLD);

		for(i=1;i<=cn;i++)
		{
			if(i==hl)
			{
				wattron(batin,COLOR_PAIR(1));
				wprintw(batin,">");
				
			}	
			if(kmap[i]=='A')
				wprintw (batin,"Attack(A)\n");
			else if(kmap[i]=='B')
				wprintw (batin,"Block(B)\n");
			else if(kmap[i]=='F')
				wprintw (batin,"Flank(F)\n");
			else if(kmap[i]=='W')
				wprintw(batin,"Double Attack(W)\n");
			else if(kmap[i]=='X')
				wprintw(batin, "Double Flank(X)\n");
			else if(kmap[i]=='Y')
				wprintw(batin, "1.5*Attack(Y)\n");
			else if(kmap[i]=='Z')
				wprintw(batin,"1.5*Flank(Z)\n");
			else if(kmap[i]=='D')
				wprintw (batin,"Delete(D)\n");
			if(i==hl)
				wattroff(batin,COLOR_PAIR(1));
		}

			wrefresh(title);
			wrefresh(player);
			wrefresh(enemy);
			wrefresh(batlog);
			wrefresh(batin);

		if(noin)
			noin=false;
		else{
			wprintw(message,"");
			wrefresh(message);

			in=getch();
		}
		

		switch (in)
		{
			case 'f':
			case 'F':
				Battle_Add (&batt, 'F');
				break;
			case 'A':
			case 'a':
				Battle_Add (&batt, 'A');
				break;
			case 'B':
			case 'b':
				Battle_Add (&batt, 'B');
				break;
			case KEY_BACKSPACE:
			case 'D':
			case 'd':
				if(!Battle_IsEmpty(&batt)){
					Battle_Del (&batt);
				}
				else{
					empt=true;
				}
				break;
			case 'w':
			case 'W':
				if(prof->skill_ids[4])
					Battle_Add(&batt, 'W');
				break;

			case 'X':
			case 'x':
				if(prof->skill_ids[5])
					Battle_Add(&batt, 'X');
				break; 

			case 'Y':
			case 'y':
				if(prof->skill_ids[6])
					Battle_Add(&batt, 'Y');
				break;  

			case 'z':
			case 'Z':
				if(prof->skill_ids[7])
					Battle_Add(&batt, 'Z');
				break; 

			case '\n':
				if (Battle_IsFull (&batt))
				{
					loop = Battle_Act (&batt);
					
					if (loop)
					{
						Battle_Prepare (&batt);
						Battle_GetEnemyMove (&batt, m);
					}
					else
					{
						clear();
						Battle_Msg(&batt,loop);
					}
				}
				else
				{
					in=kmap[hl];
					noin=true;
				}
				break;
			case KEY_UP:
				hl--;
				break;
			case KEY_DOWN:
				hl++;
				break;

		}
		if(hl>cn)
			hl=1;
		else if(hl<1)
			hl=cn;

		if (msg)
		{
			msg = false;
			
			char buf;
			wprintw(message,"Press Enter to Continue:");	
			wrefresh(message);
			do{
				buf=getch();
			}while(buf!='\n');
		}
	}
	endwin();
}
