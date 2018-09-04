#include <ncurses.h>
#include <stdlib.h>
#include <game/Asset.h>

/* Matrix effect */
#define MAXDROPS 500
#define MINLEN 15
#define MAXLEN 30

WINDOW* anim_buf;
WINDOW* anim_logo;

static struct drop
{
	int x, y, speed, len;
	char str[MAXLEN];
}
drop[MAXDROPS];

int w, h, i, j;

int
Anim_Rand (int a, int b)
{
	return (rand() % (b - a)) + a;
}

void
Anim_Prepare (void)
{
	for(i = 0; i < MAXDROPS; i++)
	{
		drop[i].x = Anim_Rand(0, 1000);
		drop[i].y = Anim_Rand(0, 1000);
		drop[i].speed = 5 + Anim_Rand(0, 30);
		drop[i].len = MINLEN + Anim_Rand(0, (MAXLEN - MINLEN));
		for (j = 0; j < MAXLEN; j++)
			drop[i].str[j] = Anim_Rand('0', 'z');
	}
}

void
Anim_Update (void)
{
	getmaxyx (anim_buf, h, w);

	for (i = 0; i < MAXDROPS && i < (w * h / 32); i++)
	{
		drop[i].y += drop[i].speed;
		if (drop[i].y > 1000)
		{
			drop[i].y -= 1000;
			drop[i].x = Anim_Rand(0, 1000);
		}
	}
}

#define COLOR1 (8)
#define COLOR2 (9)

void
Anim_Render (void)
{
	getmaxyx (anim_buf, h, w);

	wclear (anim_buf);
	
	for (i = 0; i < MAXDROPS && i < (w * h / 32); i++)
	{
		int x, y;

		x = drop[i].x * w / 1000 / 2 * 2;
		y = drop[i].y * (h + MAXLEN) / 1000;

		for (j = 0; j < drop[i].len; j++)
		{
			if(j < 2)
			{
				wattron (anim_buf, A_BOLD);
				wcolor_set (anim_buf, COLOR1, NULL);
			}
			else if(j < drop[i].len / 4)
			{
				wattron (anim_buf, A_BOLD);
				wcolor_set (anim_buf, COLOR2, NULL);
			}
			else if(j < drop[i].len * 4 / 5)
			{
				wcolor_set (anim_buf, COLOR2, NULL);
			}
			else
			{
				wcolor_set (anim_buf, COLOR1, NULL);
			}

			mvwaddch (anim_buf, y - j, x,
			          drop[i].str[(y - j) % drop[i].len]);
			
			wattroff (anim_buf, A_BOLD);
		}
	}
}

void
Anim_Logo (void)
{
	int scr_max = getmaxx (stdscr);
	anim_logo = newwin(Asset_Logo_R + 4, Asset_Logo_C + 4, 3, (scr_max - (Asset_Logo_C + 4)) / 2);

	WINDOW* win = derwin (anim_logo, Asset_Logo_R, Asset_Logo_C, 2, 3);
	box (anim_logo, 0, 0);
	
	int i;
	for (i = 0; i < Asset_Logo_R; i++)
	{
		move (i, 0);
		
		const char* ch = Asset_Logo[i];
		
		while (*ch)
		{
			switch (*ch)
			{
			case '0':
				wattron (win,A_REVERSE);
				waddch (win,' ');
				wattroff (win,A_REVERSE);
				break;
				
			case '1':
				waddch (win,ACS_ULCORNER);
				break;
				
			case '3':
				waddch (win,ACS_URCORNER);
				break;
				
			case '7':
				waddch (win,ACS_LLCORNER);
				break;
				
			case '9':
				waddch (win,ACS_LRCORNER);
				break;
				
			case '2':
				waddch (win,ACS_HLINE);
				break;
				
			case '4':
				waddch (win,ACS_VLINE);
				break;
				
			default:
				waddch (win,*ch);
				break;
			}
			
			ch++;
		}
	}
}

void
Anim_Init (void)
{
	getmaxyx (stdscr, h, w);
	anim_buf = newwin (h, w, 0, 0);
	
	Anim_Logo ();
	Anim_Prepare ();
}

void
Anim_Frame (void)
{
	Anim_Update ();
	Anim_Render ();
	
	overwrite (anim_logo, anim_buf);
	overwrite (anim_buf, stdscr);
}
