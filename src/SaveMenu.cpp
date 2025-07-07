#include "GameState.hpp"
#include "SaveMenu.hpp"
#include "ArrowKey.hpp"
#include "utils.hpp"

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

vector<string> saveInfo = {
  " ↑        {SELECTED}        ↓ ",
  " ↑{NAME}↓ ",
  " ↑   Items: {ITEMS}/{TOTAL}   ↓ "
};

int selectedSave = 0;
vector<Save> saves = {Save(), Save(), Save()};
const int numSaves = saves.size();
const int numItens = 10;

void renderSaves() {
  int chars = 69;
  centralPrint(repeat(numSaves, " ↑→→→→→→→→→→→→→→→→→→↓ ", selectedSave) + "\n", chars );
  string str;
  for (int i = 0; i < numSaves; ++i) {
    if (selectedSave == i) str += greenText + replacePlaceholder(saveInfo[0], "{SELECTED}", "◹◸") + normalText;
    else str += replacePlaceholder(saveInfo[0], "{SELECTED}", "  ");
  }
  centralPrint(str, chars);

  string nameStr, itemStr;
  for (int i = 0; i < numSaves; ++i) {
    if (i == selectedSave) {
      nameStr += greenText; 
      itemStr += greenText;
    }

    string name, items;
    if (saves[i].getIsWritten()) {
      name = saves[i].getHero().getName();
      items = to_string(saves[i].getHero().getEquipment().size());
    } else {
      name = "----";
      items = "--";
    }
    nameStr += replacePlaceholder(saveInfo[1], "{NAME}", formatField(name, 18, ' ')); // 18 chars dentro do save
    itemStr += replacePlaceholder(saveInfo[2], {
    {"{TOTAL}", "30"},
    {"{ITEMS}", formatField(items, 2, '0')}
    });

    if (i == selectedSave) {
      nameStr += normalText; 
      itemStr += normalText;
    }
  }
  cout << "\n";
  centralPrint(nameStr + "\n", chars);
  centralPrint(itemStr + "\n", chars);
  centralPrint(repeat(numSaves, " ↑                  ↓ ", selectedSave) + "\n", chars);
  centralPrint(repeat(numSaves, " ↑←←←←←←←←←←←←←←←←←←↓ ", selectedSave) + "\n", chars);
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