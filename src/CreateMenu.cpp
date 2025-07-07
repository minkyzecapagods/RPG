#include <vector>
#include <string>
#include <iostream>

#include "CreateMenu.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"
#include "utils.hpp"

using namespace std;

// Name, defense, attack, mana
const DefaultCharacter tank = {{"Magnolia,", "a", "escudeira"}, 16, 6, 8};
const DefaultCharacter healer = {{"Cesar,", "o", "curandeiro"}, 3, 12, 15};
const DefaultCharacter assassin = {{"Cahara,", "o", "assassino"}, 20, 6, 4};

vector<string> defaultChar = {
" .-/|           \\ /           |\\-. ",
" ||||{NAME}| Ataque: {ATK} |||| ",
" ||||     {THE}      | Defesa: {DEF} |||| ",
" ||||{TITLE}| Mana:   {MAG} |||| ",
" ||||            |            |||| ",
" ||/============\\|/============\\|| ",
" `-------------~___------------~'' ",};

vector<string> createChar = 
{
"  (`\\ \\_..-~~-._   _.-~--.._       ",
"   `=\\/\\        \\ /        \\\\      ",
"    `=\\/         V          \\\\     ",
"     //\\_.-~-._  |  _.-~-..__\\\\   ",
"    //) (--~~._\\ | /_.~~--..._\\\\   ",
"   =(_INK_)====\\\\|//============   ",
"                                   ",
};

vector<string> getStrs() {
    string sel1 = " ", sel2 = " ", sel3 = " ", sel4 = " ", sel5 = " ";
    string c1 = normalText, c2 = normalText, c3 = normalText, c4 = normalText, c5 = normalText;

    if (Game::selectedOption == 0) sel1 = "▾", c1 = greenText;
    if (Game::selectedOption == 1) sel2 = "▾", c2 = greenText;
    if (Game::selectedOption == 2) sel3 = "▾", c3 = greenText;
    if (Game::selectedOption == 3) sel4 = "▾", c4 = greenText;
    if (Game::selectedOption > 3) sel5 = "▷", c5 = greenText;

    string str1 = c1 + "    ____________ " + sel1 + " ___________    " + c2 + "     ____________ " + sel2 + " ___________     " + normalText;
    string str2 = c3 + "    ____________ " + sel3 + " ___________    " + c4 + "                  " + sel4 + "                 " + normalText;
    string str3 = c5 + "                              " + sel5 + " Voltar                                " + normalText;
    
    return {str1, str2, str3};
}

vector<string> formatCharacterCard(DefaultCharacter character) {
    vector<string> result = defaultChar;
    
    string name = formatField(character.name[0], 12, ' ');       
    string title = formatField(character.name[2], 12, ' ');
    string atk = formatField(to_string(character.attack), 2, '0');
    string def = formatField(to_string(character.defense), 2, '0');
    string mag = formatField(to_string(character.magic), 2, '0');
    result[1] = replacePlaceholder(result[1], {
    {"{NAME}", name},
    {"{ATK}", atk}
    });
    result[2] = replacePlaceholder(result[2], {
    {"{THE}", character.name[1]},
    {"{DEF}", def}
    });
    result[3] = replacePlaceholder(result[3], {
    {"{TITLE}", title},
    {"{MAG}", mag}
    });
    return result;
}

void renderCharacterChoice(){
    int chars = 71;
    vector<string> str = getStrs(),
                   tankCard = formatCharacterCard(tank),
                   healerCard = formatCharacterCard(healer),
                   assassinCard = formatCharacterCard(assassin);

    string sel1 = "", sel2 = "", sel3 = "", sel4 = "", sel5 = "";
    if (Game::selectedOption == 0) sel1 = greenText;
    if (Game::selectedOption == 1) sel2 = greenText;
    if (Game::selectedOption == 2) sel3 = greenText;
    if (Game::selectedOption == 3) sel4 = greenText;
    if (Game::selectedOption > 3) sel5 = greenText;
    
    system(CLEAR_COMMAND);

    cout << "\n\n";
    centralPrint(sel1 + str[0] + normalText +"\n", chars); 
    for (int i = 0; i < 7; i++) centralPrint(sel1 + tankCard[i] + normalText +
                                             sel2 + healerCard[i] + normalText + "\n", chars);
    cout << "\n\n";
    centralPrint(sel3 + str[1] + normalText + "\n", chars);
    for (int i = 0; i < 7; i++) centralPrint(sel3 + assassinCard[i] + normalText +
                                             sel4 + createChar[i] + normalText + "\n", chars);
    cout << "\n\n";
    centralPrint(sel5 + str[2] + "\n", chars);
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