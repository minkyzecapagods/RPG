#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "Battle.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"
#include "Character.hpp"
#include "utils.hpp"
#include "BattleMenu.hpp"
#include "Enemy.hpp"

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

Battle::Battle(Character player, Enemy enemy){
    this->player = player;
    this->enemy = enemy;

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
                announceAction(player.getName(), playerAction);
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
            Game::isBattleOver = true;
            Game::currentState = GameState::MAIN_MENU; // Volta ao menu principal após a batalha (temporário)
        }
    }
};

void Battle::playerTurn() {
    this->playerAction = player.action(Game::selectedOption, &enemy, havePlayerDefended, haveEnemyDefended);
    if(playerAction == 1) {
        this->havePlayerDefended = true;
    }
    else {
        this->havePlayerDefended = false;
    }
}

void Battle::enemyTurn() {
    this->enemyAction = enemy.autoAction(&player, havePlayerDefended, haveEnemyDefended);
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
        cout << "Você venceu a batalha!" << endl;
        pressSpaceToContinue(); // Temporario
    } else if (player.getHp() <= 0) {
        this->setBattleOver();
        whoWon = 2; // Inimigo venceu
        cout << "Você foi derrotado!" << endl;
        pressSpaceToContinue(); // Temporario
    }
}
