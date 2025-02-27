#pragma once
#include <iostream>
#include "Achievements.h"
#include "Bestiary.h" 

// Forward declaration of Monster (avoids circular includes)
class Monster;

class PlayerChar
{
public:
    PlayerChar(const std::string& name, const Bestiary& BestiaryArg);
    
    const Bestiary& refToBestiary; //gives character access to all monster data (names, hp etc)
    Achievements Cheevos; //gives an achievement list to character.

    int myXP;
    std::string myCharName;


    void GetAchievement(int achievementID);
    void AttackMonster(Monster& target, int damage);
    void xpUpdate();
    void DisplayAchievements();
    void DisplayStats();
};
    