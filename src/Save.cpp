#include "Save.hpp"
#include "utils.hpp"

#include <fstream>
#include <sstream>

using namespace std;

vector<Save> saveVector = {Save(), Save(), Save()};
const int numSaves = saveVector.size();

Save::Save() : hero(), enemys_inventory(), isWritten(false) {}

const Character& Save::getHero() const{ return hero; }

vector<vector<int>>& Save::getEnemysInventory() {return enemys_inventory;}

bool Save::getIsWritten() const { return isWritten; }

bool Save::saveToFile(const Character& hero, const vector<vector<int>>& enemys_inv) {
    // Determina índice do save no vetor (por subtração de vetores)
    int index = this - &saveVector[0];
    if (index < 0 || index >= numSaves) return false;

    string filename = "../saves/save" + to_string(index) + ".txt";
    ofstream file(filename);
    if (!file.is_open()) return false;

    // Salva os dados do personagem
    file << hero.getName() << ";" << hero.getDefense() << ";" 
         << hero.getAttack() << ";" << hero.getMagic() << ";";

    // Salva equipamentos do herói
    for (size_t i = 0; i < hero.getEquipment().size(); ++i) {
        file << hero.getEquipment()[i];
        if (i != hero.getEquipment().size() - 1)
            file << ",";
    }
    file << "\n";

    // Salva inventário dos inimigos
    for (const auto& inv : enemys_inv) {
        for (size_t i = 0; i < inv.size(); ++i) {
            file << inv[i];
            if (i != inv.size() - 1)
                file << ",";
        }
        file << "\n";
    }

    file.close();

    // Atualiza o objeto Save
    this->hero = hero;
    this->enemys_inventory = enemys_inv;
    isWritten = true;

    return true;
}

void loadFromFile() {
    for (int i = 0; i < numSaves; ++i) {
        string filename = "../saves/save" + to_string(i) + ".txt";
        ifstream file(filename);
        if (!file.is_open()) {
            saveVector[i] = Save();
            continue;
        }

        string line;
        // Lê linha do herói
        if (getline(file, line)) {
            stringstream ss(line);
            string name, defense, attack, magic, equipStr;

            getline(ss, name, ';');
            getline(ss, defense, ';');
            getline(ss, attack, ';');
            getline(ss, magic, ';');
            getline(ss, equipStr, ';');

            vector<int> equipment;
            stringstream equipSS(equipStr);
            string id;
            while (getline(equipSS, id, ',')) {
                equipment.push_back(stoi(id));
            }

            Character hero(name, stoi(defense), stoi(attack), stoi(magic), equipment);

            // Lê inventário dos inimigos
            vector<vector<int>> enemys_inv;
            while (getline(file, line)) {
                stringstream invSS(line);
                vector<int> inv;
                while (getline(invSS, id, ',')) {
                    inv.push_back(stoi(id));
                }
                enemys_inv.push_back(inv);
            }

            saveVector[i].saveToFile(hero, enemys_inv);
        }
        file.close();
    }
}

void renderSaves(const int selectedSave) {
    vector<string> saveInfo = {
                                " ↑        {SELECTED}        ↓ ",
                                " ↑{NAME}↓ ",
                                " ↑   Items: {ITEMS}/{TOTAL}   ↓ "};
                                
  int chars = 23 * numSaves;  // largura do quadrado do save é 23
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
