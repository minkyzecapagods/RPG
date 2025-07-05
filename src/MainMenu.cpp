#include <iostream>
#include <vector>
#include <string>

#include "MainMenu.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"
#include "utils.hpp"

vector<string> mainMenuOptions = {
    "Novo Jogo",
    "Carregar Jogo",
    "Sair",
    "Battle Test"
};

void renderMainMenu() {
    system(CLEAR_COMMAND);
    renderScroll(mainMenuOptions);
    centralPrint("Use setas para mover, espaço para selecionar, pressione q para sair.\n");
}

void handleMainMenuInput() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 1 + mainMenuOptions.size()) % mainMenuOptions.size();
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % mainMenuOptions.size();
            break;
        case Key::Enter: {
            if (mainMenuOptions[Game::selectedOption] == "Novo Jogo") {
                Game::currentState = GameState::CREATE_MENU_CHOICE;
            } if (mainMenuOptions[Game::selectedOption] == "Carregar Jogo") {
                Game::currentState = GameState::SAVE_MENU;
            } if (mainMenuOptions[Game::selectedOption] == "Sair") {
                Game::currentState = GameState::EXIT;  
            } if (mainMenuOptions[Game::selectedOption] == "Battle Test") {
                Game::currentState = GameState::IN_GAME;  
            }
            break;} 
            Game::selectedOption = 0;
            break;
        case Key::Quit:
            Game::currentState = GameState::EXIT;
            break;
        default:
            break;
    }
}