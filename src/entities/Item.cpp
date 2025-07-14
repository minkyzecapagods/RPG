#include "entities/Item.hpp"
#include <iostream>

using namespace std;

Item::Item(string name, string quest, string description, ItemType type, vector<string> ascii, int bonus)
    : name(name), quest(quest), description(description), type(type), ascii(ascii), bonus(bonus) {}
Item::Item() {
    name = "Default Item";
    quest = "No Quest";
    description = "No Description";
    type = ItemType::WEAPON; // Default type
    ascii = {"Default ASCII Art"};
    bonus = 0; // Default bonus
};

string Item::getName() const { return name; }
string Item::getDescription() const { return description; }
string Item::getQuest() const { return quest; }
ItemType Item::getType() const { return type; }
vector<string> Item::getAscii() const { return ascii; }
int Item::getBonus() const { return bonus; }

string itemTypeToString(ItemType type) {
    switch (type) {
    case ItemType::WEAPON: return "WEAPON";
    case ItemType::ARMOR: return "ARMOR";
    case ItemType::TALISMAN: return "TALISMAN";
    case ItemType::LUCKYCHARM: return "LUCKYCHARM";
    default: return "OTHER"; // TRY CATCH??
    }
}

string itemTypeToStat(ItemType type) {
    switch (type) {
    case ItemType::WEAPON: return "ATK";
    case ItemType::ARMOR: return "ARM";
    case ItemType::TALISMAN: return "MAG";
    case ItemType::LUCKYCHARM: return "LUK";
    default: return "???"; // TRY CATCH??
    }
}