#pragma once
#define _CRT_SECURE_NO_WARNINGS		
#include <fstream>
#include <iostream>
#include <string>
class PlayerChar;
#include "Achievements.h"

class CharSaver 
{
public:

	static void SaveWriter(PlayerChar& playerArg, std::string filename)
	{
		std::ofstream myFile(filename);  // Open the file

		if (!myFile.is_open()) {
			std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
			return;
		}
		else std::cout << "file save launched \n";

		myFile << "ID,XP Granted,Completed\n";


	}

};
