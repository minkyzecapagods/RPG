#include <iostream>

#include "GameState.hpp"
#include "MainMenu.hpp"

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
        std::cout << "Em andamento...\n\n";
        Game::currentState = GameState::MAIN_MENU;
    }
}
