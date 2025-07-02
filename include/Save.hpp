#ifndef SAVEMENU_H
#define SAVEMENU_H

#include <string>
#include <vector>
#include <set>
#include "Character.hpp"

class Save {
private:
  Character hero;
  bool isEmpty;
  vector<bool> unlocked;
  set<vector<bool>> enemys_inventory;
  };
#endif