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
  int chars = 69;
  centralPrint(repetir(numSaves, " ↑→→→→→→→→→→→→→→→→→→↓ ") + "\n", chars );
  string nonSelected = " ↑                  ↓ ";
  string selected = " ↑        ◹◸        ↓ ";
  string str;
  for (int i = 0; i < numSaves; ++i) {
    if (selectedSave == i) str += selected;
    else str += nonSelected;
  }
  centralPrint(str, chars);
  string nameStr, itemStr;

  for (int i = 0; i < numSaves; ++i) {
    nameStr += " ↑";
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
      itemStr += " ↑   Items: " + num.str() + "\\" + to_string(numItens) + "   ↓ ";
    }
    else {
      nameStr += " ↑       ----       ↓ ";
      itemStr += " ↑   Items: --/--   ↓ ";
    }
  }
  cout << "\n";
  centralPrint(nameStr + "\n", chars);
  centralPrint(itemStr + "\n", chars);
  centralPrint(repetir(numSaves, " ↑                  ↓ ") + "\n", chars);
  centralPrint(repetir(numSaves, " ↑←←←←←←←←←←←←←←←←←←↓ ") + "\n", chars);
}

void renderSaveMenu() {
  system(CLEAR_COMMAND);
  renderSaves();
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