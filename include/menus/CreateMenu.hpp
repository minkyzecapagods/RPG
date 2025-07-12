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
    vector<string> ascii;
};

extern DefaultCharacter chosen;

void renderCharacterChoice();
void handleChoiceMenuInput();
void handleCreateSaveInput();
void renderCreateSaveMenu();
void resetCustomCharacter();

#endif