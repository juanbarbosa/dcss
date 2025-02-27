#include "Monster.h"
#include "Player.h" 

//import bestiary ref and create the monster according to its ID.
//TODO: Make it possible to use monster name instead of ID for clarity.
Monster::Monster(const Bestiary& BestiaryArg, int monsterID)
    : refToBestiary(BestiaryArg) 
{
    if (monsterID < 0 || monsterID >= BestiaryArg.myListOfMonsters.size()) {
        throw std::out_of_range("Invalid monster ID!");
    }

    MonsterStats = BestiaryArg.myListOfMonsters[monsterID]; //Initialize monsters stats according to ID
}

//used by player to dmg the monster.
void Monster::getDamaged(int damageArg, PlayerChar& damageInflicter)
{
    MonsterStats.MonsterHP -= damageArg;
    std::cout << "\nMonster took " << damageArg
        << " damage from "
        << damageInflicter.myCharName
        << "! \nRemaining HP : " << MonsterStats.MonsterHP << std::endl;

    if (MonsterStats.MonsterHP <= 0)
    {
        MonDeath(damageInflicter);
    }
}


void Monster::MonDeath(PlayerChar& playerArg)
{
    if(taggedByPlayer = true)
    {
        std::cout << "\n" << MonsterStats.MonsterName << " Died." << std::endl;
        playerArg.GetAchievement(MonsterStats.IDnumber); // gives xp to player on monster death
    }

    //delete monster or convert it to something else here.
}

void Monster::DisplayStats()
{
    refToBestiary.PrintMonsterStats(MonsterStats);
}