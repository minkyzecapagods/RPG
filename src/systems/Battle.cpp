#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "systems/Battle.hpp"
#include "core/GameState.hpp"
#include "core/ArrowKey.hpp"
#include "entities/Character.hpp"
#include "helpers/utils.hpp"
#include "menus/BattleMenu.hpp"
#include "entities/Enemy.hpp"

using namespace std;

//teste
vector<string> n = {
"              _,-'|",
"           ,-'._  |",
" .||,      |####\\ |",
"\\.`',/     \\####| |",
"= ,. =      |###| |",
"/ || \\    ,-'\\#/,'`.",
"  ||     ,'   `,,. `.",
"  ,|____,' , ,;' \\| |",
" (3|\\    _/|/'   _| |",
"  ||/,-''  | >-'' _,\\",
"  ||'      ==\\ ,-'  ,'",
"  ||       |  V \\ ,|",
"  ||       |    |` |",
"  ||       |    |   \\",
"  ||       |    \\    \\",
"  ||       |     |    \\",
"  ||       |      \\_,-'",
"  ||       |___,,--')_\\",
"  ||         |_|   ccc/",
"  ||        ccc/",
"  ||"};

Battle::Battle(Character* player, Enemy enemy){
    this->player = player;
    this->enemy = enemy;
    // Vida cheia no início da batalha
    this->player->setHp(this->player->getMaxHp());
    this->enemy.setHp(this->enemy.getMaxHp());
    
    //USAR O CONSTRUCTOR, INICIA UMA BATALHA!
    while (!Game::isBattleOver) {
        Game::currentState = GameState::BATTLE_MENU;
        while (Game::currentState == GameState::BATTLE_MENU) {
            Game::render(getPlayer(), getEnemy());
            Game::render();
            Game::handleInput();
        }
        if (Game::currentState == GameState::IN_GAME) {
            if(!this->battleOver){
                playerTurn();
                Game::render(getPlayer(), getEnemy());
                announceAction(player->getName(), playerAction);
                checkBattleStatus();
            }
            
            if(!this->battleOver){
                enemyTurn();
                Game::render(getPlayer(), getEnemy());
                announceAction(enemy.getName(), enemyAction);
                checkBattleStatus();
            }
        }
        
        if (battleOver) {
            Game::isBattleOver = true; // Define a flag global
            if (whoWon == 1) {
                if (static_cast<size_t>(Game::currentEnemyIndex) < Game::getTotalEnemies()) {
                    Game::currentState = GameState::GAME_MENU; // Retorna ao menu do jogo
                } else {
                    Game::currentState = GameState::MAIN_MENU; // Todos os inimigos derrotados, volta ao menu principal
                }
            } else { // whoWon == 2 (jogador perdeu)
                Game::currentState = GameState::MAIN_MENU; // Volta ao menu principal
            }
        }
    }
};

void Battle::playerTurn() {
    if(Game::selectedOption == 3)
    {
        this->setBattleOver();
        this->playerAction = 3; // Jogador fugiu
        whoWon = 2; // Jogador fugiu, logo o inimigo venceu
        return; // Sai da função se o jogador fugiu
    }
    this->playerAction = player->action(Game::selectedOption, &enemy, havePlayerDefended, haveEnemyDefended);
    if(playerAction == 1) {
        this->havePlayerDefended = true;
    }
    else {
        this->havePlayerDefended = false;
    }
}

void Battle::enemyTurn() {
    this->enemyAction = enemy.autoAction(player, havePlayerDefended, haveEnemyDefended);
    if(enemyAction == 1) {
        this->haveEnemyDefended = true;
    }
    else {
        this->haveEnemyDefended = false;
    }
}


void Battle::checkBattleStatus() {
    if (enemy.getHp() <= 0) {
        this->setBattleOver();
        whoWon = 1; // Jogador venceu
        Game::currentEnemyIndex++; // Incrementa o índice do inimigo
    } else if (player->getHp() <= 0) {
        this->setBattleOver();
        whoWon = 2; // Inimigo venceu
    }
}
