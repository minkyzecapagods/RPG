#ifndef BATTLEMENU_HPP
#define BATTLEMENU_HPP

#include "Character.hpp"

extern vector<string> battleMenuOptions;

void renderBattleMenu();
void renderBattleStatus(Character enemy, Character player);
void pressSpaceToContinue();
void handleBattleMenuInput();
void renderBattleStatus(Character *enemy, Character *player);






#endif