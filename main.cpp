#include <iostream>
#include <string>
#include <vector>

#include "ArrowKey.hpp"
#include "GameState.hpp"
#include "include/Character.hpp"

using namespace std;

int main() {
    initKeyboard();
    cout << "\033[8;100;60t";
    
    while (Game::currentState != GameState::EXIT) {
        Game::render();
        Game::handleInput();
        if (Game::currentState == GameState::INITIALIZE_BATTLE) {
            Game::isBattleOver = false;
            Battle(Character("player"), Character("enemy")); // Inicia uma batalha com um personagem jogador e um inimigo
            Game::isBattleOver = false; // Reseta o estado da batalha
        }
    }

    restoreKeyboard(); // restaurar de forma segura no fim
    cout << "Saindo do jogo...\n";
    return 0;
}
