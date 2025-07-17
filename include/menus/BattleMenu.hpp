#ifndef BATTLEMENU_HPP
#define BATTLEMENU_HPP

#include "entities/Character.hpp"
#include "entities/Enemy.hpp"

extern vector<string> battleMenuOptions;

void renderBattleMenu();
//void renderBattleStatus(Character enemy, Character player);
void pressSpaceToContinue();
void handleBattleMenuInput();
void renderBattleStatus(Character player, Enemy enemy);
void announceAction(string name, int action);





#endif