/* Battle.c */
#include <stdio.h>
#include <util/String.h>
#include <game/Shuffle.h>
#include <math.h>
#include <ncurses.h>

#define Graphics_SendMsg wprintw


#define BATTLE_MASK '-'

#include "Battle.h"


// Itungan

int Battle_DamageEnemy(const Profile* Player, StatE Enemy)
{
    float sum;
    int res;
   
    sum = (Player->Str - 0.25*Enemy.idE.Def)*log(Player->Lvl+1)*0.2125;
    
    res = (int)roundf(sum);
    
    return res;
}

int Battle_DamagePlayer(const Profile* Player, StatE Enemy)
{
    float sum;
    int res;
    
    sum = (Enemy.idE.Str - 0.25*Player->Def) * log(Enemy.idE.Lvl+1)*0.2;
    
    res = (int)roundf(sum);
    
    return res;

}

int Battle_DamageFinalBoss(const Profile* Player, StatE FinalBoss)
{
    int res = Battle_DamageEnemy(Player,FinalBoss);
    
    return res;
}

int Battle_DeltaEXP(StatE enemy)
{
    return (enemy.idE.Lvl * 20);
}


// Battle

void Battle_Create (Battle* self, Profile* prof, StatE enemy)
{
    self->profile = prof;
    self->profileen = enemy;
    
    self->enemy_moves = Shuffle_MoveCreate (enemy.Total_A, enemy.Total_B, enemy.Total_F);
}

void Battle_Add (Battle * self, char ch)
{
	if (!Battle_IsFull (self))
		Queue_Add (&self->player_moves,ch);
}

void Battle_Del (Battle * self)
{
	char ch;
    Queue_DelLast(&self->player_moves, &ch);
}

void Battle_Prepare (Battle * self)
{
	assert (self != NULL);
	
	Stack_Pop(&self->enemy_moves, &self->enemy_move);
	Queue_CreateEmpty (&self->player_moves);
}

