#include <assert.h>
#include <stdio.h>
#include <game/Profile.h>
#include <game/GameAsset.h>
#include <game/control/Level.h>
#include <fallback/main.h>
#include <game/Skill.h>
#include <util/List.h>
#include <ncurses.h>
#include <unistd.h>


const char* level_msg_level1[] =
{
	"Entering the hacker world......\n",
	"Here you don't need to go guns blazing or fist fighting to finish your mission.\n",
	"You only need your hacking skill to take down the invasive mastermind\n",
	"that has been monitoring and manipulating every move of your computer\n",
	"You're at level 1, good luck.\n",
	NULL
};
	
const char* level_msg_level2[] =
{
	"Level up.... You're at Level 2.\n",
	"You can feel an eye has been eyeing every inch of your move.\n",
	"You feel a bit paranoid and forget about it.\n",
	NULL
};

const char* level_msg_level3[] =
{
	"Level up.... You're at Level 3.\n",
	"As you gain more hacking skills, the more you realize...\n",
	"Even though you're on your own, there's someone\n",
	"who listens and sees every step you take.\n",
	"Who is it?\n",
	"Your thought starts to wander, but you ditch the thought.\n",
	NULL
};
	
const char* level_msg_level4[] =
{
	"Level up again.... You're at Level 4.\n",
	"There's a slight error when you're operating your computer.\n",
	"But it's nothing major, so you leave it at that.\n",
	NULL
};
	
const char* level_msg_level5[] =
{
	"I'm impressed, you have survived so far. You're at Level 5.\n",
	"There's a glitch every time you try to access your data.\n",
	"What exactly is happening?\n",
	NULL
};
	
const char* level_msg_level6[] =
{
	"BOOM! You're at Level 6.\n",
	"Wait what was that? Your computer is not working as you command it anymore!\n",
	"You should track the problem, your computer is not responding.\n",
	"You can feel the tension as you look further into your computer.\n",
	NULL
};

const char* msg_credits[] =
{
	"CLOUDY NIGHT\n",
	"\n",
	"PROJECT MANAGER\n",
	"Daniel Pintara\n",
	"\n",
	"ORIGINAL STORY\n",
	"Daniel Pintara\n",
	"Verena Severina\n",
	"Wenny Yustalim\n",
	"\n",
	"2D ARTISTS\n",
	"Daniel Pintara\n",
	"Irene Edria Devina\n",
	"Kanisius Kenneth Halim\n",
	"Verena Severina\n",
	"Wenny Yustalim\n",
	"\n",
	"PROGRAMMING\n",
	"Daniel Pintara\n",
	"Irene Edria Devina\n",
	"Kanisius Kenneth Halim\n",
	"Reinhard Linardi\n",
	"Verena Severina\n",
	"Wenny Yustalim\n",
	"\n",
	"DEBUGGING\n",
	"Daniel Pintara\n",
	"Irene Edria Devina\n",
	"Kanisius Kenneth Halim\n",
	"Reinhard Linardi\n",
	"Verena Severina\n",
	"Wenny Yustalim\n",
	"\n",
	"Very Special Thanks to William Sentosa (13515026)\n",
	"\n",
	"See You on Our Next Project\n",
	NULL
};

const char** level_msg[] =
{
	level_msg_level1,
	level_msg_level2,
	level_msg_level3,
	level_msg_level4,
	level_msg_level5,
	level_msg_level6,
	NULL
};

static void
Level_LevelUpscene (const char** msgs)
{
	bool to = true;
	
	while (*msgs != NULL)
	{
		const char* msg = *msgs;
		
		while (*msg != 0)
		{
			printw ("%c", *msg);
			
			if (to)
			{
				if (*msg == ' ')
					timeout (50);
				else
				if (*msg == '\n')
					timeout (350);
				else
					timeout (25);
				
				to = (getch () == ERR);
			}
			
			refresh ();
			msg++;
		}
		
		refresh ();
		msgs++;
	}
	
	timeout (-1);
	
	printw("\nPress Enter to continue: ");
	while (getch () != '\n');
}

void
Level_Credits (void)
{
	initscr ();
	keypad (stdscr, TRUE);
	noecho ();
	
	clear ();
	
	Level_LevelUpscene (msg_credits);
	
	endwin ();
}

