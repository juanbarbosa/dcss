#include <string>			
#include <iostream>		

#include "Bestiary.h"	
#include "Achievements.h"
#include "Player.h"
#include "Monster.h"

int main()
{
	const Bestiary GameBestiary;


	PlayerChar mainPlayer("Big Joe", GameBestiary);
	Monster gobbo(GameBestiary, 0);
	Monster gobbo2(GameBestiary, 0);

	GameBestiary.PrintBestiary();

	mainPlayer.DisplayAchievements();
	mainPlayer.DisplayStats();
	gobbo.DisplayStats();

	mainPlayer.AttackMonster(gobbo, 1);
	mainPlayer.AttackMonster(gobbo, 1);
	mainPlayer.AttackMonster(gobbo, 3);

	mainPlayer.AttackMonster(gobbo2, 5);
}
