#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <game/io/Io.h>
#include <game/util/Graph.h>

Profile profiles[51]; //array of profiles
int profile_cnt = 0; //profile counter
int profile_index = 0; //index for profile search if found

Profile *all_profile = profiles; //pointer to array of profiles

String hehe;
char input[100];
char ans;

GameAsset gameassets; //GameAsset

int i,j,k; //iterator

void segfault_handler()
/* I.S. ada signal segfault */
/* F.S signal segfault terhandle */
{
	printf("Received segmentation fault, program terminated.\n");
	exit(0);
}

void stat_changer(Profile * self)
{
	int val;
	int a,b,c,d,e,f;
	char temp[100];
	
	printf("Lvl = ");
	scanf("%s",temp);
	if(sscanf(temp,"%d",&val)==1) (*self).Lvl = val;

	printf("HP = ");
	scanf("%s",temp);
	if(sscanf(temp,"%d",&val)==1) (*self).HP = val;

	printf("Str = ");
	scanf("%s",temp);
	if(sscanf(temp,"%d",&val)==1) (*self).Str = val;
	
	printf("Def = ");
	scanf("%s",temp);
	if(sscanf(temp,"%d",&val)==1) (*self).Def = val;
	
	printf("Exp = ");
	scanf("%s",temp);
	if(sscanf(temp,"%d",&val)==1) (*self).Exp = val;
	
	printf("map_ids = ");
	scanf("%c",&ans); //read \n from previous input
	fgets(temp,sizeof(temp),stdin);
	if(sscanf(temp,"%d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)==6)
	{
		(*self).map_ids[1] = a;
		(*self).map_ids[2] = b;
		(*self).map_ids[3] = c;
		(*self).map_ids[4] = d;
		(*self).map_ids[5] = e;
		(*self).map_ids[6] = f;
	}
	
	printf("loc_map_id = ");
	scanf("%s",temp);
	if(sscanf(temp,"%d",&val)==1) (*self).loc_map_id = val;
	
	printf("loc_point.x = ");
	scanf("%s",temp);
	if(sscanf(temp,"%d",&val)==1) Absis((*self).loc_point) = val;
	
	printf("loc_point.y = ");
	scanf("%s",temp);
	if(sscanf(temp,"%d",&val)==1) Ordinat((*self).loc_point) = val;
	
	printf("skill_ids = ");
	scanf("%s",temp);
	if(sscanf(temp,"%d",&val)==1)
	{
		for(i=0;i<16;i++) //load 16 skills
		{
			if((val & (1 << i)) != 0) (*self).skill_ids[i+1] = true; //if (i+1)th skill acquired by player
		}
	}
	
	printf("\n");
}

bool is_profile_exist(String test_name,int *idx) // check if profile with profile name test_name exists
{
	for(i=1;i<=profile_cnt;i++)
	{
		if(String_IsEqual(&test_name,&profiles[i].Name)) //return index if found
		{
			*idx = i;
			return true;
		}
	}
	
	return false;
}

int main()
{
	//Register external file segfault and signal handler
	signal(SIGSEGV,no_end_character);
	/*
	GameAsset_Create(&gameassets);
	load_gameasset(&gameassets);
	load_enemymoves(&gameassets);
	
	printf("Area :\n");
	
	//Test print gameasset
	for(int k=1;k<=12;k++)
	{
		printf("%d\n",k);
		
		for(i=1;i<=24;i++)
		{
			for(j=1;j<=80;j++)
			{
				printf("%c",Matrix_Elmt(gameassets.WholeMap.Area[k],i,j));
			}
			
			printf("\n");
		}
	}
	
	printf("\nMap Connection :");
	PrintGraph(gameassets.WholeMap.AllAreaCombine);
	
	printf("Player :\n");
	printf("Lvl : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Player.idP[i].Lvl);
		else printf("%d ",gameassets.Player.idP[i].Lvl);
	}
	
	printf("HP : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Player.idP[i].HP);
		else printf("%d ",gameassets.Player.idP[i].HP);
	}
	
	printf("Str : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Player.idP[i].Str);
		else printf("%d ",gameassets.Player.idP[i].Str);
	}
	
	printf("Def : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Player.idP[i].Def);
		else printf("%d ",gameassets.Player.idP[i].Def);
	}
	
	printf("EXP : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Player.EXP[i]);
		else printf("%d ",gameassets.Player.EXP[i]);
	}
	
	printf("\nEnemy :\n");
	
	printf("Name : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%s\n",gameassets.Enemy[i].Name);
		else printf("%s ",gameassets.Enemy[i].Name);
	}
	
	printf("Lvl : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Enemy[i].idE.Lvl);
		else printf("%d ",gameassets.Enemy[i].idE.Lvl);
	}
	
	printf("HP : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Enemy[i].idE.HP);
		else printf("%d ",gameassets.Enemy[i].idE.HP);
	}
	
	printf("Str : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Enemy[i].idE.Str);
		else printf("%d ",gameassets.Enemy[i].idE.Str);
	}
	
	printf("Def : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Enemy[i].idE.Def);
		else printf("%d ",gameassets.Enemy[i].idE.Def);
	}
	
	printf("Total_F : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Enemy[i].Total_F);
		else printf("%d ",gameassets.Enemy[i].Total_F);
	}
	
	printf("Total_A : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Enemy[i].Total_A);
		else printf("%d ",gameassets.Enemy[i].Total_A);
	}
	
	printf("Total_B : ");
	
	for(i=1;i<=6;i++)
	{
		if(i==6) printf("%d\n",gameassets.Enemy[i].Total_B);
		else printf("%d ",gameassets.Enemy[i].Total_B);
	}
	
	printf("\nFinalBoss :\n");
	
	printf("Name : ");
	printf("%s\n",gameassets.FinalBoss.Name);
	
	printf("Lvl : ");
	printf("%d\n",gameassets.FinalBoss.idE.Lvl);
	
	printf("HP : ");
	printf("%d\n",gameassets.FinalBoss.idE.HP);
	
	printf("Str : ");
	printf("%d\n",gameassets.FinalBoss.idE.Str);
	
	printf("Def : ");
	printf("%d\n",gameassets.FinalBoss.idE.Def);
	
	printf("Total_F : ");
	printf("%d\n",gameassets.FinalBoss.Total_F);
	
	printf("Total_A : ");
	printf("%d\n",gameassets.FinalBoss.Total_A);
	
	printf("Total_B : ");
	printf("%d\n",gameassets.FinalBoss.Total_B);
	
	printf("Win : %s\n",gameassets.Win);
	printf("Lose : %s\n",gameassets.Lose);
	printf("Credit : %s\n",gameassets.Credit);
	
	
	//New profile / existing profile
	while(1)
	{
		printf("\nEnter profile name : ");
		scanf("%s",input);
		
		String_CreateFromCStr(&hehe,input);
		
		if(!is_profile_exist(hehe,&profile_index)) //if profile does not exist create new profile
		{
			profile_cnt++;
			profile_create(&profiles[profile_cnt]);
			
			String_Create(&profiles[profile_cnt].Name);
			String_Append(&profiles[profile_cnt].Name,&hehe);
			
			profile_index = profile_cnt;
		}
		else
		{
			scanf("%c",&ans); //read \n form previous input
			
			printf("Want to change stats? ");
			scanf("%c",&ans);
			
			if(ans=='y' || ans=='Y')
			{
				stat_changer(&profiles[profile_index]);
			}
		}
		
	    save_profile(all_profile,profile_cnt,profile_index);
		load_profile(&profiles[profile_index],profiles[profile_index].Name);
		*/
		
		load_all_profile(all_profile,&profile_cnt);
		
		//Register general segfault and signal handler
		signal(SIGSEGV,segfault_handler);
		
		for(k=1;k<=profile_cnt;k++)
		{
			profile_index = k;
			
			printf("Name : ");
			
			for(i=0;i<profiles[profile_index].Name.len;i++)
			{
				printf("%c",profiles[profile_index].Name.buf[i]);
			}
			
			printf("\n");
			
			printf("Lvl : %d\n",profiles[profile_index].Lvl);
			printf("HP : %d\n",profiles[profile_index].HP);
			printf("Str : %d\n",profiles[profile_index].Str);
			printf("Def : %d\n",profiles[profile_index].Def);
			printf("Exp : %d\n",profiles[profile_index].Exp);
			
			printf("map_ids : ");
			
			for(i=1;i<=6;i++)
			{
				if(i!=6) printf("%d ",profiles[profile_index].map_ids[i]);
				else printf("%d\n",profiles[profile_index].map_ids[i]);
			}
			
			printf("loc_map_id : %d\n",profiles[profile_index].loc_map_id);
			printf("loc_point.x : %d\n",Absis(profiles[profile_index].loc_point));
			printf("loc_point.y : %d\n",Ordinat(profiles[profile_index].loc_point));
			
			printf("skill_ids :");
			
			for(i=1;i<=15;i++)
			{
				if(profiles[profile_index].skill_ids[i]) printf(" %d",i);
			}
			
			printf("\n");
			
			for(i=1;i<=6;i++)
			{
				printf("%d\n",i);
				
				printf("loc_enemy.x =");
				
				for(j=1;j<=10;j++) printf(" %d",Absis(profiles[profile_index].loc_enemy[i][j]));
				printf("\n");
				
				printf("loc_enemy.y =");
				
				for(j=1;j<=10;j++) printf(" %d",Ordinat(profiles[profile_index].loc_enemy[i][j]));
				printf("\n");
				
				printf("loc_medicine.x =");
				
				for(j=1;j<=10;j++) printf(" %d",Absis(profiles[profile_index].loc_medicine[i][j]));
				printf("\n");
				
				printf("loc_medicine.y =");
				
				for(j=1;j<=10;j++) printf(" %d",Ordinat(profiles[profile_index].loc_medicine[i][j]));
				printf("\n");
			}
			
			printf("Hour : %d\n",Hour(profiles[profile_index].save_time));
			printf("Minute : %d\n",Minute(profiles[profile_index].save_time));
			printf("Second : %d\n",Second(profiles[profile_index].save_time));
			
			String_Eject(&hehe);
			
			printf("\n");
			/*
			scanf("%c",&ans); //read \n form previous input
			
			printf("\nDo you want to continue ? ");
			scanf("%c",&ans);
			
			if(ans=='y' || ans=='Y')
			{
				printf("Continuing...\n\n");
			}
			else
			{
				printf("Program terminated.\n");
				break;
			}*/
		}
	//}
	
    return 0;
}
