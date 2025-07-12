#include "systems/Save.hpp"
#include "helpers/utils.hpp"
#include "core/GameState.hpp"

#include <fstream>
#include <sstream>


using namespace std;

vector<Save> saveVector = {Save(), Save(), Save()};
const int numSaves = saveVector.size();

Save::Save() : hero(), enemys_inventory(), isWritten(false) {}

const Character& Save::getHero() const{ return hero; }

bool Save::getIsWritten() const { return isWritten; }

bool Save::saveToFile(const Character& hero, const vector<vector<int>>& enemys_inv) {
    // Determina índice do save no vetor (por subtração de vetores)
    int index = this - &saveVector[0] + 1; // +1 porque o vetor começa em 0, mas os saves começam em 1

    if (index < 0 || index >= numSaves) return false;

    string filename = "data/saves" + to_string(index) + "/save.txt";
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

bool Save::saveToVector(const Character& hero, const vector<vector<int>>& enemys_inv)  {
    // Determina índice do save no vetor (por subtração de vetores)
    int index = this - &saveVector[0] + 1; // +1 porque o vetor começa em 0, mas os saves começam em 1
    if (index < 0 || index >= numSaves) return false;

    // Atualiza o objeto Save
    this->hero = hero;
    this->enemys_inventory = enemys_inv;
    isWritten = true;

    return true;
}

void loadFromFile() {
  for (int i = 0; i < numSaves; ++i) {
    string filename = "data/save" + to_string(i + 1) + "/save.txt";
    ifstream file(filename);

    if (!file.is_open()) continue;

    string line;
    // Lê linha do herói
    if (getline(file, line)) {
      stringstream ss(line);
      // Lê os dados do herói
      // Exemplo de linha: "HeroName;100;50;30;1,
      string name, defense, attack, magic, equipStr;
      getline(ss, name, ';');
      getline(ss, defense, ';');
      getline(ss, attack, ';');
      getline(ss, magic, ';');
      getline(ss, equipStr, ';');

      // Lê os equipamentos do herói
      // Exemplo de equipStr: "1,2,3"
      vector<int> equipment;
      stringstream equipSS(equipStr);
      string id;
      while (getline(equipSS, id, ',')) equipment.push_back(stoi(id));

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
      saveVector[i].saveToVector(hero, enemys_inv);
    }
    file.close();
  }
}

void loadSave(const Save& save, int saveId) {
    Game::player = save.getHero(); // Atualiza o personagem do jogo com o herói salvo

    addSavedItensInfo(saveId, save.getHero().getEquipment());
    // Quando tiver itens e inimigos, devemos tambem atualizar o inventário dos inimigos
}

bool Save::deleteSave() {
    // Determina índice do save no vetor (por subtração de vetores)
    int index = this - &saveVector[0] + 1; // +1 porque o vetor começa em 0, mas os saves começam em 1
    if (index < 0 || index >= numSaves) return false;

    // Reseta o objeto Save
    saveVector[index - 1] = Save();
    isWritten = false;

    // Remove o arquivo correspondente
    string filename = "data/save" + to_string(index) + "/save.txt";
    ofstream file(filename);
    file.close();
    return true;
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
