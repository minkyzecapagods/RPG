#include <iostream>
#include <string>
#include <vector>

#include "core/ArrowKey.hpp"
#include "core/GameState.hpp"
#include "entities/Character.hpp"
#include "helpers/utils.hpp"
#include "entities/Enemy.hpp"
#include "systems/Save.hpp"
#include "systems/ItemRegistry.hpp"

using namespace std;

int main() {
    cout << normalText; // Modo de texto dentro do jogo (fundo preto, texto branco)
    initKeyboard();
    items.loadItemsFromFile(); // Carrega todos os itens do jogo
    //items.unlockAllItems(); // DEBUG: desbloqueia todos os itens para teste
    loadFromFile(); // Carrega os saves do jogo
    while (Game::currentState != GameState::EXIT) {
        adjustWindow();
        
        Game::render();
        Game::handleInput();
        if (Game::currentState == GameState::INITIALIZE_BATTLE) {
            Game::isBattleOver = false;
            Battle(&Game::player, Game::getEnemyByIndex(Game::currentEnemyIndex)); // Inicia uma batalha com o personagem ativo e o inimigo atual
            Game::isBattleOver = false; // Reseta o estado da batalha
        }
    }

    restoreKeyboard(); // restaurar de forma segura no fim 
    system(CLEAR_COMMAND);
    cout << "Saindo do jogo...\n" << "\033[0;0m"; // mensagem junto ao retorno das cores normais do terminal
    return 0;
}