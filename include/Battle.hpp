#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "Character.hpp"

class Battle{
    private:
        int battleState;
    public:
        Character player;
        Character enemy;
        Battle(Character player, Character enemy);
        vector<string> battleMenuOptions = {
        "Atacar",
        "Defender",
        "Curar"
        };
        size_t selectedOptionBattle = 0;
        void renderBattleMenu();
        void renderBattleStatus();
        bool handleBattleMenuInput();
        int advanceBattleLogic();
        void pressSpaceToContinue();
};

#endif