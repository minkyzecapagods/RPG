#include <iostream>

#include "core/GameState.hpp"
#include "menus/MainMenu.hpp"
#include "menus/SaveMenu.hpp"
#include "menus/CreateMenu.hpp"
#include "menus/CustomMenu.hpp"
#include "menus/BattleMenu.hpp"
#include "menus/GameMenu.hpp"
#include "menus/ItemsMenu.hpp"

#include "entities/Character.hpp"
#include "systems/Battle.hpp"

GameState Game::currentState = GameState::MAIN_MENU;
size_t Game::selectedOption = 0;
bool Game::isBattleActive = false;
bool Game::isBattleOver = false;
int Game::selectedHorizontal = 0;

Character Game::player;
Save Game::currentSave;
int Game::currentEnemyIndex = 0;

namespace {
    // Lista de inimigos pré-definidos
    const std::vector<Enemy> enemies = {
        Enemy("Goblin", 5, 15, 0),   // Nome, Defesa, Ataque, Magia
        Enemy("Orc", 10, 20, 0),
        Enemy("Slime", 2, 10, 0),
        Enemy("Dragon", 20, 30, 0)
    };
}

Enemy Game::getEnemyByIndex(int index) {
    if (index >= 0 && static_cast<size_t>(index) < enemies.size()) {
        return enemies[index];
    }
    // Retorna um inimigo padrão ou lança um erro se o índice for inválido
    return Enemy("Inimigo Desconhecido");
}

size_t Game::getTotalEnemies() {
    return enemies.size();
}

void Game::handleInput() {
    switch (Game::currentState) {
        case GameState::MAIN_MENU:
            handleMainMenuInput();
            break;
        case GameState::BATTLE_MENU:
            handleBattleMenuInput();
            break;
        case GameState::IN_GAME: {
            /*
            Character player("player");
            Character enemy("enemy");
            Battle currentBattle(player, enemy); //inicializando uma batalha com player e enemy
            int result;
            while(true){
                result = currentBattle.advanceBattleLogic();
                if(result == 1){
                    cout << "vitoria" << endl;
                    Game::currentState = GameState::MAIN_MENU;
                    break;
                }
                else if(result == 2){
                    cout << "derrota" << endl;
                    Game::currentState = GameState::MAIN_MENU;
                    break;
                }
            }
            */
            break;
        }
        case GameState::SAVE_MENU:
            handleSaveMenuInput();
            break;
        case GameState::CREATE_MENU_CHOICE:
            handleChoiceMenuInput();
            break;
        case GameState::CREATE_SAVE:
            handleCreateSaveInput();
            break;
        case GameState::GIVE_NAME:
            handleNameInput();
            break;
        case GameState::CREATE_CHARACTER:
            handleCharCreation();
            break;
        case GameState::GAME_MENU:
            handleGameMenuInput();
            break;
        case GameState::INVENTORY_MENU:
            handleItemsMenuInput();
            break;
        default: break;
    }
}

void Game::render() {
    if (Game::currentState != GameState::BATTLE_MENU) {system(CLEAR_COMMAND);} // Limpa a tela antes de renderizar
    switch (Game::currentState) {
        case GameState::MAIN_MENU:
            renderMainMenu();
            break;
        case GameState::SAVE_MENU:
            renderSaveMenu();
            break;
        case GameState::CREATE_MENU_CHOICE:
            renderCharacterChoice();
            break;
        case GameState::BATTLE_MENU:
            renderBattleMenu();
            break;
        case GameState::CREATE_SAVE:
            renderCreateSaveMenu();
            break;
        case GameState::CREATE_CHARACTER:
            renderCharCreation();
            break;
        case GameState::GIVE_NAME:
            renderNameInput();
            break;
        case GameState::GAME_MENU:
            renderGameMenu();
            break;
        case GameState::INVENTORY_MENU:
            renderItemsMenu();
            break;
        default: break;
    }
}

void Game::render(Character player, Character enemy) {
    renderBattleStatus(player, enemy);
}

