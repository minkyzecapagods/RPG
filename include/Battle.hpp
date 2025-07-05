#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "Character.hpp"

class Battle{
    private:
        bool battleOver = false;
    public:
        Character player;
        Character enemy;
        Battle(Character player, Character enemy);
        void playerTurn();
        void enemyTurn();
        void checkBattleStatus();

        bool getBattleOver() { return battleOver; }
        void setBattleOver() { battleOver = true; }
        Character getPlayer() { return player; }
        Character getEnemy() { return enemy; }
};

#endif