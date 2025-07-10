#include "Enemy.hpp"

Enemy::Enemy(string name) : Character(name) {}

Enemy::Enemy() : Character() {}

Enemy::Enemy(string name, int defense, int attack, int magic) : Character(name, defense, attack, magic, {}) {}

void Enemy::autoAction(Character* target) {
    if ((this->getHp()) < (target->getAttack() + 10) - this->getDefense()){
        Character::cure();
        return;
    }
    else if(this->getHp() == 100){
        Character::defend();
        return;
    }
    else {
        Character::dealDamage(target);
    }
}