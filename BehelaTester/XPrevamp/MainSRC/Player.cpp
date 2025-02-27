#include "Player.h"
#include "Monster.h" // Now we can include Monster since implementation happens in .cpp
#include <string>

//Achievement lists need a bestiary class to build itself.
//This allows player to receive that bestiary class as an argument and pass it onto the achievement list. 
//refToBestiary also saves the reference to the bestiary.
PlayerChar::PlayerChar(const std::string& name, const Bestiary& BestiaryArg)
    : Cheevos(BestiaryArg), refToBestiary(BestiaryArg) 
{
    myCharName = name;
    //add a load function here BEFORE xp update.
    xpUpdate(); //defines current xp according to cheevos list on creation.
}


//used by monster on death to give xp
void PlayerChar::GetAchievement(int achievementID)
{
    if (Cheevos.myAchievementList[achievementID].Completed != 1)
    {
        Cheevos.myAchievementList[achievementID].Completed = 1;
        std::cout << "\nFirst time killing a " 
            << refToBestiary.myListOfMonsters[achievementID].MonsterName
            << " You get "
            << refToBestiary.myListOfMonsters[achievementID].XPgranted
            << " xp points! \n";

        xpUpdate();  //update your xp score.
    }
    else
    {
        std::cout << "\n You killed this monster before, no xp.";
    }

}

//used to dmg monsters.
//TODO: overload function to allow different targets.
void PlayerChar::AttackMonster(Monster& target, int damage) 
{
    if (target.MonsterStats.MonsterHP > 0)
    {
     std::cout << "Player attacks monster for " << damage 
         << " damage!" << std::endl;

        target.getDamaged(damage, *this);
    }
    else
    {
        std::cout << "\n Can't attack this target !";
    }
   
}


//refresh player XP. Use it on achievement get.
void PlayerChar::xpUpdate()
{
	Cheevos.currentXPCheck();
	myXP = Cheevos.CurrentXP;
}

void PlayerChar::DisplayAchievements()
{
    Cheevos.PrintAchievements();
}

void PlayerChar::DisplayStats()
{
    std::cout << "-- Displaying Player Stats -- " << "\n";

    std::cout << "player name is : " << myCharName << "\n";
    std::cout << "current xp is : " << myXP << "\n";
}