#include <vector>
#include <string>
#include <iostream>

#include "CreateMenu.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"

using namespace std;

string str1;
string str2;
string str3;

vector<string> magnolia = {
" .-/|           \\ /           |\\-. ",
" |||| Magnolia,  | Ataque: 06 |||| ",
" ||||     a      | Defesa: 16 |||| ",
" |||| escudeira  | Mana:   08 |||| ",
" ||||            |            |||| ",
" ||/============\\|/============\\|| ",
" `-------------~___------------~'' ",};

vector<string> cesar = {
" .-/|           \\ /           |\\-. ",
" ||||   Cesar,   | Ataque: 12 |||| ",
" ||||     o      | Defesa: 03 |||| ",
" |||| curandeiro | Mana:   15 |||| ",
" ||||            |            |||| ",
" ||/============\\|/============\\|| ",
" `-------------~___------------~'' ",};

vector<string> cahara = {
" .-/|           \\ /           |\\-. ",
" ||||  Cahara,   | Ataque: 20 |||| ",
" ||||     o      | Defesa: 06 |||| ",
" |||| mercenário | Mana:   04 |||| ",
" ||||            |            |||| ",
" ||/============\\|/============\\|| ",
" `-------------~___------------~'' ",};
vector<string> fechado = 
{
"  (`\\ \\_..-~~-._   _.-~--.._       ",
"   `=\\/\\        \\ /        \\\\      ",
"    `=\\/         V          \\\\     ",
"     //\\_.-~-._  |  _.-~-..__\\\\    ",
"    //) (--~~._\\ | /_.~~--..._\\\\   ",
"   =(_INK_)====\\\\|//============   ",
"                                     ",

};

void getStrs() {
    if (Game::selectedOption == 0) {
        str1 = "    ____________ ▾ ___________         ____________   ___________     ";
        str2 = "    ____________   ___________                                        ";
        str3 = "                             ▏ Voltar ▏                               ";
    }
    if (Game::selectedOption == 1) {
        str1 = "    ____________   ___________         ____________ ▾ ___________     ";
        str2 = "    ____________   ___________                                        ";
        str3 = "                             ▏ Voltar ▏                               ";
    }
    if (Game::selectedOption == 2) {
        str1 = "    ____________   ___________         ____________   ___________     ";
        str2 = "    ____________ ▾ ___________                                        ";
        str3 = "                             ▏ Voltar ▏                              ";
    }
    if (Game::selectedOption == 3) {
        str1 = "    ____________   ___________         ____________   ___________     ";
        str2 = "    ____________   ___________                      ▾                 ";
        str3 = "                             ▏ Voltar ▏                               ";
    }
    if (Game::selectedOption > 3) {
        str1 = "    ____________   ___________         ____________   ___________     ";
        str2 = "    ____________   ___________                                        ";
        str3 = "                             ▏▷ Voltar ▏                              ";
    }
}

void renderCharacterChoice(){
    getStrs();
    system(CLEAR_COMMAND);
    cout << "\n\n" << str1 << "\n";
    for (int i = 0; i < 7; i++) cout << magnolia[i] << cesar[i] << "\n";
    cout << "\n\n" << str2 << "\n";
    for (int i = 0; i < 7; i++) cout << cahara[i] << fechado[i] << "\n";
    cout << "\n\n" << str3 << "\n";
}
    
void handleChoiceMenuInput() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 2 + 6) % 6;
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 2) % 6;
            break;
        case Key::Left:
            Game::selectedOption = (Game::selectedOption - 1 + 5) % 5;
            break;
        case Key::Right:
            Game::selectedOption = (Game::selectedOption + 1) % 5;
            break;
        case Key::Enter:
            if (Game::selectedOption > 3) {
                Game::currentState = GameState::MAIN_MENU;
                Game::selectedOption = 0;
            }
            break;
        case Key::Quit:
            Game::currentState = GameState::EXIT;
            break;
        default:
            break;
    }
}