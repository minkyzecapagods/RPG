#include <iostream>
#include <vector>
#include <string>

#include "MainMenu.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"

vector<string> mainMenuOptions = {
    "Novo Jogo",
    "Carregar Jogo",
    "Sair"
};

void renderMainMenu() {
    system(CLEAR_COMMAND);
    cout << "   __________________\n";
    cout << "/ \\                  ▏\n";
    cout << "\\_,▏                 ▏\n";
    for (size_t i = 0; i < mainMenuOptions.size(); ++i) {
        string prefix = (i == Game::selectedOption) ? "• " : "  ";
        size_t spaces = 14 - mainMenuOptions[i].size();
        cout << "   ▏ " << prefix << mainMenuOptions[i] << string(spaces, ' ') << "▏\n";
    }
    cout << "   ▏  ________________\n";
    cout << "   \\_/________________/\n\n";
    cout << "Use ↑ ↓ para mover, espaço para selecionar, q para sair.\n";
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
        case Key::Enter:
            if (mainMenuOptions[Game::selectedOption] == "Novo Jogo") {
                Game::currentState = GameState::IN_GAME;
            } else if (mainMenuOptions[Game::selectedOption] == "Carregar Jogo") {
                Game::currentState = GameState::SAVE_MENU;
            } else if (mainMenuOptions[Game::selectedOption] == "Sair") {
                Game::currentState = GameState::EXIT;
            }
            Game::selectedOption = 0;
            break;
        case Key::Quit:
            Game::currentState = GameState::EXIT;
            break;
        default:
            break;
    }
}