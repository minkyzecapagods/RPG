#ifndef SAVE_H
#define SAVE_H

#include <string>
#include <vector>
#include <set>
#include "entities/Character.hpp"

class ItemRegistry;

class Save {
private:
  Character hero;
  vector<vector<int>> enemys_inventory;
  int existingItems;
  int currentEnemyIndex; // Adicionado para salvar o progresso do inimigo
  bool isWritten;
public:
  Save();
  const Character& getHero() const;
  int getCurrentEnemyIndex() const; // Getter para o índice do inimigo
  vector<vector<int>>& getEnemysInventory();
  bool getIsWritten() const;
  int getexistingItems() const;
  bool saveToFile(const Character& hero, const vector<vector<int>>& enemys_inventory, const ItemRegistry& registry, const int saveIndex);
  bool saveToVector(const Character& hero, const vector<vector<int>>& enemys_inventory, int numItems, int enemyIndex);
  bool deleteSave();
};

extern const int numSaves;
extern vector<Save> saveVector;

void loadFromFile();

void loadSave(const Save& save, int saveId = -1);

#endif