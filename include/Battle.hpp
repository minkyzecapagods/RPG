#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "Character.hpp"

void renderBattleMenu();
void renderBattleStatus(Character *player, Character *enemy);
bool handleBattleMenuInput();
int advanceBattleLogic(Character *player, Character *enemy);
void pressSpaceToContinue();

#endif