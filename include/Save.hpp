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
  Character& getHero();
  vector<vector<int>>& getEnemysInventory();
  bool getIsWritten() const;
  bool saveToFile(const std::string& filename) const; 
};

#endif