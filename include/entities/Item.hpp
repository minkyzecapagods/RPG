#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

using namespace std;

enum class ItemType { WEAPON, ARMOR, TALISMAN, LUCKYCHARM };

class Item {
private:
  string name;
  string quest;
  string description;
  ItemType type;
  vector<string> ascii;
  int bonus;
public:
  Item(string name, string quest, string description, ItemType type, vector<string> ascii, int bonus);
  Item(); // Construtor padrão
  string getName() const;
  string getDescription() const;
  ItemType getType() const;
  int getBonus() const;
};

#endif