#include <iostream>
#include <vector>
#include <string>

#include "menus/MainMenu.hpp"
#include "core/GameState.hpp"
#include "core/ArrowKey.hpp"
#include "helpers/utils.hpp"

vector<string> mainMenuOptions = {
    "Novo Jogo",
    "Carregar Jogo",
    "Sair",
    "Battle Test"
};

void renderMainMenu() {
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
            } else if (mainMenuOptions[Game::selectedOption] == "Carregar Jogo") {
                Game::currentState = GameState::SAVE_MENU;
            } else if (mainMenuOptions[Game::selectedOption] == "Sair") {
                Game::currentState = GameState::EXIT;  
            } if (mainMenuOptions[Game::selectedOption] == "Battle Test") {
                Game::currentState = GameState::INITIALIZE_BATTLE;  
            }
            
            Game::selectedOption = 0;
            break;
        }
        case Key::Quit:
            Game::currentState = GameState::EXIT;
            break;
        default:
            break;
    }
}