#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "Character.hpp"
#include "Enemy.hpp"

class Battle{
    private:
        bool battleOver = false;
        int whoWon = 0; // 0 = Ninguém, 1 = Jogador, 2 = Inimigo
        bool havePlayerDefended = false;
        bool haveEnemyDefended = false;
        int playerAction;
        int enemyAction;
        //a informação whoWon vai ser utilizada pra saber se precisamos tirar um item do player
        //ou dar um item pra ele!

        //talvez possamos criar uma outra variavel privada que vai ser o item que foi dado ou retirado
        //de uma forma em que a classe "leia" o item do inimigo, e salve essa informação
        //para que o player possa pegar o item depois da batalha, ou perder o item se
        //ele perder a batalha.
        
    public:
        Character player;
        Enemy enemy;
        Battle(Character player, Enemy enemy);
        void playerTurn();
        void enemyTurn();
        void checkBattleStatus();

        bool getBattleOver() { return battleOver; }
        void setBattleOver() { battleOver = true; }
        Character getPlayer() { return player; }
        Character getEnemy() { return enemy; }
};

#endif