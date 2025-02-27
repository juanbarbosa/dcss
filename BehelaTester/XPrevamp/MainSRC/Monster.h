#pragma once
#include <iostream>
#include "Bestiary.h"

class PlayerChar;

class Monster
{
public:
    Monster(const Bestiary& BestiaryArg, int monsterID);

    const Bestiary& refToBestiary;
    MonsterCV MonsterStats;

    void getDamaged(int damageArg, PlayerChar& damageInflicter);
    void MonDeath(PlayerChar& playerArg);
    void DisplayStats();

    bool taggedByPlayer = false;
};