static void
Skill_PrintMenu(int x)
{
	if(x==1)
		printw("Bagbiting(HP+10)");
	else if(x==2)
		printw("Daemon(Str+10)");
	else if(x==3)
		printw("Firewall(Def+10)");
	else if(x==4)
		printw("Foo(Str+20) + Double Attack");
	else if(x==5)
		printw("Jock(HP+20) + Double Flank");
	else if(x==6)
		printw("Pseudoprime(Exp+5) + 1.5*Attack");
	else if(x==7)
		printw("Shield(Def+20) + 1.5*Flank");
	else if(x==8)
		printw("Quux(Str+30)");
	else if(x==9)
		printw("SkillYuShiangWholeFish(HP+30)");
	else if(x==10)
		printw("Infinite(Str+40)");
	else if(x==11)
		printw("Sabotage(Exp+8)");
	else if(x==12)
		printw("Trojan(Def+40)");
	else if(x==13)
		printw("Glitch(HP+40)");
	else if(x==14)
		printw("AOS(Exp+15)");
	else if(x==15)
		printw("SuperProgrammer(Def+30))");
}

static void
Skill_GetSkill(Profile *prof, int y)
{
		prof->skill_ids[y]=true;
					if(y==1)
						Battle_SkillBagbiting(prof);
					else if(y==2)
						Battle_SkillDaemon(prof);
					else if(y==3)
						Battle_SkillFirewall(prof);
					else if(y==4)
						Battle_SkillFoo(prof);
					else if(y==5)
						Battle_SkillJock(prof);
                    else if(y==6)
                        Battle_SkillPseudoprime(prof);
					else if(y==7)
						Battle_SkillPseudoprime(prof);
					else if(y==8)
						Battle_SkillQuux(prof);
					else if(y==9)
						Battle_SkillYuShiangWholeFish (prof);
					else if(y==10)
                        Battle_SkillInfinite (prof);
					else if(y==11)
						Battle_SkillSabotage(prof);
					else if(y==12)
						Battle_SkillTrojan(prof);
					else if(y==13)
						Battle_SkillGlitch(prof);
					else if(y==14)
						Battle_SkillAOS(prof);
					else if(y==15)
						Battle_SkillSuperProgrammer(prof);
	
}

void
Game_Level (Profile *prof)
{

	Level_Change (prof, Game_Asset);
	initscr();
	start_color();
	init_pair(1, COLOR_BLACK,COLOR_WHITE);
	init_pair(2, COLOR_WHITE,COLOR_BLACK);
	keypad(stdscr,TRUE);
	if(prof->Lvl>=2){
	
		bool loop=true;
		int x;
		int sc;
		int ch;
		clear();
		int i,n;
		int hl=1;
		bool f=false;

		List Skill =  Skill_Available(prof);
			 n=List_Count(&Skill);
		while(loop){
			if(f){
				ch=getch();
				switch(ch)
				{
					case KEY_UP:
						hl--;break;
					case KEY_DOWN:
						hl++;break;
					default:
						hl=hl;break;
				}
				if(hl<1)
					hl+=n;
				else if(hl>n)
					hl-=n;
				
			}
		
			clear();
			f=true;
			printw("LEVEL UP!\n Congratulations You've reached level %d\n",prof->Lvl);
			printw("\nChoose your new skill:\n\n");
			ListElmt* elmt = List_First(&Skill);
			i=1;
			while (elmt != NULL)
					{
						x=ListElmt_Val(elmt, int);
						if(i==hl)
						{
							sc=x;
							attron(COLOR_PAIR(1) | A_BOLD);
								printw("> ");
								Skill_PrintMenu(x);
							attroff(COLOR_PAIR(1) | A_BOLD);
						}
						else
						{

							attron(COLOR_PAIR(2));
								Skill_PrintMenu(x);
							attroff(COLOR_PAIR(2));
						}
						printw("\n");
						i++;
						elmt=ListElmt_Next(elmt);
					}
				
				printw("Press Enter to Choose: ");
				if(ch==(int)'\n'){
					loop=false;
				}
			}
			Skill_GetSkill(prof,sc);
	}
			int ch;
			clear();
			Level_LevelUpscene(level_msg[prof->Lvl - 1]);

	endwin();
}
