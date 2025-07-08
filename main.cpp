#include <iostream>
#include <string>
#include <vector>

#include "ArrowKey.hpp"
#include "GameState.hpp"
#include "utils.hpp"

using namespace std;

int main() {
    cout << normalText; // Modo de texto dentro do jogo (fundo preto, texto branco)
    initKeyboard();
    
    while (Game::currentState != GameState::EXIT) {
        adjustWindow();

        Game::render();
        Game::handleInput();
    }

    restoreKeyboard(); // restaurar de forma segura no fim 
    system(CLEAR_COMMAND);
    cout << "Saindo do jogo...\n" << "\033[0;0m"; // mensagem junto ao retorno das cores normais do terminal
    return 0;
}