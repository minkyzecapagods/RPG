#include "systems/Save.hpp"
#include "helpers/utils.hpp"
#include "core/GameState.hpp"
#include "systems/ItemRegistry.hpp"

#include <fstream>
#include <sstream>

using namespace std;

vector<Save> saveVector = {Save(), Save(), Save()};
const int numSaves = saveVector.size();

Save::Save() : hero(), enemys_inventory(), existingItems(0), currentEnemyIndex(0), isWritten(false) {}

const Character& Save::getHero() const{ return hero; }

int Save::getCurrentEnemyIndex() const { return currentEnemyIndex; }

int Save::getexistingItems() const { return existingItems; }

bool Save::getIsWritten() const { return isWritten; }

bool Save::saveToFile(const Character& hero, const vector<vector<int>>& enemys_inv, const ItemRegistry& registry, const int saveIndex) {
    // Determina índice do save no vetor (por subtração de vetores)
    int index = saveIndex + 1;// +1 porque o vetor começa em 0, mas os saves começam em 1
    
    if (index < 0 || index >= numSaves) {
      cout << "PROBLEMA DE INT: " << index;
      return false;
    }
    
    string filename = "data/saves/save" + to_string(index) + "/save.txt";
    ofstream file(filename);
    if (!file.is_open()) {
      cout << "PROBLEMA DE SAVE";
      return false;
    }
    
    // Salva os dados do personagem
    file << hero.getName() << ";" << hero.getDefense() << ";" 
         << hero.getAttack() << ";" << hero.getMagic() << ";"
         << Game::currentEnemyIndex << ";";

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

    file << registry.getNumItems() << ";\n";
    
    file.close();

    // Atualiza o objeto Save
    saveVector[saveIndex].saveToVector(hero, enemys_inv, registry.getNumItems(), Game::currentEnemyIndex);
    return true;
}

bool Save::saveToVector(const Character& hero, const vector<vector<int>>& enemys_inv, int numItemsToSave, int enemyIndex)  {
    // Atualiza o objeto Save
    this->hero = hero;
    this->enemys_inventory = enemys_inv;
    this->existingItems = numItemsToSave;
    this->currentEnemyIndex = enemyIndex;
    isWritten = true;

    return true;
}

void loadFromFile() {
  for (int i = 0; i < numSaves; ++i) {
    string filename = "data/saves/save" + to_string(i + 1) + "/save.txt";
    ifstream file(filename);

    if (!file.is_open()) continue;

    string line;
    // Lê linha do herói
    if (getline(file, line)) {
      stringstream ss(line);
      // Lê os dados do herói
      // Exemplo de linha: "HeroName;100;50;30;1,
      string name, defense, attack, magic, equipStr, enemyIndexStr;
      getline(ss, name, ';');
      getline(ss, defense, ';');
      getline(ss, attack, ';');
      getline(ss, magic, ';');
      getline(ss, enemyIndexStr, ';');
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
      int numItemsToSave;
      while (getline(file, line)) {
        stringstream invSS(line);
        vector<int> inv;
        while (getline(invSS, id, ',')) {
          if (!id.empty() && id.back() == ';') {
              id.pop_back(); // remove o ;
              numItemsToSave = stoi(id);
          }
          if (!id.empty())
              inv.push_back(stoi(id));
          }
          enemys_inv.push_back(inv);
        }
        saveVector[i].saveToVector(hero, enemys_inv, numItemsToSave, stoi(enemyIndexStr));
      }
      file.close();
    }
  }

void loadSave(const Save& save, int saveId) {
  
    Game::player = save.getHero(); // Atualiza o personagem do jogo com o herói salvo
    Game::currentEnemyIndex = save.getCurrentEnemyIndex(); // Atualiza o índice do inimigo

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
    string filename = "data/saves/save" + to_string(index) + "/save.txt";
    ofstream file(filename);
    file.close();
    return true;
}