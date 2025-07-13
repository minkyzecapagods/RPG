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
  int numItems;
  bool isWritten;
public:
  Save();
  const Character& getHero() const;
  vector<vector<int>>& getEnemysInventory();
  bool getIsWritten() const;
  int getNumItems() const;
  bool saveToFile(const Character& hero, const vector<vector<int>>& enemys_inventory, const ItemRegistry& registry, const int saveIndex);
  bool saveToVector(const Character& hero, const vector<vector<int>>& enemys_inventory, int numItems);
  bool deleteSave();
};

extern const int numSaves;
extern vector<Save> saveVector;

void renderSaves(const int selectedSave);
void loadFromFile();

void loadSave(const Save& save, int saveId = -1);

#endif