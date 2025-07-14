#include "systems/ItemRegistry.hpp"
#include "entities/Item.hpp"
#include "core/GameState.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

ItemRegistry items("data/items/items.txt");

ItemRegistry::ItemRegistry(const string& itemsFilePath)
    : itemsFilePath(itemsFilePath) { }

Item ItemRegistry::getItem(int id) {
    auto it = itemMap.find(id);
    if (it != itemMap.end()) {
        return it->second;
    } else {
        throw runtime_error("Item com ID " + to_string(id) + " não encontrado.");
    }
}

vector<pair<Item, bool>> ItemRegistry::getAllItems() {
    vector<pair<Item, bool>> result;

    for (const auto& [id, item] : itemMap) {
        bool unlocked = isUnlocked(id);
        result.emplace_back(item, unlocked);
    }

    return result;
}

void ItemRegistry::setItemsFilePath(const string& newFilePath) {
    itemsFilePath = newFilePath;
}

void ItemRegistry::unlockItem(int id) {
    if (itemMap.find(id) != itemMap.end()) {
        unlockedItems.push_back(id);
    } else {
        throw runtime_error("Item com ID " + to_string(id) + " não encontrado.");
    }
}

void ItemRegistry::lockItem(int id) {
    auto it = find(unlockedItems.begin(), unlockedItems.end(), id);
    if (it != unlockedItems.end()) {
        unlockedItems.erase(it);
    } else {
        throw runtime_error("Item com ID " + to_string(id) + " não está desbloqueado.");
    }
}

void ItemRegistry::setUnlockedItems(const vector<int>& unlocked) {
    unlockedItems = unlocked;
}

int ItemRegistry::getNumItems() const { return itemMap.size(); }

ItemType stringToItemType(const string& typeStr) {
  if (typeStr == "WEAPON") return ItemType::WEAPON;
  if (typeStr == "ARMOR") return ItemType::ARMOR;
  if (typeStr == "TALISMAN") return ItemType::TALISMAN;
  if (typeStr == "LUCKYCHARM") return ItemType::LUCKYCHARM;
  // TRY CATCH AQUI????
  return ItemType::WEAPON;
}

void ItemRegistry::addItem(const Item& item) {
    // Gera novo ID sequencial
    int newId = 1;
    if (!itemMap.empty()) {
        auto maxIt = max_element(itemMap.begin(), itemMap.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });
        newId = maxIt->first + 1;
    }
    
    // 3. Adicionar ao mapa
    itemMap[newId] = item;
}

void ItemRegistry::loadItemsFromFile() {
  itemMap.clear();
  unlockedItems.clear();
  ifstream file(itemsFilePath);
  if (!file.is_open()) {
  throw runtime_error("Erro ao abrir arquivo de itens: " + itemsFilePath);
  }

  string line;
  while (getline(file, line)) {
    // Ignorar linhas vazias
    if (line.empty()) continue;

      string name, quest, description;
      ItemType type;
      vector<string> ascii;
      int bonus;

        name = line;

        // Quest
        if (!getline(file, quest)) break;

        // Description
        if (!getline(file, description)) break;

        // Tipo
        string typeStr;
        if (!getline(file, typeStr)) break;
        type = stringToItemType(typeStr);

        // Bonus
        string bonusStr;
        if (!getline(file, bonusStr)) break;
        try {
            bonus = stoi(bonusStr);
        } catch (...) {
            bonus = 0; // Valor padrão se conversão falhar
        }

        // Arte ASCII
        while (getline(file, line)) {
            if (line.empty()) break; // Linha vazia indica fim da arte
            
            // Remover espaços iniciais/finais se necessário
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);
            
            ascii.push_back(line);
        }

        this->addItem(Item(name, quest, description, type, ascii, bonus));
    }
  file.close();
}

void addSavedItensInfo(int index, const vector<int> &equipment) {
    if (index != -1) items.setItemsFilePath("data/saves/save" + to_string(index + 1) + "/saved_items.txt");
   items.loadItemsFromFile();
   items.setUnlockedItems(equipment);
}

void resetItemRegistry() {
    items = ItemRegistry("data/items/items.txt");
}

bool ItemRegistry::isUnlocked(int id) {
    return std::find(unlockedItems.begin(), unlockedItems.end(), id) != unlockedItems.end();
}

bool ItemRegistry::saveItemsToFile() {
    string filename = "data/saves/save" + to_string(Game::currentSave.index + 1) + "/saved_items.txt";
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo para escrita: " << filename << endl;
       return false;
    }

    // Escrever cada item no arquivo
    bool firstItem = true;
    for (const auto& [id, item] : itemMap) {
        // Linha vazia entre itens (exceto antes do primeiro)
        if (!firstItem) file << '\n';
        firstItem = false;

        // Escrever campos básicos
        file << item.getName() << '\n'
             << item.getDescription() << '\n'
             << item.getQuest() << '\n'
             << itemTypeToString(item.getType()) << '\n'
             << item.getBonus() << '\n';

        // Escrever arte ASCII
        for (const string& line : item.getAscii()) {
            file << line << '\n';
        }
    }

    file.close();
    return true;
}
