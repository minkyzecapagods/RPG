#ifndef CREATEMENU_HPP
#define CREATEMENU_HPP

#include <string>
#include <vector>

using namespace std;

struct DefaultCharacter {
    vector<string> name;
    int defense;
    int attack;
    int magic;
};

void renderCharacterChoice();
void handleChoiceMenuInput();

#endif