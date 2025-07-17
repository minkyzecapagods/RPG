#include <iostream>

#include "entities/Character.hpp"
#include "menus/BattleMenu.hpp"
#include "core/ArrowKey.hpp"
#include "core/GameState.hpp"
#include "menus/MainMenu.hpp"
#include "menus/SaveMenu.hpp"
#include "entities/Character.hpp"
#include "systems/Battle.hpp"
#include "menus/CreateMenu.hpp"
#include "helpers/utils.hpp"
#include "systems/ItemRegistry.hpp"

using namespace std;

string Character::getName() const{return name;}
int Character::getHp() const{return hp;}

const vector<int>& Character::getEquipment() const{return equipment;}
vector<int>& Character::getEquipment() { return equipment; }

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
    this->name = "----";
    hp = 100;
    defense = 10;
    attack = 10;
    magic = 10;
    equipment = {};
}
void Character::dealDamage(Character* target){
    int damage = 10 + this->getAttack();
    
    target->takeDamage(damage);  //chamando a takeDamage do target
}

void Character::takeDamage(int rawDamage){
    int damage = rawDamage - this->getDefense();
    if(this->raisedDefenses){
        damage = rawDamage - this->getDefense() - 5;
    }

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

bool Character::defend(bool havePlayerDefended){
    if(havePlayerDefended) {
        this->raisedDefenses = false;
        return false;
    }
    else {
        this->raisedDefenses = true;
        return true;
    }
}

int Character::action(size_t choice, Character* target, bool havePlayerDefended) {
    raisedDefenses = false; // Reseta o estado de defesa antes de cada ação
    switch(choice){
        case 0: //atacar
            this->dealDamage(target);
            return 0; // Retorna 0 para indicar que a ação foi de ataque
            break;
        case 1: //defender
            if (this->defend(havePlayerDefended)){
                return 1; //Retorna 1 para indicar que tentou defender e conseguiu
            };
            return -1; // Retorna -1 para indicar que tentou defender e não conseguiu
            break;
        case 2: //curar
            this->cure();
            return 2; // Retorna 2 para indicar que a ação foi de cura
            break;
        default:
            cout << "Alguma coisa muito estranha aconteceu!" << endl;
            return 4; // Retorna -1 para indicar que a ação é inválida
            break;
    }
}

int Character::getAttackBonus() const {
    int bonus = 0;
    for (int id : equipment) {
        Item item = items.getItem(id);
        if (item.getType() == ItemType::WEAPON)
            bonus += item.getBonus();
    }
    return bonus;
}

int Character::getDefenseBonus() const {
    int bonus = 0;
    for (int id : equipment) {
        Item item = items.getItem(id);
        if (item.getType() == ItemType::ARMOR)
            bonus += item.getBonus();
    }
    return bonus;
}

int Character::getMagicBonus() const {
    int bonus = 0;
    for (int id : equipment) {
        Item item = items.getItem(id);
        if (item.getType() == ItemType::TALISMAN)
            bonus += item.getBonus();
    }
    return bonus;
}

int Character::getAttack() const {
    return attack + getAttackBonus();
}

int Character::getDefense() const {
    return defense + getDefenseBonus();
}

int Character::getMagic() const {
    return magic + getMagicBonus();
}

void Character::setHp(int value) {
    hp = value;
}

int Character::getMaxHp() const {
    return 100; // Valor fixo, pode ser alterado se necessário
}
