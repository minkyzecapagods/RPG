#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

using namespace std;

enum class ItemType { ARMA, ARMADURA, TALISMA, ANEL };

class Item {
private:
  string name;
  string description;
  ItemType type;
  int bonus;
  bool isLocked;

public:
  Item(string name, string description, ItemType type, int bonus, bool isLocked);
  string getName() const;
  string getDescription() const;
  ItemType getType() const;
  int getBonus() const;
  bool getIsLocked() const;
  void setIsLocked(bool locked);
};

extern vector<Item> UnlockedItems;

#endif