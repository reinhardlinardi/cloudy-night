//
//  Skill.h
//  


#pragma once

#include "Profile.h"
#include "Tree.h"
#include "util/List.h"

List Skill_Available (Profile * prof);

/* Perhitungan Skill */


/* Perhitungan Skill */

// Nomor masih bisa berubah
void Battle_SkillBagbiting (Profile * prof); // 1
// HP Player naik 10

void Battle_SkillDaemon (Profile * prof); // 2
// Strength Player naik 10

void Battle_SkillFirewall (Profile * prof); // 3
// Defense Player naik 10

void Battle_SkillFoo (Profile * prof); // 4
// Strength Player naik 20

void Battle_SkillJock (Profile * prof) ; // 5
// HP Player naik 20

void Battle_SkillPseudoprime (Profile * prof); // 6
// Exp Player naik 5

void Battle_SkillShield (Profile * prof); // 7
// Defense Player naik 20

void Battle_SkillQuux (Profile * prof); // 8
// Strength Player naik 30

void Battle_SkillYuShiangWholeFish (Profile * prof); // 9
// HP Player naik 30

void Battle_SkillInfinite (Profile * prof); // 10
// Strength Player naik 40

void Battle_SkillSabotage (Profile * prof); // 11
// Exp Player naik 10

void Battle_SkillTrojan (Profile * prof); // 12
// Defense Player naik 40

void Battle_SkillGlitch (Profile * prof); // 13
// HP Player naik 40

void Battle_SkillAOS (Profile * prof); // 14
// Exp Player naik 15

void Battle_SkillSuperProgrammer(Profile * prof); // 15
// Defense Player naik 30
