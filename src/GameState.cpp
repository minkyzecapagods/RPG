#include <iostream>

#include "GameState.hpp"
#include "MainMenu.hpp"
#include "SaveMenu.hpp"
#include "Character.hpp"
#include "Battle.hpp"
#include "CreateMenu.hpp"
#include "BattleMenu.hpp"

GameState Game::currentState = GameState::MAIN_MENU;
size_t Game::selectedOption = 0;
bool Game::isBattleActive = false;
bool Game::isBattleOver = false;

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
        default: break;
    }
}

void Game::render() {
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
        default: break;
    }
}

void Game::render(Character player, Character enemy) {
    renderBattleStatus(player, enemy);
}

