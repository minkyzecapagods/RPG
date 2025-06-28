#include <iostream>

#include "GameState.hpp"
#include "MainMenu.hpp"
#include "Character.hpp"
#include "Battle.hpp"

GameState Game::currentState = GameState::MAIN_MENU;

void Game::handleInput() {
    if (Game::currentState == GameState::MAIN_MENU) {
        handleMainMenuInput();
    }
}

void Game::render() {
    if (Game::currentState == GameState::MAIN_MENU) {
        renderMainMenu();
    } else if (Game::currentState == GameState::IN_GAME) {
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
    }
}
