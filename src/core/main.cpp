#include <iostream>
#include <string>
#include <vector>

#include "core/ArrowKey.hpp"
#include "core/GameState.hpp"
#include "entities/Character.hpp"
#include "helpers/utils.hpp"
#include "entities/Enemy.hpp"
#include "systems/Save.hpp"


using namespace std;

int main() {
    cout << normalText; // Modo de texto dentro do jogo (fundo preto, texto branco)
    initKeyboard();
    loadFromFile(); // Carrega os saves do jogo
    
    while (Game::currentState != GameState::EXIT) {
        adjustWindow();

        Game::render();
        Game::handleInput();
        if (Game::currentState == GameState::INITIALIZE_BATTLE) {
            Game::isBattleOver = false;
            Battle(Game::player, Enemy("enemy")); // Inicia uma batalha com um personagem jogador e um inimigo
            Game::isBattleOver = false; // Reseta o estado da batalha
        }
    }

    restoreKeyboard(); // restaurar de forma segura no fim 
    system(CLEAR_COMMAND);
    cout << "Saindo do jogo...\n" << "\033[0;0m"; // mensagem junto ao retorno das cores normais do terminal
    return 0;
}