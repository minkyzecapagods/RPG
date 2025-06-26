#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "Character.hpp"

void renderBattleMenu();
void handleBattleStatus(Character player, Character enemy);
size_t handleBattleMenuInput();
int advanceBattleLogic(Character player, Character enemy);

#endif