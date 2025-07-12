#include "entities/Item.hpp"
#include <iostream>

using namespace std;

Item::Item(string name, string description, ItemType type, int bonus, bool isLocked)
    : name(name), description(description), type(type), bonus(bonus), isLocked(isLocked){}
string Item::getName() const { return name; }
string Item::getDescription() const { return description; }
ItemType Item::getType() const { return type; }
int Item::getBonus() const { return bonus; }
bool Item::getIsLocked() const { return isLocked; }
void Item::setIsLocked(bool locked) { isLocked = locked; }