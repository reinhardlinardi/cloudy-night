#include <stdio.h>
#include <signal.h>
#include <ncurses.h>
#include "Io.h"

//nama file eksternal penyimpanan
char gameasset_file[]="data/gameasset.txt";
char profile_file[]="data/profile.txt";

bool is_load_gameasset = true;

void no_end_character()
/* I.S. ada signal segfault  */
/* F.S. signal segfault dihandle */
{
	if(is_load_gameasset)
	{
		printf("X-files : Scanned blank line or no END character in \"%s\".\n",gameasset_file);
		printf("Gameasset load failed.\n");
	}
	else
	{
		printf("X-files : Scanned blank line or no END character in \"%s\".\n",profile_file);
		printf("Profile load failed.\n");
	}
	
	endwin();
	exit(0); //terminate program with return value 0
}

void save_profile(Profile* profile,int max_profile,int update_index)
/* I.S. profile terdefinisi */
/* F.S. Semua data profile tersimpan dalam file eksternal */
{
	int i,j,k; //iterator
	int mask; //for bitmask
		
	FILE* out = fopen(profile_file,"w"); //open file in write mode
	
	for(i=1;i<=max_profile;i++)
	{
		fprintf(out,"[");
		
		for(j=0;j<profile[i].Name.len;j++)
		{
			fprintf(out,"%c",profile[i].Name.buf[j]); //Save profile name
		}
		
		fprintf(out,"]\n");
		
		fprintf(out,"Lvl = %d\n",profile[i].Lvl); //Save profile level
		fprintf(out,"HP = %d\n",profile[i].HP); //Save profile HP
		fprintf(out,"Str = %d\n",profile[i].Str); //Save profile strength
		fprintf(out,"Def = %d\n",profile[i].Def); //Save profile defense
		fprintf(out,"Exp = %d\n",profile[i].Exp); //Save profile experience
		
		fprintf(out,"map_ids = ");
		
		for(j=1;j<=6;j++)
		{
			if(j!=6) fprintf(out,"%d ",profile[i].map_ids[j]); //Save profile map ids
			else fprintf(out,"%d\n",profile[i].map_ids[j]);
		}
		
		fprintf(out,"loc_map_id = %d\n",profile[i].loc_map_id); //Save current map location id
		fprintf(out,"loc_point.x = %d\n",Row(profile[i].loc_point)); //Save current x axis position
		fprintf(out,"loc_point.y = %d\n",Col(profile[i].loc_point)); //Save current y axis position
		
		mask = 0; //set mask = 0
		
		for(j=1;j<=15;j++)
		{
			if(profile[i].skill_ids[j]) mask |= (1 << (j-1));
		}
		
		fprintf(out,"skill_ids = %d\n",mask); //Save skill_ids
		
		for(j=1;j<=6;j++)
		{
			fprintf(out,"%d\n",j);
			
			fprintf(out,"loc_enemy.x = ");
			
			for(k=1;k<=10;k++)
			{
				if(k!=10) fprintf(out,"%d ",Row(profile[i].loc_enemy[j][k]));
				else fprintf(out,"%d\n",Row(profile[i].loc_enemy[j][k]));
			}
			
			fprintf(out,"loc_enemy.y = ");
			
			for(k=1;k<=10;k++)
			{
				if(k!=10) fprintf(out,"%d ",Col(profile[i].loc_enemy[j][k]));
				else fprintf(out,"%d\n",Col(profile[i].loc_enemy[j][k]));
			}
			
			fprintf(out,"loc_medicine.x = ");
			
			for(k=1;k<=10;k++)
			{
				if(k!=10) fprintf(out,"%d ",Row(profile[i].loc_medicine[j][k]));
				else fprintf(out,"%d\n",Row(profile[i].loc_medicine[j][k]));
			}
			
			fprintf(out,"loc_medicine.y = ");
			
			for(k=1;k<=10;k++)
			{
				if(k!=10) fprintf(out,"%d ",Col(profile[i].loc_medicine[j][k]));
				else fprintf(out,"%d\n",Col(profile[i].loc_medicine[j][k]));
			}
		}
		
		fprintf(out,"loc_boss.x = %d\n",Row(profile[i].loc_boss));
		fprintf(out,"loc_boss.y = %d\n",Col(profile[i].loc_boss));
		fprintf(out,"loc_map_id_boss = %d\n",profile[i].loc_map_id_boss);
		
		if(profile[i].is_boss) fprintf(out,"is_boss = T\n");
		else fprintf(out,"is_boss = F\n");
		
		if(i == update_index)
		{
			//Save current local time
			time_t time_now = time(0); //get current local time
			long long t = (long long)time_now; //convert to seconds
			t %= 86400; //only consider hour, minutes, and seconds
			
			Hour(profile[i].save_time) = ((t / 3600)+7)%24; //save hour of time_save
			fprintf(out,"save_time = %lld:",((t / 3600)+7)%24); //print hour in UTC + 7
			t %= 3600;
			
			Minute(profile[i].save_time) = t / 60; //save minute of time_save
			fprintf(out,"%lld:",t / 60); //print minute
			t %= 60;
			
			Second(profile[i].save_time) = t; //save second of time_save
			fprintf(out,"%lld\n",t); //print second
		}
		else fprintf(out,"save_time = %d:%d:%d\n",Hour(profile[i].save_time),Minute(profile[i].save_time),Second(profile[i].save_time)); //Save time terakhir pemain klik save game
	}
	
	fprintf(out,"@"); //Print END character (penanda akhir file)
	
	fclose(out); //close file
}
    
