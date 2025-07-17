#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <unordered_map>

#include "systems/Battle.hpp"
#include "core/GameState.hpp"
#include "core/ArrowKey.hpp"
#include "entities/Character.hpp"
#include "helpers/utils.hpp"
#include "menus/BattleMenu.hpp"
#include "entities/Enemy.hpp"

using namespace std;

// Mapa global: nome do inimigo -> nome do item
std::unordered_map<std::string, std::string> enemyToItemDrop = {
    {"Goblin", "Espada"},
    {"Orc", "Amuleto"},
    {"Slime", "Armadura"}
};

Battle::Battle(Character* player, Enemy enemy){
    this->player = player;
    this->enemy = enemy;
    // Vida cheia no início da batalha
    this->player->setHp(this->player->getMaxHp());
    this->enemy.setHp(this->enemy.getMaxHp());
    
    //USAR O CONSTRUCTOR, INICIA UMA BATALHA!
    while (!Game::isBattleOver) {
        Game::currentState = GameState::BATTLE_MENU;
        while (Game::currentState == GameState::BATTLE_MENU) {
            Game::render(getPlayer(), getEnemy());
            Game::render();
            Game::handleInput();
        }
        if (Game::currentState == GameState::IN_GAME) {
            if(!this->battleOver){
                playerTurn();
                Game::render(getPlayer(), getEnemy());
                announceAction(player->getName(), playerAction);
                checkBattleStatus();
            }
            
            if(!this->battleOver){
                enemyTurn();
                Game::render(getPlayer(), getEnemy());
                announceAction(enemy.getName(), enemyAction);
                checkBattleStatus();
            }
        }
        
        if (battleOver) {
            Game::isBattleOver = true; // Define a flag global
            if (whoWon == 1) {
                if (static_cast<size_t>(Game::currentEnemyIndex) < Game::getTotalEnemies()) {
                    Game::currentState = GameState::GAME_MENU; // Retorna ao menu do jogo
                } else {
                    Game::currentState = GameState::MAIN_MENU; // Todos os inimigos derrotados, volta ao menu principal
                }
            } else { // whoWon == 2 (jogador perdeu)
                Game::currentState = GameState::MAIN_MENU; // Volta ao menu principal
            }
        }
    }
};

void Battle::playerTurn() {
    if(Game::selectedOption == 3)
    {
        this->setBattleOver();
        this->playerAction = 3; // Jogador fugiu
        whoWon = 2; // Jogador fugiu, logo o inimigo venceu
        return; // Sai da função se o jogador fugiu
    }
    this->playerAction = player->action(Game::selectedOption, &enemy, havePlayerDefended);
    if(playerAction == 1) {
        this->havePlayerDefended = true;
    }
    else {
        this->havePlayerDefended = false;
    }
}

void Battle::enemyTurn() {
    this->enemyAction = enemy.autoAction(player, haveEnemyDefended);
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
        // --- INÍCIO: Drop customizado de item ao derrotar inimigo ---
        std::string enemyName = enemy.getName();
        auto it = enemyToItemDrop.find(enemyName);
        if (it != enemyToItemDrop.end()) {
            int itemId = items.getIdByName(it->second);
            if (itemId != -1 && !items.isUnlocked(itemId)) {
                items.unlockItem(itemId);
                addSavedItensInfo(Game::currentSave.index);
                // Mensagem de item encontrado
                cout << "\n\n";
                centralPrint("Você encontrou um novo item: " + items.getItem(itemId).getName() + "!\n");
                centralPrint("Pressione Enter para continuar...");
                std::cin.ignore();
                std::cin.get();
            }
        }
        // --- FIM: Drop customizado ---
        Game::currentEnemyIndex++; // Incrementa o índice do inimigo
    } else if (player->getHp() <= 0) {
        this->setBattleOver();
        whoWon = 2; // Inimigo venceu
    }
}
