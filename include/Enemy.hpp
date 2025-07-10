#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include <Character.hpp>

#include "Item.hpp"

using namespace std;

class Enemy : public Character {
    public:
        Enemy();
        Enemy(string name);
        bool defend(bool havePlayerDefended) override;
        int autoAction(Character* target, bool havePlayerDefended, bool haveEnemyDefended);
};

#endif