#include "Character.hpp"
#include <iostream>

string Character::getName(){return name;}
int Character::getHp(){return hp;}
int Character::getDefense(){return defense;}
int Character::getAttack(){return attack;}
int Character::getMagic(){return magic;}
vector<Item> Character::getEquipment(){return equipment;}

Character::Character(string name){
    this->name = name;
}

void Character::dealDamage(Character target){
    int damage = 10 * attack/4;
    target.takeDamage(damage);
}

void Character::takeDamage(int rawDamage){
    int damage = rawDamage * (60/defense);
    hp -= damage;
}

void Character::cure(){
    hp += magic/4;
    if (hp > 100){
        hp = 100;
    }
}

void Character::defend(){
    defense += 1;
}

void Character::action(size_t choice, Character target){
    switch(choice){
        case 0: //atacar
            Character::dealDamage(target);
            break;
        case 1: //defender
            Character::defend();
            break;
        case 2: //curar
            Character::cure();
            break;
        default:
            cout << "Alguma coisa muito estranha aconteceu!" << endl;
            break;
    }
}

void Character::action(Character target){
    Character::dealDamage(target);
}