bool Battle_Act(Battle * self)
{
    WINDOW *win = newwin(8,40,13,40);
    bool f = true;
    Queue* ActEnemy  = &self->enemy_move;
	Queue* ActPlayer = &self->player_moves;
    
    while((self->profile->HP > 0 && self->profileen.idE.HP > 0) && !Queue_IsEmpty(*ActEnemy))
    {
            char P;
            char E;
            Queue_DelFirst(ActPlayer,&P);
            Queue_DelFirst(ActEnemy,&E);
            if(P == 'A' && E == 'A') {
                int dp = Battle_DamagePlayer(self->profile,self->profileen);
                int de = Battle_DamageEnemy(self->profile,self->profileen);
                self->profile->HP -= dp;
                self->profileen.idE.HP -= de;
                
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",String_Peek(&self->profile->Name), self->profileen.Name,self->profileen.Name,de);
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",self->profileen.Name, String_Peek(&self->profile->Name),String_Peek(&self->profile->Name),dp);
            }
            else if (P == 'F' && E == 'F') {
                int dp = 0.9*Battle_DamagePlayer(self->profile,self->profileen);
                int de = 0.9*Battle_DamageEnemy(self->profile,self->profileen);
                self->profile->HP -= dp;
                self->profileen.idE.HP -= de;
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",String_Peek(&self->profile->Name), self->profileen.Name,self->profileen.Name,de);
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",self->profileen.Name, String_Peek(&self->profile->Name),String_Peek(&self->profile->Name),dp);
            }
            else if (P == 'A' && E == 'F') {
                int de = Battle_DamageEnemy(self->profile,self->profileen);
                self->profileen.idE.HP -= de;
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",String_Peek(&self->profile->Name), self->profileen.Name,self->profileen.Name,de);
                
            }
            else if (P == 'F' && E == 'A') {
                int dp = Battle_DamagePlayer(self->profile,self->profileen);
                self->profile->HP -= dp;
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",self->profileen.Name, String_Peek(&self->profile->Name),String_Peek(&self->profile->Name),dp);
            }
            else if (P == 'A' && E == 'B') {
                Graphics_SendMsg(win,"%s attacks %s, but it's blocked\n",String_Peek(&self->profile->Name), self->profileen.Name);

            }
            else if (P == 'B' && E == 'A') {
                Graphics_SendMsg(win,"%s attacks %s, but it's blocked\n",self->profileen.Name, String_Peek(&self->profile->Name));
            }
            else if (P == 'F' && E == 'B') {
                int de = 0.9*Battle_DamageEnemy(self->profile,self->profileen);
                self->profileen.idE.HP -= de;
                Graphics_SendMsg(win,"%s Flanks %s! %s HP-%d\n",String_Peek(&self->profile->Name), self->profileen.Name, self->profileen.Name,de);
           }
            else if (P == 'B' && E == 'F') {
                int dp = 0.9*Battle_DamagePlayer(self->profile,self->profileen);
                self->profile->HP -= dp;
                Graphics_SendMsg(win,"%s Flanks %s! %s HP-%d\n",self->profileen.Name, String_Peek(&self->profile->Name), String_Peek(&self->profile->Name),dp);
            }
            else if (P == 'W' && E == 'A') {
				int dp = Battle_DamagePlayer(self->profile,self->profileen);
                int de = 2*Battle_DamageEnemy(self->profile,self->profileen);
                self->profile->HP -= dp;
                self->profileen.idE.HP -= de;
                
                Graphics_SendMsg(win,"%s used skill! %s HP-%d\n",String_Peek(&self->profile->Name),self->profileen.Name,de);
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",self->profileen.Name, String_Peek(&self->profile->Name),String_Peek(&self->profile->Name),dp);
			}
			else if (P == 'W' && E == 'F') {
				int de = 2*Battle_DamageEnemy(self->profile,self->profileen);
                self->profileen.idE.HP -= de;
                
                Graphics_SendMsg(win,"%s used skill! %s HP-%d\n",String_Peek(&self->profile->Name),self->profileen.Name,de);
            }
            else if (P == BATTLE_MASK && E == 'A') {
				int dp = Battle_DamagePlayer(self->profile,self->profileen);
                self->profile->HP -= dp;
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",self->profileen.Name, String_Peek(&self->profile->Name),String_Peek(&self->profile->Name),dp);
			}
			else if (P == BATTLE_MASK && E == 'F') {
				int dp = 0.9*Battle_DamagePlayer(self->profile,self->profileen);
                int de = 1.5*Battle_DamageEnemy(self->profile,self->profileen);
                self->profile->HP -= dp;
                self->profileen.idE.HP -= de;
                Graphics_SendMsg(win,"%s used skill! %s HP-%d\n",String_Peek(&self->profile->Name), self->profileen.Name,de);
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",self->profileen.Name, String_Peek(&self->profile->Name),String_Peek(&self->profile->Name),dp);
            }
            else if (P == BATTLE_MASK && E == 'B') {
                int de = 2*Battle_DamageEnemy(self->profile,self->profileen);
                self->profileen.idE.HP -= de;
                Graphics_SendMsg(win,"%s used skill! %s HP-%d\n",String_Peek(&self->profile->Name), self->profileen.Name,de);
            }
                
            else if (P == 'Y' && E == 'A') {
				int dp = Battle_DamagePlayer(self->profile,self->profileen);
                int de = 3/2*Battle_DamageEnemy(self->profile,self->profileen);
                self->profile->HP -= dp;
                self->profileen.idE.HP -= de;
                
                Graphics_SendMsg(win,"%s used skill! %s HP-%d\n",String_Peek(&self->profile->Name),self->profileen.Name,de);
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",self->profileen.Name, String_Peek(&self->profile->Name),String_Peek(&self->profile->Name),dp);
			}
			else if (P == 'Y' && E == 'F') {
				int de = 3/2*Battle_DamageEnemy(self->profile,self->profileen);
                self->profileen.idE.HP -= de;
                
                Graphics_SendMsg(win,"%s used skill! %s HP-%d\n",String_Peek(&self->profile->Name),self->profileen.Name,de);
            }
             else if (P == 'Z' && E == 'A') {
				int dp = Battle_DamagePlayer(self->profile,self->profileen);
                self->profile->HP -= dp;
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",self->profileen.Name, String_Peek(&self->profile->Name),String_Peek(&self->profile->Name),dp);
			}
			else if (P == 'Z' && E == 'F') {
				int dp = 0.9*Battle_DamagePlayer(self->profile,self->profileen);
                int de = 1.125*Battle_DamageEnemy(self->profile,self->profileen);
                self->profile->HP -= dp;
                self->profileen.idE.HP -= de;
                Graphics_SendMsg(win,"%s used skill! %s HP-%d\n",String_Peek(&self->profile->Name), self->profileen.Name,de);
                Graphics_SendMsg(win,"%s attacks %s! %s HP-%d\n",self->profileen.Name, String_Peek(&self->profile->Name),String_Peek(&self->profile->Name),dp);
            }
            else if (P == 'Z' && E == 'B') {
                int de = 1.5*Battle_DamageEnemy(self->profile,self->profileen);
                self->profileen.idE.HP -= de;
                Graphics_SendMsg(win,"%s used skill! %s HP-%d\n",String_Peek(&self->profile->Name), self->profileen.Name,de);
            }
            else if ((P == 'W' || P == 'Y' ) && (E == 'B')) {
				Graphics_SendMsg(win,"%s used skill, but it's blocked\n",String_Peek(&self->profile->Name));
			}
    }
    if(self->profile->HP <= 0){
        self->profile->HP = 0;
    }
    if(self->profileen.idE.HP <= 0){
        self->profileen.idE.HP = 0;
    }
    
    if(self->profile->HP <= 0 || self->profileen.idE.HP <= 0 || Stack_IsEmpty(self->enemy_moves)) {
        f = false;
    }
    wrefresh(win);
    
    return f;
    
}

