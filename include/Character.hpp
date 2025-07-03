#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>


#include "Item.hpp"

using namespace std;

class Character {
    private:
        string name;
        int hp;
        int defense;
        int attack;
        int magic;
        vector<int> equipment;
    public:
        Character(string name); //construtor
        Character(); //construtor padrão
        string getName() const;
        int getHp() const;
        int getDefense() const;
        int getAttack() const;
        int getMagic() const;
        const vector<int>& getEquipment() const;

        //void addItem(Item i);

        void dealDamage(Character* target);

        void takeDamage(int rawDamage);

        void cure();

        void defend();

        void action(Character* target);

        void action(size_t choice, Character* target);
};

#endif