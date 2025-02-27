#pragma once

#include "bestiary.h"
#include <vector>

struct AchievementEntry {
    int IDnumber;
    int XPgranted;
    int Completed;  // Starts at 0
};

class Achievements {
public:
    std::vector<AchievementEntry> myAchievementList; //Vector holding achievement entries (ID, XP, Completedness)

    int TotalPossibleXP;
    int CurrentXP;

    //take a bestiary class and extract every monsters' ID and grantedXP on defeat.
    Achievements(const Bestiary& bestiaryArg) {
        for (const auto& myMonster : bestiaryArg.myListOfMonsters) {
            myAchievementList.push_back({ myMonster.IDnumber, myMonster.XPgranted, 0 });
        }
        maximumXPCheck(); //Check Sets max xp.
    }


    void PrintAchievements() const {  //print function for debugging purpose
        
        std::cout << "\n- Displaying player achievement list -\n";

        for (const auto& myCheevos : myAchievementList) {
            std::cout   << "ID: " << myCheevos.IDnumber
                        << ", XP: " << myCheevos.XPgranted
                        << ", Completed: " << myCheevos.Completed << std::endl;
        }
        std::cout << "\n";
    }


    void currentXPCheck() //call this function to update current XP.
    {    
        int xpSUM = 0;
        for (const auto& myCheevos : myAchievementList) {
            if (myCheevos.Completed == 1) {
                xpSUM += myCheevos.XPgranted;
            }
        }
        CurrentXP = xpSUM;
    }
    

private:
    //Check maximum possible XP according to current bestiary. Mostly useful for game design.
    void maximumXPCheck() {
        int MAXxpSUM = 0;
        for (const auto& myCheevos : myAchievementList) {
            MAXxpSUM += myCheevos.XPgranted;
        }
        TotalPossibleXP = MAXxpSUM;
    }
};