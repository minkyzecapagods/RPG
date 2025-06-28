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

Character::Character(){
    this->name = "Pedro, o comum."; //nome padrão kkkkkkkkkkkkkkkkkkkkkk PEDRO
}
void Character::dealDamage(Character* target){
    int damage = 10 + this->attack;
    target->takeDamage(damage);
}

void Character::takeDamage(int rawDamage){
    int damage = rawDamage - (this->defense - 2);
    if(rawDamage <= (this->defense - 2)){
        damage = 1;
    }

    this->hp -= damage;
    if(this->hp < 0){
        this->hp = 0;
    }
}

void Character::cure(){
    this->hp += this->magic;
    if (this->hp > 100){
        this->hp = 100;
    }
}

void Character::defend(){
    this->defense += 1;
}

void Character::action(size_t choice, Character* target){
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

void Character::action(Character* target){
    Character::dealDamage(target);
}