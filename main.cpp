#include <iostream>
#include <string>
#include <vector>

#include "ArrowKey.hpp"
#include "GameState.hpp"
#include "utils.hpp"

using namespace std;

int main() {
    cout << normalText;
    initKeyboard();
    
    while (Game::currentState != GameState::EXIT) {
        adjustWindow();

        Game::render();
        Game::handleInput();
    }

    restoreKeyboard(); // restaurar de forma segura no fim
    cout << "Saindo do jogo...\n" << "\033[0;0m";
    return 0;
}