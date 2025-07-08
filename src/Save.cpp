#include "Save.hpp"
#include "utils.hpp"

#include <fstream>
#include <sstream>

using namespace std;

const vector<Save> saveVector = {Save(), Save(), Save()};
const int numSaves = saveVector.size();

const vector<string> saveInfo = {
  " ↑        {SELECTED}        ↓ ",
  " ↑{NAME}↓ ",
  " ↑   Items: {ITEMS}/{TOTAL}   ↓ "
};

Save::Save() {
  this -> hero = Character("boyy");
  vector<vector<int>> enemys_inventory(3);
  enemys_inventory[0] = {101, 102, 103};  
  enemys_inventory[1].push_back(201);
  enemys_inventory[2].push_back(202);
  this -> enemys_inventory = enemys_inventory;
  this -> isWritten = true;
}

const Character& Save::getHero() const{ return hero; }

vector<vector<int>>& Save::getEnemysInventory() {return enemys_inventory;}

bool Save::getIsWritten() const { return isWritten; }

bool Save::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return false;

    // Salvar nome e atributos com ponto e vírgula
    out << hero.getName() << "; "
        << hero.getAttack() << "; "
        << hero.getMagic() << "; "
        << hero.getDefense() << ";"
        << "\n";

    // Salvar itens do personagem
    const vector<int>& items = hero.getEquipment();
    for (int id : items) {
        out << id << " ";
    }
    out << "\n";

    // Salvar inventário dos inimigos
    for (const auto& inv : enemys_inventory) {
        for (int item : inv) {
            out << item << " ";
        }
        out << "\n";
    }

    return true;
}

void renderSaves(const int selectedSave) {
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
    if (saveVector[i].getIsWritten()) {
      name = saveVector[i].getHero().getName();
      items = to_string(saveVector[i].getHero().getEquipment().size());
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