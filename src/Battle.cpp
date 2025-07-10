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
    while (!battleOver) {
        Game::currentState = GameState::BATTLE_MENU;
        while (Game::currentState == GameState::BATTLE_MENU) {
            Game::render(getPlayer(), getEnemy());
            Game::render();
            Game::handleInput();
        }
        if (Game::currentState == GameState::IN_GAME) {
            playerTurn();
            checkBattleStatus();
            Game::render(getPlayer(), getEnemy()); // Renderiza após a ação do jogador e verificação de status

            if (battleOver) { // Verifica se a batalha terminou após o turno do jogador
                if (whoWon == 1) {
                    cout << "Você venceu a batalha!" << endl;
                } else { // whoWon == 2
                    cout << "Você foi derrotado!" << endl;
                }
                pressSpaceToContinue();
                break; // Sai do loop de batalha
            }

            pressSpaceToContinue(); // Solicita para continuar antes do turno do inimigo (se a batalha não terminou)

            enemyTurn();
            checkBattleStatus();
            Game::render(getPlayer(), getEnemy()); // Renderiza após a ação do inimigo e verificação de status

            if (battleOver) { // Verifica se a batalha terminou após o turno do inimigo
                if (whoWon == 1) {
                    cout << "Você venceu a batalha!" << endl;
                } else { // whoWon == 2
                    cout << "Você foi derrotado!" << endl;
                }
                pressSpaceToContinue();
                break; // Sai do loop de batalha
            }
        }
    }
    // Após o loop de batalha terminar
    Game::isBattleOver = true; // Define a flag global
    Game::currentState = GameState::MAIN_MENU; // Retorna ao menu principal
};

void Battle::playerTurn() {
    player.action(Game::selectedOption, &enemy);
}

void Battle::enemyTurn() {
    enemy.autoAction(&player);
}

void Battle::checkBattleStatus() {
    if (enemy.getHp() <= 0) {
        setBattleOver();
        whoWon = 1; // Jogador venceu
    } else if (player.getHp() <= 0) {
        setBattleOver();
        whoWon = 2; // Inimigo venceu
    }
}
