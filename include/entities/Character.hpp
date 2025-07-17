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
    
        // Métodos auxiliares para calcular bônus de itens
        int getAttackBonus() const;
        int getDefenseBonus() const;
        int getMagicBonus() const;
    protected:
        bool raisedDefenses = false;
    public:
        Character(string name); //construtor
        Character(string name, int baseDefense, int baseAttack, int baseMagic, vector<int> equipment);
        Character(); //construtor padrão
        
        //getters
        string getName() const;
        int getHp() const;
        void setHp(int value);
        int getMaxHp() const;
        int getDefense() const;
        int getAttack() const;
        int getMagic() const;
        const vector<int>& getEquipment() const;
        vector<int>& getEquipment();

        //setters

        void addDefense(int addedDefense);
        void addAttack(int addedAttack);
        void addMagic(int addedMagic);

        //void addItem(Item i);

        void dealDamage(Character* target);

        void takeDamage(int rawDamage);

        void cure();

        virtual bool defend(bool havePlayerDefended);

        //void action(Character* target);

        int action(size_t choice, Character* target, bool havePlayerDefended);
};

#endif