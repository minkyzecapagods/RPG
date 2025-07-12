#include "core/GameState.hpp"
#include "menus/SaveMenu.hpp"
#include "systems/Save.hpp"
#include "core/ArrowKey.hpp"
#include "helpers/utils.hpp"

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

vector<string> saveMenuOptions = {
  "Carregar",
  "Deletar",
  "Voltar",
};

void renderSaveMenu() {
  renderSaves(Game::selectedHorizontal);
  renderScroll(saveMenuOptions);
}

void handleSaveMenuInput() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 1 + saveMenuOptions.size()) % saveMenuOptions.size();
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % saveMenuOptions.size();
            break;
        case Key::Left:
            Game::selectedHorizontal = (Game::selectedHorizontal - 1 + numSaves) % numSaves;
            break;
        case Key::Right:
            Game::selectedHorizontal = (Game::selectedHorizontal + 1) % numSaves;
            break;
        case Key::Enter:
            if (saveMenuOptions[Game::selectedOption] == "Carregar") {
                cout << "a implementar";
            } else if (saveMenuOptions[Game::selectedOption] == "Deletar") {
                saveVector[Game::selectedHorizontal].deleteSave();
                break;
            } else if (saveMenuOptions[Game::selectedOption] == "Voltar")
                Game::currentState = GameState::MAIN_MENU;
            Game::selectedOption = 0;
            Game::selectedHorizontal = 0;
            break;
        case Key::Quit:
            Game::currentState = GameState::EXIT;
            break;
        default:
            break;
    }
}