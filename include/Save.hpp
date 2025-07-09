#ifndef SAVE_H
#define SAVE_H

#include <string>
#include <vector>
#include <set>
#include "Character.hpp"

class Save {
private:
  Character hero;
  vector<vector<int>> enemys_inventory;
  bool isWritten;
public:
  Save();
  const Character& getHero() const;
  vector<vector<int>>& getEnemysInventory();
  bool getIsWritten() const;
  bool saveToFile(const Character& hero, const vector<vector<int>>& enemys_inventory);
  bool saveToVector(const Character& hero, const vector<vector<int>>& enemys_inventory);
  bool deleteSave();
};

extern const int numSaves;
extern vector<Save> saveVector;

void renderSaves(const int selectedSave);
void loadFromFile();

#endif