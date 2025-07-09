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
        void autoAction(Character* target);
};

#endif