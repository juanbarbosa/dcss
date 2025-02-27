#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


//Struct to contain the various values associated with a monster. 
//Each variable is one column in the CSV. Add variables to struct if you increase rows.
struct MonsterCV {
    int IDnumber;
    std::string MonsterName;
    int XPgranted;
    int MonsterHP;
    int SpriteCode;
    int CanHaveWeapon;
};

class Bestiary
{
public:
    std::vector<MonsterCV> myListOfMonsters; //Vector storing struct of Monster Stats (ID, name, hp, etc)
        
    Bestiary() {  //Constructor. Will build the bestiary on object creation.
        BestiaryBuilder();
    }


    void BestiaryBuilder()
    {

        std::ifstream myFile("../../data/BehelaBestiary.csv");
        if (!myFile.is_open()) {
            std::cerr << "Error opening file.\n";
            return;
        }
        std::cout << "File opened successfully!\n";

        std::string myLine;
        std::getline(myFile, myLine); // Skip header

        while (std::getline(myFile, myLine)) {

            //temp variable for storage
            std::stringstream myStream(myLine);
            MonsterCV myMonster;
            std::string myValue;


            //if you add row, add to this as well. Just copy one block and replace the variable from XPgranted to new row var
            std::getline(myStream, myValue, ',');
            myMonster.IDnumber = myValue.empty() ? 0 : std::stoi(myValue);

            std::getline(myStream, myMonster.MonsterName, ',');

            std::getline(myStream, myValue, ',');
            myMonster.XPgranted = myValue.empty() ? 0 : std::stoi(myValue);

            std::getline(myStream, myValue, ',');
            myMonster.MonsterHP = myValue.empty() ? 0 : std::stoi(myValue);

            std::getline(myStream, myValue, ',');
            myMonster.SpriteCode = myValue.empty() ? 0 : std::stoi(myValue);

            std::getline(myStream, myValue, ',');
            myMonster.CanHaveWeapon = myValue.empty() ? 0 : std::stoi(myValue);


            myListOfMonsters.push_back(myMonster);
        }

        myFile.close();
    }

    //Also needs to be increased when rows are added.
    void PrintBestiary() const {
        std::cout << "\n -- Dispaying full Bestiary -- \n";
        for (const auto& myMonster : myListOfMonsters) {
            PrintMonsterStats(myMonster);
        }
    }

    void PrintMonsterStats(const MonsterCV& myMonster) const
    {
        std::cout << "ID: " << myMonster.IDnumber
            << ", Name: [" << myMonster.MonsterName << "]"
            << ", XP: " << myMonster.XPgranted
            << ", HP: " << myMonster.MonsterHP
            << ", Sprite: " << myMonster.SpriteCode
            << ", CanHaveWeapon: " << myMonster.CanHaveWeapon
            << std::endl;
    }

};
