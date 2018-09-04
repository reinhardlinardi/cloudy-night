/*
 * Brightsouls v0.1
 */

#include <stdlib.h>
#include <ncurses.h>

#include "Asset.h"


// Logo

int Asset_Logo_R = 16;
int Asset_Logo_C = 80;

const char* Asset_Logo[] =
{
	"       *                                               .-~~~-.                  ",
	"                      '*                       .- ~ ~-(       )_ _              ",
	"                                              /                    ~ -.         ",
	"    0000003003 *'   0000003 003   0030000003 003   003                 ~ -.     ",
	"   00122229004     001222003004   004001220037003 0019                     ',   ",
	"*' 004    :004     004   004004 * 004004  004 7000019                      .'   ",
	"   004    !004     004   004004   004004  004  70019- ._ ,. ,.,.,., ,.. -~      ",
	"   700000030000000370000001970000001900000019   004                             ",
	"    722222972222229 7222229  7222229 7222229 *' 729                             ",
	"          |_               0003   003003 0000003 003  003000000003              ",
	"       ,  | `.             00003  00400400122229 004  004722001229      .       ",
	" --- --+-<#>-+- ---  --  - 001003 004004004  000300000004   004  *'     ;       ",
	"       `._|_,'             0047003004004004   00400122004   004     - --+- -    ",
	"          T        *'      004 700004004700000019004  004   004         !       ",
	"  *       !                729  72229729 7222229 729  729   729         .       ",
	"          :         . :   ",
	NULL
};


// Menu

int Asset_Menu_R = 4;
int Asset_Menu_C = 12;

const char* Asset_Menu_New   = "New  Game";
const char* Asset_Menu_Start = "Start  Game";
const char* Asset_Menu_Load  = "Load Game";
const char* Asset_Menu_Exit  = "Exit Game";


// Battle

int Asset_Battle_R = 4;
int Asset_Battle_C = 9;

const char* Asset_Battle_Fight = "Fight  ";
const char* Asset_Battle_Flank = "Flank  ";
const char* Asset_Battle_Block = "Block  ";
const char* Asset_Battle_Skill = "Skill >";


// Strings

const char* Asset_Name = "Name:";
