#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "entities/Character.hpp"
#include "entities/Enemy.hpp"

class Battle {
    private:
        bool battleOver = false;
        int whoWon = 0; // 0 = Ninguém, 1 = Jogador, 2 = Inimigo
        bool havePlayerDefended = false;
        bool haveEnemyDefended = false;
        int playerAction;
        int enemyAction;
        
    public:
        Character* player;
        Enemy enemy;
        Battle(Character* player, Enemy enemy);
        void playerTurn();
        void enemyTurn();
        void checkBattleStatus();

        void setBattleOver() { battleOver = true; }
        Character& getPlayer() { return *player; }
        Enemy getEnemy() { return enemy; }
};

#endif