void load_profile(Profile *profile,String name)
/* I.S. profile terdefinisi */
/* F.S. Semua data profile dengan nama name tersimpan dalam struktur data Profile */
{
	int i; //iterator
	int lc = 1; //line counter
	int check_id; //id for attribute checking
	int line;
	
	String s; //for string input
	int val; //for integer input
	int a,b,c,d,e,f,v,x,y,z; //for integer input
	bool found = false; //false = skip other's player data
	
	char in; //for char input
	
	for(i=0;i<CKata.len;i++) CKata.c[i]='\0'; //clear CKata
	CKata.len = 0; //initialization
	
	STARTKATA(profile_file); //Start reading
	
	while(!EndKata)
	{
		check_id=lc%46;
		if(check_id==0) check_id=46;
		
		switch(check_id) //one attribute per line
		{
			case 1 :
				if(!found) //search profile name while not found
				{
					String_Create(&s);
					
					for(i=1;i<(CKata.len)-1;i++) String_AppendChar(&s,CKata.c[i]); //get profile name
				
					if(String_IsEqual(&s,&name)) found = true; //if player's profile found
				}
				else EndKata = true; //quit when done
				
				break;
				
			case 2 :
				if(found)
				{
					sscanf(CKata.c,"Lvl = %d",&val); //get profile level
					(*profile).Lvl = val;
				}
				
				break;
				
			case 3 :
				if(found)
				{
					sscanf(CKata.c,"HP = %d",&val); //get profile HP
					(*profile).HP = val;
				}
				
				break;
			
			case 4 :
				if(found)
				{
					sscanf(CKata.c,"Str = %d",&val); //get profile strength
					(*profile).Str = val;
				}
				
				break;
				
			case 5 :
				if(found)
				{
					sscanf(CKata.c,"Def = %d",&val); //get profile defense
					(*profile).Def = val;
				}
				
				break;
				
			case 6 :
				if(found)
				{
					sscanf(CKata.c,"Exp = %d",&val); //get profile experience
					(*profile).Exp = val;
				}
				
				break;
				
			case 7 :
				if(found)
				{
					sscanf(CKata.c,"map_ids = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f); //get profile map_ids
					(*profile).map_ids[1] = a;
					(*profile).map_ids[2] = b;
					(*profile).map_ids[3] = c;
					(*profile).map_ids[4] = d;
					(*profile).map_ids[5] = e;
					(*profile).map_ids[6] = f;
				}
				
				break;
				
			case 8 :
				if(found)
				{
					sscanf(CKata.c,"loc_map_id = %d",&val); //get profile location map id
					(*profile).loc_map_id = val;
				}
				
				break;
				
			case 9 :
				if(found)
				{
					sscanf(CKata.c,"loc_point.x = %d",&val); //get profile x axis location
					Row((*profile).loc_point) = val;
				}
				
				break;
				
			case 10 :
				if(found)
				{
					sscanf(CKata.c,"loc_point.y = %d",&val); //get profile y axis location
					Col((*profile).loc_point) = val;
				}
				
				break;
							
			case 11 :
				if(found)
				{
					sscanf(CKata.c,"skill_ids = %d",&val); //get profile skill_ids
					
					for(i=0;i<16;i++) //load 16 skills
					{
						if((val & (1 << i)) != 0) (*profile).skill_ids[i+1] = true;  //if (i+1)th skill acquired by player
					}
				}
				
				break;
				
			case 12 :
				if(found)
				{
					line = 6;
					
					while(line--)
					{
						ADVKATA();
						lc++;
						
						sscanf(CKata.c,"loc_enemy.x = %d %d %d %d %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f,&v,&x,&y,&z);
						Row((*profile).loc_enemy[6-line][1]) = a;
						Row((*profile).loc_enemy[6-line][2]) = b;
						Row((*profile).loc_enemy[6-line][3]) = c;
						Row((*profile).loc_enemy[6-line][4]) = d;
						Row((*profile).loc_enemy[6-line][5]) = e;
						Row((*profile).loc_enemy[6-line][6]) = f;
						Row((*profile).loc_enemy[6-line][7]) = v;
						Row((*profile).loc_enemy[6-line][8]) = x;
						Row((*profile).loc_enemy[6-line][9]) = y;
						Row((*profile).loc_enemy[6-line][10]) = z;
						
						ADVKATA();
						lc++;
						
						sscanf(CKata.c,"loc_enemy.y = %d %d %d %d %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f,&v,&x,&y,&z);
						Col((*profile).loc_enemy[6-line][1]) = a;
						Col((*profile).loc_enemy[6-line][2]) = b;
						Col((*profile).loc_enemy[6-line][3]) = c;
						Col((*profile).loc_enemy[6-line][4]) = d;
						Col((*profile).loc_enemy[6-line][5]) = e;
						Col((*profile).loc_enemy[6-line][6]) = f;
						Col((*profile).loc_enemy[6-line][7]) = v;
						Col((*profile).loc_enemy[6-line][8]) = x;
						Col((*profile).loc_enemy[6-line][9]) = y;
						Col((*profile).loc_enemy[6-line][10]) = z;
						
						ADVKATA();
						lc++;
						
						sscanf(CKata.c,"loc_medicine.x = %d %d %d %d %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f,&v,&x,&y,&z);
						Row((*profile).loc_medicine[6-line][1]) = a;
						Row((*profile).loc_medicine[6-line][2]) = b;
						Row((*profile).loc_medicine[6-line][3]) = c;
						Row((*profile).loc_medicine[6-line][4]) = d;
						Row((*profile).loc_medicine[6-line][5]) = e;
						Row((*profile).loc_medicine[6-line][6]) = f;
						Row((*profile).loc_medicine[6-line][7]) = v;
						Row((*profile).loc_medicine[6-line][8]) = x;
						Row((*profile).loc_medicine[6-line][9]) = y;
						Row((*profile).loc_medicine[6-line][10]) = z;
						
						ADVKATA();
						lc++;
						
						sscanf(CKata.c,"loc_medicine.y = %d %d %d %d %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f,&v,&x,&y,&z);
						Col((*profile).loc_medicine[6-line][1]) = a;
						Col((*profile).loc_medicine[6-line][2]) = b;
						Col((*profile).loc_medicine[6-line][3]) = c;
						Col((*profile).loc_medicine[6-line][4]) = d;
						Col((*profile).loc_medicine[6-line][5]) = e;
						Col((*profile).loc_medicine[6-line][6]) = f;
						Col((*profile).loc_medicine[6-line][7]) = v;
						Col((*profile).loc_medicine[6-line][8]) = x;
						Col((*profile).loc_medicine[6-line][9]) = y;
						Col((*profile).loc_medicine[6-line][10]) = z;
						
						ADVKATA();
						lc++;
					}
				}
				
			case 42 :
				if(found)
				{
					sscanf(CKata.c,"loc_boss.x = %d",&val); //get profile x axis location
					Row((*profile).loc_boss) = val;
				}
				
				break;
					
			case 43 :
				if(found)
				{
					sscanf(CKata.c,"loc_boss.y = %d",&val); //get profile x axis location
					Col((*profile).loc_boss) = val;
				}
				
				break;
						
			case 44 :
				if(found)
				{
					sscanf(CKata.c,"loc_map_id_boss = %d",&val); //get profile x axis location
					(*profile).loc_map_id_boss = val;
				}
				
				break;
				
			case 45 :
				if(found)
				{
					sscanf(CKata.c,"is_boss = %c",&in);
					
					if(in=='T') (*profile).is_boss = true;
					else (*profile).is_boss = false;
				}
			
				break;
				
			case 46 :
				if(found)
				{
					sscanf(CKata.c,"save_time = %d:%d:%d",&a,&b,&c); //get profile save time
					Hour((*profile).save_time) = a;
					Minute((*profile).save_time) = b;
					Second((*profile).save_time) = c;
				}
				
				break;
		}
		
		ADVKATA(); //read next line
		lc++; //add line counter
	}
}

void load_gameasset(GameAsset *gameasset)
/* I.S. gameasset terdefinisi */
/* F.S. Semua data profile tersimpan dalam struktur data GameAsset */
{
	if(!check_error_gameasset())
	{
		int a,b,c,d,e,f; //for integer input
		String s;
		
		char as[50],bs[50],cs[50],ds[50],es[50],fs[50]; //for char array input
		char v,x,y,z; //single char input
		
		int i,j; //iterator
		
		/* Error checking starts here */
		
		int lc = 1; //line counter
		int line;
		
		for(i=0;i<CKata.len;i++) CKata.c[i]='\0'; //clear CKata
		CKata.len = 0; //initialization
		STARTKATA(gameasset_file); //Start reading
		
		while(!EndKata) //read until End
		{
			switch(lc)
			{
				case 2 : //get player level
					sscanf(CKata.c,"Lvl = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
					(*gameasset).Player.idP[1].Lvl = a;
					(*gameasset).Player.idP[2].Lvl = b;
					(*gameasset).Player.idP[3].Lvl = c;
					(*gameasset).Player.idP[4].Lvl = d;
					(*gameasset).Player.idP[5].Lvl = e;
					(*gameasset).Player.idP[6].Lvl = f;
				
					break;
					
				case 3 : //get player HP
					sscanf(CKata.c,"HP = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
					(*gameasset).Player.idP[1].HP = a;
					(*gameasset).Player.idP[2].HP = b;
					(*gameasset).Player.idP[3].HP = c;
					(*gameasset).Player.idP[4].HP = d;
					(*gameasset).Player.idP[5].HP = e;
					(*gameasset).Player.idP[6].HP = f;
				
					break;
					
				case 4 : //get player strength
					sscanf(CKata.c,"Str = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
					(*gameasset).Player.idP[1].Str = a;
					(*gameasset).Player.idP[2].Str = b;
					(*gameasset).Player.idP[3].Str = c;
					(*gameasset).Player.idP[4].Str = d;
					(*gameasset).Player.idP[5].Str = e;
					(*gameasset).Player.idP[6].Str = f;
				
					break;
					
				case 5 : //get player defense
					sscanf(CKata.c,"Def = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
					(*gameasset).Player.idP[1].Def = a;
					(*gameasset).Player.idP[2].Def = b;
					(*gameasset).Player.idP[3].Def = c;
					(*gameasset).Player.idP[4].Def = d;
					(*gameasset).Player.idP[5].Def = e;
					(*gameasset).Player.idP[6].Def = f;
				
					break;
					
				case 6 : //get player experience
					sscanf(CKata.c,"EXP = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
					(*gameasset).Player.EXP[1] = a;
					(*gameasset).Player.EXP[2] = b;
					(*gameasset).Player.EXP[3] = c;
					(*gameasset).Player.EXP[4] = d;
					(*gameasset).Player.EXP[5] = e;
					(*gameasset).Player.EXP[6] = f;
					
					break;
					
				case 8 : //get enemy name
					sscanf(CKata.c,"Name = %s %s %s %s %s %s",as,bs,cs,ds,es,fs);
					String_CreateFromCStr(&s,as);
					(*gameasset).Enemy[1].Name = String_Eject(&s);
					String_CreateFromCStr(&s,bs);
					(*gameasset).Enemy[2].Name = String_Eject(&s);
					String_CreateFromCStr(&s,cs);
					(*gameasset).Enemy[3].Name = String_Eject(&s);
					String_CreateFromCStr(&s,ds);
					(*gameasset).Enemy[4].Name = String_Eject(&s);
					String_CreateFromCStr(&s,es);
					(*gameasset).Enemy[5].Name = String_Eject(&s);
					String_CreateFromCStr(&s,fs);
					(*gameasset).Enemy[6].Name = String_Eject(&s);
					
					break;
					
				case 9 : //get enemy level
					sscanf(CKata.c,"Lvl = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
					(*gameasset).Enemy[1].idE.Lvl = a;
					(*gameasset).Enemy[2].idE.Lvl = b;
					(*gameasset).Enemy[3].idE.Lvl = c;
					(*gameasset).Enemy[4].idE.Lvl = d;
					(*gameasset).Enemy[5].idE.Lvl = e;
					(*gameasset).Enemy[6].idE.Lvl = f;
					
					break;
					
				case 10 : //get enemy HP
					sscanf(CKata.c,"HP = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
					(*gameasset).Enemy[1].idE.HP = a;
					(*gameasset).Enemy[2].idE.HP = b;
					(*gameasset).Enemy[3].idE.HP = c;
					(*gameasset).Enemy[4].idE.HP = d;
					(*gameasset).Enemy[5].idE.HP = e;
					(*gameasset).Enemy[6].idE.HP = f;
				
					break;
					
				case 11 : //get enemy strength
					sscanf(CKata.c,"Str = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
					(*gameasset).Enemy[1].idE.Str = a;
					(*gameasset).Enemy[2].idE.Str = b;
					(*gameasset).Enemy[3].idE.Str = c;
					(*gameasset).Enemy[4].idE.Str = d;
					(*gameasset).Enemy[5].idE.Str = e;
					(*gameasset).Enemy[6].idE.Str = f;
				
					break;
					
				case 12 : //get enemy defense
					sscanf(CKata.c,"Def = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
					(*gameasset).Enemy[1].idE.Def = a;
					(*gameasset).Enemy[2].idE.Def = b;
					(*gameasset).Enemy[3].idE.Def = c;
					(*gameasset).Enemy[4].idE.Def = d;
					(*gameasset).Enemy[5].idE.Def = e;
					(*gameasset).Enemy[6].idE.Def = f;
				
					break;
				
				case 17 : //get final boss name
					sscanf(CKata.c,"Name = %s",as);
					String_CreateFromCStr(&s,as);
					(*gameasset).FinalBoss.Name = String_Eject(&s);
				
					break;
					
				case 18 : //get final boss level
					sscanf(CKata.c,"Lvl = %d",&a);
					(*gameasset).FinalBoss.idE.Lvl = a;
					
					break;
					
				case 19 : //get final boss HP
					sscanf(CKata.c,"HP = %d",&a);
					(*gameasset).FinalBoss.idE.HP = a;
				
					break;
					
				case 20 : //get final boss strength
					sscanf(CKata.c,"Str = %d",&a);
					(*gameasset).FinalBoss.idE.Str = a;
				
					break;
					
				case 21 : //get final boss defense
					sscanf(CKata.c,"Def = %d",&a);
					(*gameasset).FinalBoss.idE.Def = a;
				
					break;
					
				case 27 : //get connection graph
					line = 6;
					
					while(line--)
					{
						sscanf(CKata.c,"%d%c %d%c %d%c %d%c",&a,&v,&b,&x,&c,&y,&d,&z);
						
						if(!(a==0 && v=='N')) AddAdj(&(gameasset->WholeMap.AllAreaCombine),6-line,'R',a,v);
						if(!(b==0 && x=='N')) AddAdj(&(gameasset->WholeMap.AllAreaCombine),6-line,'D',b,x);
						if(!(c==0 && y=='N')) AddAdj(&(gameasset->WholeMap.AllAreaCombine),6-line,'L',c,y);
						if(!(d==0 && z=='N')) AddAdj(&(gameasset->WholeMap.AllAreaCombine),6-line,'U',d,z);
						
						ADVKATA();
						lc++;
					}
					
					break;
				
				case 34 :
					line = 12;
					
					while(line--)
					{
						ADVKATA();
						lc++;
						
						for(i=1;i<=24;i++)
						{
							for(j=1;j<=80;j++)
							{
								Matrix_Elmt((*gameasset).WholeMap.Area[12-line],i,j) = CKata.c[j-1];
							}
							
							ADVKATA();
							lc++;
						}
					}
				
				case 335 :
					String_CreateFromCStr(&s,CKata.c);
					(*gameasset).Win = String_Eject(&s);
					break;
					
				case 337 :
					String_CreateFromCStr(&s,CKata.c);
					(*gameasset).Lose = String_Eject(&s);
					break;
				
				default :
					break;
			}
			
			ADVKATA(); //read next line
			lc++;
		}
	}
	else
	{
		endwin();
		exit(0);
	}
}

void load_enemymoves(GameAsset *gameasset)
/* I.S. gameasset terdefinisi */
/* F.S. Enemy moves tersimpan dalam struktur data GameAsset */
{
	int a,b,c,d,e,f; //for integer input
	int lc = 1; //line counter
	int i; //iterator
	
	for(i=0;i<CKata.len;i++) CKata.c[i]='\0'; //clear CKata
	CKata.len = 0; //initialization
	STARTKATA(gameasset_file); //Start reading
	
	while(!EndKata) //read until End
	{
		switch(lc)
		{
			case 13 : //get enemy total flank
				sscanf(CKata.c,"Total_F = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
				(*gameasset).Enemy[1].Total_F = a;
				(*gameasset).Enemy[2].Total_F = b;
				(*gameasset).Enemy[3].Total_F = c;
				(*gameasset).Enemy[4].Total_F = d;
				(*gameasset).Enemy[5].Total_F = e;
				(*gameasset).Enemy[6].Total_F = f;
				
				break;
				
			case 14 : //get enemy total attack
				sscanf(CKata.c,"Total_A = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
				(*gameasset).Enemy[1].Total_A = a;
				(*gameasset).Enemy[2].Total_A = b;
				(*gameasset).Enemy[3].Total_A = c;
				(*gameasset).Enemy[4].Total_A = d;
				(*gameasset).Enemy[5].Total_A = e;
				(*gameasset).Enemy[6].Total_A = f;
					
				break;
					
			case 15 : //get enemy total block
				sscanf(CKata.c,"Total_B = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
				(*gameasset).Enemy[1].Total_B = a;
				(*gameasset).Enemy[2].Total_B = b;
				(*gameasset).Enemy[3].Total_B = c;
				(*gameasset).Enemy[4].Total_B = d;
				(*gameasset).Enemy[5].Total_B = e;
				(*gameasset).Enemy[6].Total_B = f;
			
				break;
				
			case 22 : //get final boss total flank
				sscanf(CKata.c,"Total_F = %d",&a);
				(*gameasset).FinalBoss.Total_F = a;
				
				break;
			
			case 23 : //get final boss total attack
				sscanf(CKata.c,"Total_A = %d",&a);
				(*gameasset).FinalBoss.Total_A = a;
				
				break;
					
			case 24 : //get final boss total block
				sscanf(CKata.c,"Total_B = %d",&a);
				(*gameasset).FinalBoss.Total_B = a;
				
				EndKata = true; //quit when done
				
				break;
			
			default :
				break;
		}
		
		ADVKATA(); //read next line
		lc++;
	}
}

bool check_error_profile()
/* I.S. File eksternal profile terdefinisi, isi sembarang */
/* F.S. File eksternal profile tidak mengandung error dan siap dibaca */
{
	int check_id; //id for attribute checking
	
	int val; //for integer input
	int a,b,c,d,e,f,v,x,y,z; //for integer input
	bool error = false; //true = format error in external file
	
	/* Error checking starts here */
	
	int lc = 1; //line counter
	int i; //iterator
	int line;
	
	char in; //for char input
	
	for(i=0;i<CKata.len;i++) CKata.c[i]='\0'; //clear CKata
	CKata.len = 0; //initialization
	STARTKATA(profile_file); //Start reading
	
	while(!EndKata) //read until END
	{
		check_id=lc%46;
		if(check_id==0) check_id=46;
		
		switch(check_id) //one attribute per line
		{
			case 1 : //check profile name format validity or check END character
				if(CKata.c[0]!='[' && CKata.c[0]!='@') //not profile name or END character
				{
					error = true;
					printf("X-files : Unknown profile name format or END character in \"%s\", line %d.\n",profile_file,lc);
				}
				else
				{
					if(CKata.c[(CKata.len)-1]!=']' || CKata.len<3) //invalid profile name
					{
						error = true;
						printf("X-files : Unknown profile name format in \"%s\", line %d.\n",profile_file,lc);
					}
				}
				
				break;
				
			case 2 : //check profile level format validity
				if(sscanf(CKata.c,"Lvl = %d",&val)!=1) //if string format not satisfied
				{
					error = true;
					printf("X-files : Unknown profile Lvl format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
				
			case 3 : //check profile HP format validity
				if(sscanf(CKata.c,"HP = %d",&val)!=1)
				{
					error = true;
					printf("X-files : Unknown profile HP format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
			
			case 4 : //check profile strength format validity
				if(sscanf(CKata.c,"Str = %d",&val)!=1)
				{
					error = true;
					printf("X-files : Unknown profile Str format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
				
			case 5 : //check profile defense format validity
				if(sscanf(CKata.c,"Def = %d",&val)!=1)
				{
					error = true;
					printf("X-files : Unknown profile Def format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
				
			case 6 : //check profile experience format validity
				if(sscanf(CKata.c,"Exp = %d",&val)!=1)
				{
					error = true;
					printf("X-files : Unknown profile Exp format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
				
			case 7 : //check profile map ids format validity
				if(sscanf(CKata.c,"map_ids = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown profile map_ids format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
				
			case 8 : //check profile location map id format validity
				if(sscanf(CKata.c,"loc_map_id = %d",&val)!=1)
				{
					error = true;
					printf("X-files : Unknown profile loc_map_id format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
				
			case 9 : //check profile x axis location format validity
				if(sscanf(CKata.c,"loc_point.x = %d",&val)!=1)
				{
					error = true;
					printf("X-files : Unknown profile loc_point.x format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
				
			case 10 : //check profile y axis location format validity
				if(sscanf(CKata.c,"loc_point.y = %d",&val)!=1)
				{
					error = true;
					printf("X-files : Unknown profile loc_point.y format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
				
			case 11 : //check profile skill ids format validity
				if(sscanf(CKata.c,"skill_ids = %d",&val)!=1)
				{
					error = true;
					printf("X-files : Unknown profile skill_ids format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
				
			case 12 :
				line = 6;
				
				while(!EndKata && line--)
				{
					if(sscanf(CKata.c,"%d",&a)!=1)
					{
						error = true;
						printf("X-files : Unknown map enemy and medicine format in \"%s\", line %d.\n",profile_file,lc);
					}
					
					ADVKATA();
					lc ++;
					
					if(!EndKata)
					{
						if(sscanf(CKata.c,"loc_enemy.x = %d %d %d %d %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f,&v,&x,&y,&z)!=10)
						{
							error = true;
							printf("X-files : Unknown enemy x axis location format in \"%s\", line %d.\n",profile_file,lc);
						}
					}
					
					ADVKATA();
					lc++;
					
					if(!EndKata)
					{
						if(sscanf(CKata.c,"loc_enemy.y = %d %d %d %d %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f,&v,&x,&y,&z)!=10)
						{
							error = true;
							printf("X-files : Unknown enemy y axis location format in \"%s\", line %d.\n",profile_file,lc);
						}
					}
					
					ADVKATA();
					lc++;
					
					if(!EndKata)
					{
						if(sscanf(CKata.c,"loc_medicine.x = %d %d %d %d %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f,&v,&x,&y,&z)!=10)
						{
							error = true;
							printf("X-files : Unknown medicine x axis location format in \"%s\", line %d.\n",profile_file,lc);
						}
					}
					
					ADVKATA();
					lc++;
					
					if(!EndKata)
					{
						if(sscanf(CKata.c,"loc_medicine.y = %d %d %d %d %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f,&v,&x,&y,&z)!=10)
						{
							error = true;
							printf("X-files : Unknown medicine y axis location format in \"%s\", line %d.\n",profile_file,lc);
						}
					}
					
					ADVKATA();
					lc++;
				}
			
			case 42 : //check boss x axis format validity
				if(sscanf(CKata.c,"loc_boss.x = %d",&a)!=1)
				{
					error = true;
					printf("X-files : Unknown boss x axis format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
					
			case 43 : //check boss y axis format validity
				if(sscanf(CKata.c,"loc_boss.y = %d",&a)!=1)
				{
					error = true;
					printf("X-files : Unknown boss y axis format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
						
			case 44 : //check boss map id format validity
				if(sscanf(CKata.c,"loc_map_id_boss = %d",&a)!=1)
				{
					error = true;
					printf("X-files : Unknown boss map id format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
				
			case 45 : //check is_boss format validity
				if(sscanf(CKata.c,"is_boss = %c",&in)!=1 || (!(in=='F' || in=='T')))
				{
					error = true;
					printf("X-files : Unknown profile is_boss format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
				
			case 46 : //check save time format validity
				if(sscanf(CKata.c,"save_time = %d:%d:%d",&a,&b,&c)!=3)
				{
					error = true;
					printf("X-files : Unknown profile save_time format in \"%s\", line %d.\n",profile_file,lc);
				}
				
				break;
		}
		
		ADVKATA(); //read next line
		lc++; //add line counter
	}
	
	if(error) printf("Profile load failed.\n");
	
	return error;
}

bool check_error_gameasset()
/* I.S. File eksternal gameasset terdefinisi, isi sembarang */
/* F.S. File eksternal gameasset tidak mengandung error dan siap dibaca */
{
	String s,in; //for string
	
	int a,b,c,d,e,f; //for integer input
	bool error = false; //true = format error in external file
	
	char as[50],bs[50],cs[50],ds[50],es[50],fs[50]; //for char array input
	char v,x,y,z; //single char input
	
	int i,j; //iterator
	
	/* Error checking starts here */
	
	int lc = 1; //line counter
	int line;
	
	for(i=0;i<CKata.len;i++) CKata.c[i]='\0'; //clear CKata
	CKata.len = 0; //initialization
	STARTKATA(gameasset_file); //Start reading
	
	while(!EndKata) //read until END
	{
		switch(lc)
		{
			case 1 : //check player gameasset format validity
				String_CreateFromCStr(&s,"[Player]");
				String_CreateFromCStr(&in,CKata.c);
				
				if(!String_IsEqual(&in,&s))
				{
					error = true;
					printf("X-files : Unknown player gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
			
			case 2 : //check player level format validity
				if(sscanf(CKata.c,"Lvl = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown player Lvl gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
			
			case 3 : //check player HP format validity
				if(sscanf(CKata.c,"HP = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown player HP gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 4 : //check player strength format validity
				if(sscanf(CKata.c,"Str = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown player Str gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 5 : //check player defense format validity
				if(sscanf(CKata.c,"Def = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown player Def gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 6 : //check player experience format validity
				if(sscanf(CKata.c,"EXP = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown player EXP gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 7 : //check enemy gameasset format validity
				String_CreateFromCStr(&s,"[Enemy]");
				String_CreateFromCStr(&in,CKata.c);
				
				if(!String_IsEqual(&in,&s))
				{
					error = true;
					printf("X-files : Unknown enemy gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
			
			case 8 : //check enemy name format validity
				if(sscanf(CKata.c,"Name = %s %s %s %s %s %s",as,bs,cs,ds,es,fs)!=6)
				{
					error = true;
					printf("X-files : Unknown enemy name gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 9 : //check enemy level format validity
				if(sscanf(CKata.c,"Lvl = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown enemy Lvl gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
			
			case 10 : //check enemy HP format validity
				if(sscanf(CKata.c,"HP = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown enemy HP gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 11 : //check enemy strength format validity
				if(sscanf(CKata.c,"Str = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown enemy Str gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 12 : //check enemy defense format validity
				if(sscanf(CKata.c,"Def = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown enemy Def gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 13 : //check enemy total flank format validity
				if(sscanf(CKata.c,"Total_F = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown enemy Total_F gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 14 : //check enemy total attack format validity
				if(sscanf(CKata.c,"Total_A = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown enemy Total_A gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 15 : //check enemy total block format validity
				if(sscanf(CKata.c,"Total_B = %d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)!=6)
				{
					error = true;
					printf("X-files : Unknown enemy Total_B gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 16 : //check final boss format validity
				String_CreateFromCStr(&s,"[FinalBoss]");
				String_CreateFromCStr(&in,CKata.c);
				
				if(!String_IsEqual(&in,&s))
				{
					error = true;
					printf("X-files : Unknown final boss gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 17 : //check final boss name format validity
				if(sscanf(CKata.c,"Name = %s",as)!=1)
				{
					error = true;
					printf("X-files : Unknown final boss name gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 18 : //check final boss level format validity
				if(sscanf(CKata.c,"Lvl = %d",&a)!=1)
				{
					error = true;
					printf("X-files : Unknown final boss Lvl gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
			
			case 19 : //check final boss HP format validity
				if(sscanf(CKata.c,"HP = %d",&a)!=1)
				{
					error = true;
					printf("X-files : Unknown final boss HP gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 20 : //check final boss strength format validity
				if(sscanf(CKata.c,"Str = %d",&a)!=1)
				{
					error = true;
					printf("X-files : Unknown final boss Str gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 21 : //check final boss defense format validity
				if(sscanf(CKata.c,"Def = %d",&a)!=1)
				{
					error = true;
					printf("X-files : Unknown final boss Def gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 22 : //check final boss total flank format validity
				if(sscanf(CKata.c,"Total_F = %d",&a)!=1)
				{
					error = true;
					printf("X-files : Unknown final boss Total_F gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 23 : //check final boss total attack format validity
				if(sscanf(CKata.c,"Total_A = %d",&a)!=1)
				{
					error = true;
					printf("X-files : Unknown final boss Total_A gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 24 : //check final boss total block format validity
				if(sscanf(CKata.c,"Total_B = %d",&a)!=1)
				{
					error = true;
					printf("X-files : Unknown final boss Total_B gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 25 : //check map gameasset validity
				String_CreateFromCStr(&s,"[Map]");
				String_CreateFromCStr(&in,CKata.c);
				
				if(!String_IsEqual(&in,&s))
				{
					error = true;
					printf("X-files : Unknown map gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 26 : //check graph format validity
				String_CreateFromCStr(&s,"Graph :");
				String_CreateFromCStr(&in,CKata.c);
				
				if(!String_IsEqual(&in,&s))
				{
					error = true;
					printf("X-files : Unknown graph gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 27 : //check graph connection format validity
				line = 6;
				
				while(!EndKata && line--)
				{
					if(sscanf(CKata.c,"%d%c %d%c %d%c %d%c",&a,&v,&b,&x,&c,&y,&d,&z)==8)
					{
						if(!(((a>=1 && a<=6 && v=='L') || (a==0 && v=='N')) && ((b>=1 && b<=6 && x=='U') || (b==0 && x=='N')) && ((c>=1 && c<=6 && y=='R') || (c==0 && y=='N')) && ((d>=1 && d<=6 && z=='D') || (d==0 && z=='N'))))
						{
								error = true;
								printf("X-files : Unknown graph connection gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
						}
					}
					else
					{
						error = true;
						printf("X-files : Unknown graph connection gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
					}
					
					ADVKATA();
					lc++;
				}
				
				break;
				
			case 33 : //check area format validity
				String_CreateFromCStr(&s,"Area :");
				String_CreateFromCStr(&in,CKata.c);
				
				if(!String_IsEqual(&in,&s))
				{
					error = true;
					printf("X-files : Unknown area format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 34 : //check map detail format validity
				line = 12;
				
				while(!EndKata && line--)
				{
					if(sscanf(CKata.c,"%d",&a)!=1)
					{
						error = true;
						printf("X-files : Unknown area number gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
					}
					
					lc++;
					i = 24;
					
					ADVKATA();
					
					while(!EndKata && i--)
					{
						for(j=1;j<=80;j++)
						{
							z = CKata.c[j-1];
							
							if(!(z=='.' || z=='#'))
							{
								error = error || true;
								printf("X-files : Unknown area detail gameasset format in \"%s\", %d:%d.\n",gameasset_file,lc,j);
							}
						}
						
						ADVKATA();
						lc++;
					}
				}
				
			case 334 : //check win gameasset validity
				String_CreateFromCStr(&s,"[Win]");
				String_CreateFromCStr(&in,CKata.c);
				
				if(!String_IsEqual(&in,&s))
				{
					error = true;
					printf("X-files : Unknown win gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 336 : //check lose gameasset validity
				String_CreateFromCStr(&s,"[Lose]");
				String_CreateFromCStr(&in,CKata.c);
				
				if(!String_IsEqual(&in,&s))
				{
					error = true;
					printf("X-files : Unknown lose gameasset format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
				break;
				
			case 338 :
				if(CKata.len!=1 || CKata.c[0]!='@')
				{
					error = true;
					printf("X-files : Unknown END character format in \"%s\", line %d.\n",gameasset_file,lc);
				}
				
			default :
				break;
		}
		
		ADVKATA(); //read next line
		lc++; //add line counter
	}
	
	if(error) printf("Gameasset load failed.\n");
	
	return error;
}

void load_all_profile(Profile *profile,int *number_of_profile)
{
	is_load_gameasset = false;
	
	if(!check_error_profile())
	{
		int i; //iterator
		String s; //for string input
		
		for(i=0;i<CKata.len;i++) CKata.c[i]='\0'; //clear CKata
		CKata.len = 0; //initialization
		
		*number_of_profile = 0;
		
		STARTKATA(profile_file);
		
		while(!EndKata)
		{
			String_Create(&s);
			
			for(i=1;i<CKata.len-1;i++) String_AppendChar(&s,CKata.c[i]);
			
			(*number_of_profile)++;
			profile[*number_of_profile].Name = s;
			
			for(i=1;i<=46;i++) ADVKATA();
		}
		
		for(i=1;i<=(*number_of_profile);i++)
		{
			load_profile(&(profile[i]),profile[i].Name);
		}
	}
	else
	{
		endwin();
		exit(0);
	}
}