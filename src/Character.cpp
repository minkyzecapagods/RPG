#include "Character.hpp"
#include <iostream>

using namespace std;

string Character::getName() const{return name;}
int Character::getHp() const{return hp;}
int Character::getDefense() const{return defense;}
int Character::getAttack() const{return attack;}
int Character::getMagic() const{return magic;}

const vector<int>& Character::getEquipment() const{return equipment;}

void Character::addDefense(int addedDefense){
    defense += addedDefense;
    if (defense < 0) {
        defense = 0; // Evita defesa negativa
    }
}

void Character::addAttack(int addedAttack){
    attack += addedAttack;
    if (attack < 0) {
        attack = 0; // Evita ataque negativo
    }
}

void Character::addMagic(int addedMagic){
    magic += addedMagic;
    if (magic < 0) {
        magic = 0; // Evita magia negativa
    }
}

Character::Character(string name) {
    this->name = name;
    hp = 100;
    defense = 10;
    attack = 10;
    magic = 10;
    equipment = {1, 2, 3, 4};
}

Character::Character(string name, int defense, int attack, int magic, vector<int> equipment) {
    this->name = name;
    this->hp = 100; // HP padrão
    this->defense = defense;
    this->attack = attack;
    this->magic = magic;
    this->equipment = equipment;

    // Verifica se os valores de defesa, ataque e magia são válidos
    if (this->defense < 0) this->defense = 0;
    if (this->attack < 0) this->attack = 0;
    if (this->magic < 0) this->magic = 0;
}


Character::Character() {
    this->name = "name";
    hp = 100;
    defense = 10;
    attack = 10;
    magic = 10;
    equipment = {1, 2, 3, 4};
}
void Character::dealDamage(Character* target){
    int damage = 10 + this->attack;
    
    target->takeDamage(damage);  //chamando a takeDamage do target
}

void Character::takeDamage(int rawDamage){
    int damage = rawDamage - defense;
    if(damage < 1){
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

//void Character::action(Character* target){
   // Character::dealDamage(target);
    //IA
//}