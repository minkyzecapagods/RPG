#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

enum class ItemType { ARMA, ARMADURA, TALISMA, ANEL };

class Item {
private:
  string name;
  string description;
  ItemType type;
  int bonus;
  bool isLocked;
};              

#endif