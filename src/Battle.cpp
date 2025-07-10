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
            announceAction(player.getName(), playerAction);

            if (battleOver) { // Verifica se a batalha terminou após o turno do jogador
                if (whoWon == 1) {
                    cout << "Você venceu a batalha!" << endl;
                    if (static_cast<size_t>(Game::currentEnemyIndex) >= Game::getTotalEnemies()) {
                        cout << "Parabéns! Você derrotou todos os inimigos!" << endl;
                    }
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
            announceAction(enemy.getName(), enemyAction);
            

            if (battleOver) { // Verifica se a batalha terminou após o turno do inimigo
                if (whoWon == 1) {
                    cout << "Você venceu a batalha!" << endl;
                    if (static_cast<size_t>(Game::currentEnemyIndex) >= Game::getTotalEnemies()) {
                        cout << "Parabéns! Você derrotou todos os inimigos!" << endl;
                    }
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
    if (whoWon == 1) {
        if (static_cast<size_t>(Game::currentEnemyIndex) < Game::getTotalEnemies()) {
            Game::currentState = GameState::INITIALIZE_BATTLE; // Inicia a próxima batalha
        } else {
            Game::currentState = GameState::MAIN_MENU; // Todos os inimigos derrotados, volta ao menu principal
        }
    } else { // whoWon == 2 (jogador perdeu)
        Game::currentState = GameState::MAIN_MENU; // Volta ao menu principal
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
        Game::currentEnemyIndex++; // Incrementa o índice do inimigo
    } else if (player.getHp() <= 0) {
        this->setBattleOver();
        whoWon = 2; // Inimigo venceu
    }
}
