//
//  Skill.c
//  

#include "Skill.h"
#include <stdio.h>

/* Perhitungan Skill */
List Skill_Available (Profile * prof) 
// Skill yang bisa dibuka 
{ 
    List L; 
    List_Create(&L,sizeof(int)); 
    BinTree P; 
    Generate_SkillTree(&P); 
    int i; 
    if(!prof->skill_ids[1])
    {
        ListElmt* elmt= ListElmt_Alloc(&L); 
        ListElmt_Val(elmt, int) = 1; 
        List_InsertFirst(&L,elmt);
   }
   else{
    for(i=1;i<=7;i++) 
    { 
        if( prof->skill_ids[i] ) 
        { 
            int a,b; 
            Child(P,i,&b,&a); 
            if(!prof->skill_ids[a] && a!=0) 
            { 
                //Insert Element Ke List 
                ListElmt* elmt= ListElmt_Alloc(&L); 
                ListElmt_Val(elmt, int) = a; 
                List_InsertFirst(&L,elmt); 
            }   
            if(!prof->skill_ids[b] && b!=0) 
            { 
            //Insert Element Ke List 
            ListElmt* elmt= ListElmt_Alloc(&L); 
            ListElmt_Val(elmt, int) = b; 
            List_InsertFirst(&L,elmt); 
            } 
        } 
    } 
    }
    return L; 
}

// Nomor masih bisa berubah
void Battle_SkillBagbiting (Profile * prof) // 1
// HP Player naik 10
{
    prof->HP += 10;
}
void Battle_SkillDaemon (Profile * prof) // 2
// Strength Player naik 10
{
    prof->Str += 10;
}
void Battle_SkillFirewall (Profile * prof) // 3
// Defense Player naik 10
{
    prof->Def += 10;
}
void Battle_SkillFoo (Profile * prof) // 4
// Strength Player naik 20
{
    prof->Str += 20;
}
void Battle_SkillJock (Profile * prof) // 5
// HP Player naik 20
{
    prof->HP += 20;
}
void Battle_SkillPseudoprime (Profile * prof) // 6
// Exp Player naik 5
{
    prof->Exp += 5;
}
void Battle_SkillShield (Profile * prof) // 7
// Defense Player naik 20
{
    prof->Def += 20;
}
void Battle_SkillQuux (Profile * prof) // 8
// Strength Player naik 30
{
    prof->Str += 30;
}
void Battle_SkillYuShiangWholeFish (Profile * prof) // 9
// HP Player naik 30
{
    prof->HP += 30;
}
void Battle_SkillInfinite (Profile * prof) // 10
// Strength Player naik 40
{
    prof->Str += 40;
}
void Battle_SkillSabotage (Profile * prof) // 11
// Exp Player naik 10
{
    prof->Exp += 8;
}
void Battle_SkillTrojan (Profile * prof) // 12
// Defense Player naik 40
{
    prof->Def += 40;
}
void Battle_SkillGlitch (Profile * prof) // 13
// HP Player naik 40
{
    prof->HP += 40;
}
void Battle_SkillAOS (Profile * prof) // 14
// Exp Player naik 15
{
    prof->Exp +=15;
}
void Battle_SkillSuperProgrammer(Profile * prof) // 15
// Defense Player naik 30
{
    prof->Def += 30;
}



/*void Battle_SkillPoison (Profile * prof); // 
// Exp Player naik 20
{
    prof->Exp +=20;
}*/

