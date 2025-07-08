#include <iostream>
#include <string>
#include <vector>

#include "ArrowKey.hpp"
#include "GameState.hpp"
#include "include/Character.hpp"
#include "utils.hpp"


using namespace std;

int main() {
    cout << normalText; // Modo de texto dentro do jogo (fundo preto, texto branco)
    initKeyboard();
    
    while (Game::currentState != GameState::EXIT) {
        adjustWindow();

        Game::render();
        Game::handleInput();
        if (Game::currentState == GameState::INITIALIZE_BATTLE) {
            Game::isBattleOver = false;
            Battle(Character("player"), Character("enemy")); // Inicia uma batalha com um personagem jogador e um inimigo
            Game::isBattleOver = false; // Reseta o estado da batalha
        }
    }

    restoreKeyboard(); // restaurar de forma segura no fim 
    system(CLEAR_COMMAND);
    cout << "Saindo do jogo...\n" << "\033[0;0m"; // mensagem junto ao retorno das cores normais do terminal
    return 0;
}