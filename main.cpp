#include <iostream>
#include <string>
#include <vector>

#include "ArrowKey.hpp"
#include "GameState.hpp"

using namespace std;

int main() {
    initKeyboard();
    cout << "\033[8;100;60t";
    
    while (Game::currentState != GameState::EXIT) {
        Game::render();
        Game::handleInput();
        if (Game::currentState == GameState::INITIALIZE_BATTLE) {
            Game::isBattleOver = false;
            Game::startBattle();
            Game::isBattleOver = false; // Reseta o estado da batalha
        }
    }

    restoreKeyboard(); // restaurar de forma segura no fim
    cout << "Saindo do jogo...\n";
    return 0;
}