void Battle_Msg(Battle * self, bool BattleAct)
{
    if(!BattleAct) {
        if(self->profile->HP <= 0) {
            printw("You Lose");
        }
        else if(self->profileen.idE.HP <= 0) {
            self->profile->Exp += Battle_DeltaEXP(self->profileen);
            printw("You Win");
			
			// Ilangin enemy
			
			Point* p = self->profile->cur_loc_enemy;
			
			self->profile->loc_point = *p;
			*p = Point_MakePOINT (0, 0);
            
        }
        else {
            printw("Draw");
        }
    }
}

// Get

bool
Battle_IsFull (Battle*  self)
{
	return Queue_NbElmt (self->player_moves) >= 4;
}

bool
Battle_IsEmpty(Battle* self)
{
    return Queue_NbElmt (self->player_moves) == 0;
}

void
Battle_GetPlayerMove (Battle*  self,
                      char*    ch)
{
	assert (self != NULL);
	assert (ch != NULL);
	
	for (int i = 0; i < 4; i++)
		ch[i] = ' ';
	
	QueueAddress addr = Queue_Head(self->player_moves);
	
	int i = 0;
	
	while (addr != NULL)
	{
		ch[i++] = Queue_Info(addr);
		addr = Queue_Next(addr);
	}
}

void
Battle_GetEnemyMove (Battle*  self,
                     char*    ch)
{
	assert (self != NULL);
	assert (ch != NULL);
	
	QueueAddress addr = Queue_Head (self->enemy_move);
	
	ch[0] = Queue_Info(addr);
	addr = Queue_Next (addr);
	ch[1] = Queue_Info(addr);
	addr = Queue_Next (addr);
	ch[2] = Queue_Info(addr);
	addr = Queue_Next (addr);
	ch[3] = Queue_Info(addr);
	addr = Queue_Next (addr);
	
	int r = rand() % 6;
	
	switch (r)
	{
	case 0:
		ch[0] = BATTLE_MASK;
		ch[1] = BATTLE_MASK;
		break;
		
	case 1:
		ch[0] = BATTLE_MASK;
		ch[2] = BATTLE_MASK;
		break;
		
	case 2:
		ch[0] = BATTLE_MASK;
		ch[3] = BATTLE_MASK;
		break;
		
	case 3:
		ch[1] = BATTLE_MASK;
		ch[2] = BATTLE_MASK;
		break;
		
	case 4:
		ch[1] = BATTLE_MASK;
		ch[3] = BATTLE_MASK;
		break;
		
	case 5:
		ch[2] = BATTLE_MASK;
		ch[3] = BATTLE_MASK;
		break;
	}
}
