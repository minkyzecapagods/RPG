#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>


#include "Item.hpp"

using namespace std;

class Character {
    private:
        string name;
        int hp = 100;
        int defense = 100;
        int attack = 100;
        int magic = 100;
        vector <Item> equipment;
    public:
        Character(string name); //construtor
        string getName();
        int getHp();
        int getDefense();
        int getAttack();
        int getMagic();
        vector<Item> getEquipment();

        //void addItem(Item i);

        void dealDamage(Character* target);

        void takeDamage(int rawDamage);

        void cure();

        void defend();

        void action(Character* target);

        void action(size_t choice, Character* target);
};

#endif