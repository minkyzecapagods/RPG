#include "entities/Enemy.hpp"
#include "menus/BattleMenu.hpp"
#include <ctime>

Enemy::Enemy(string name) : Character(name) {}

Enemy::Enemy() : Character() {}

Enemy::Enemy(string name, int defense, int attack, int magic) : Character(name, defense, attack, magic, {}) {}

int Enemy::autoAction(Character* target, bool havePlayerDefended, bool haveEnemyDefended) {
    this->raisedDefenses = false;

    size_t choice;
    std::srand(std::time(0));

    int shouldDefend = rand() % 3; // 33% chance to defend

    if ((this->getHp()) < (target->getAttack() + 10) - this->getDefense()){
        choice = 2; // Cure
    }
    else if(shouldDefend == 0 && !haveEnemyDefended) {
        choice = 1; // Defend
    }
    else {
        choice = 0; // Attack
    }

    return this->action(choice, target, haveEnemyDefended, havePlayerDefended);
}