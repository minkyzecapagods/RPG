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

Battle::Battle(Character player, Character enemy){
    this->player = player;
    this->enemy = enemy;

    //USAR O CONSTRUCTOR, INICIA UMA BATALHA!
    while (!Game::isBattleOver) {
        Game::currentState = GameState::BATTLE_MENU;
        while (Game::currentState == GameState::BATTLE_MENU) {
            Game::render(this->player, this->enemy);
            Game::render();
            Game::handleInput();
        }
        if (Game::currentState == GameState::IN_GAME) {
            playerTurn();
            checkBattleStatus();
            Game::render(this->player, this->enemy);
            pressSpaceToContinue(); // Temporario
            enemyTurn();
            checkBattleStatus();
            Game::render(this->player, this->enemy);
        }
        if (battleOver) {
            Game::isBattleOver = true;
            Game::currentState = GameState::MAIN_MENU; // Volta ao menu principal após a batalha (temporário)
        }
    }
};

void Battle::playerTurn() {
    player.action(Game::selectedOption, &enemy);
}

void Battle::enemyTurn() {
    enemy.action(&player);
}

void Battle::checkBattleStatus() {
    if (enemy.getHp() <= 0) {
        setBattleOver();
        whoWon = 1; // Jogador venceu
        cout << "Você venceu a batalha!" << endl;
    } else if (player.getHp() <= 0) {
        setBattleOver();
        whoWon = 2; // Inimigo venceu
        cout << "Você foi derrotado!" << endl;
    }
}
