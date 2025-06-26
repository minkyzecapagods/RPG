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
        Character player = Character(player);
        Character enemy = Character(enemy);
        Game::currentState = GameState::MAIN_MENU;
        int result;
        while(true){
            result = advanceBattleLogic(player, enemy);
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
