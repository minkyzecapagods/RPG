#include "GameState.hpp"
#include "SaveMenu.hpp"
#include "ArrowKey.hpp"
#include "utils.hpp"

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

int selectedSave = 0;
vector<Save> saves = {Save(), Save(), Save()};
const int numSaves = saves.size();
const int numItens = 10;

void renderSaves() {
  cout << repetir(numSaves, "↑→→→→→→→→→→→→→→→→→→↓ ") << "\n";
  string nonSelected = "↑                  ↓ ";
  string selected = "↑        ◹◸        ↓ ";
  for (int i = 0; i < numSaves; ++i) {
    if (selectedSave == i) cout << selected;
    else cout << nonSelected;
  }
  string nameStr = "\n";
  string itemStr = "\n";

  for (int i = 0; i < numSaves; ++i) {
    nameStr += "↑";
    if (saves[i].getIsWritten()) {
      string name = saves[i].getHero().getName();
      int size = name.size(), spaces = (18 - name.size())/2;
      string str = string(spaces, ' ');
      if (size % 2 == 0) {
        nameStr += str + name + str + "↓ ";
      }
      else {
        nameStr += str + name + str + " ↓ ";
      }
      ostringstream num;
      num << setw(2) << setfill('0') << saves[i].getHero().getEquipment().size();
      itemStr += "↑   Items: " + num.str() + "\\" + to_string(numItens) + "   ↓ ";
    }
    else {
      nameStr += "↑       ----       ↓ ";
      itemStr += "↑   Items: --/--   ↓ ";
    }
  }
  cout << nameStr << itemStr << "\n"
       << repetir(numSaves, "↑                  ↓ ") << "\n"
       << repetir(numSaves, "↑←←←←←←←←←←←←←←←←←←↓ ") << "\n";
}

void renderSaveMenu() {
    system(CLEAR_COMMAND);
    cout << "\n\n";
    renderSaves();
    cout << "   __________________\n"
         << "/ \\                  ▏\n"
         << "\\_,▏                 ▏\n";
    for (size_t i = 0; i < saveMenuOptions.size(); ++i) {
        string prefix = (i == Game::selectedOption) ? "• " : "  ";
        size_t spaces = 14 - saveMenuOptions[i].size();
        cout << "   ▏ " << prefix << saveMenuOptions[i] << string(spaces, ' ') << "▏\n";
    }
    cout << "   ▏  ________________\n"
         << "   \\_/________________/\n\n"
         << "Use ↑ ↓ para mover, espaço para selecionar, q para sair.\n";
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
            selectedSave = (selectedSave - 1 + numSaves) % numSaves;
            break;
        case Key::Right:
            selectedSave = (selectedSave + 1) % numSaves;
            break;
        case Key::Enter:
            if (saveMenuOptions[Game::selectedOption] == "Carregar") {
                cout << "a implementar";
            } else if (saveMenuOptions[Game::selectedOption] == "Deletar") {
                cout << "a implementar";
            } else if (saveMenuOptions[Game::selectedOption] == "Voltar") {
                Game::currentState = GameState::MAIN_MENU;
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