#ifndef SAVE_H
#define SAVE_H

#include <string>
#include <vector>
#include <set>
#include "Character.hpp"

extern const vector<string> saveInfo;
extern const int numSaves;

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
  bool saveToFile(const std::string& filename) const; 
};

extern const vector<Save> saveVector;

void renderSaves(const int selectedSave);

#endif