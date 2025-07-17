#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "menus/BattleMenu.hpp"
#include "core/ArrowKey.hpp"
#include "core/GameState.hpp"
#include "menus/MainMenu.hpp"
#include "menus/SaveMenu.hpp"
#include "entities/Character.hpp"
#include "systems/Battle.hpp"
#include "menus/CreateMenu.hpp"
#include "helpers/utils.hpp"

using namespace std;

vector<string> battleMenuOptions = {
    "Atacar",
    "Defender",
    "Curar",
    "Fugir"
};


void renderBattleMenu() {
    cout << normalText;
    int chars = 47;
    centralPrint(" ╭──────────────── ⋆ ♱ ✮ ♱ ⋆ ────────────────╮\n", chars);
    centralPrint("▕┘                                           └▏\n", chars);
    for (size_t i = 0; i < battleMenuOptions.size(); ++i) {
        string prefix = (i == Game::selectedOption) ? greenText + "• " : "  ";
        size_t spaces = 42 - battleMenuOptions[i].size();
        string line = "▕ " + prefix + battleMenuOptions[i] + string(spaces, ' ') + normalText + "▏\n";
        centralPrint(line, chars);
    }
    centralPrint("▕┐                                           ┌▏\n", chars);
    centralPrint(" ╰──────────────── ⋆ ♱ ✮ ♱ ⋆ ────────────────╯\n\n", chars);
    centralPrint("Use ↑ ↓ para mover, espaço para selecionar.\n", 44);
}

void handleBattleMenuInput() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
             Game::selectedOption = (Game::selectedOption - 1 + battleMenuOptions.size()) % battleMenuOptions.size();
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % battleMenuOptions.size();
            break;
        case Key::Enter:
            Game::currentState = GameState::IN_GAME; // Indica que uma opção foi selecionada
            break;
        default:
            break;
    }
}

void pressSpaceToContinue(){ //Temporario, enquanto não temos o sistema que fala "fulaninho te atacou"
    bool i = true;
    centralPrint("Aperte espaço para continuar : \n");
    while(i){
        Key key = getArrowKey();
        switch(key){
            case Key::Enter:
                i = false;
                system(CLEAR_COMMAND);
                break;
            default:
                continue;
        }
    }
}


void renderBattleStatus(Character player, Character enemy) {
    system(CLEAR_COMMAND);
    enemy.printAscii();
    cout << "\n\n";
    centralPrint(enemy.getName());
    cout << "\n";
    string enemyBar = formatField(to_string(enemy.getHp()) + ": ", 3, '0') +
        redText + repeat(enemy.getHp()/2, "▇") +
        repeat(50 - enemy.getHp()/2, "◫") + normalText + "\n\n";
    centralPrint(enemyBar, 55);
    centralPrint(player.getName()); 
    cout << "\n";
    string playerBar = formatField(to_string(player.getHp()) + ": ", 3, '0') +
        greenText + repeat(player.getHp()/2, "▇") +
        repeat(50 - player.getHp()/2, "◫") + normalText + "\n\n";
    centralPrint(playerBar, 55);
}

void announceAction(string name, int action){
    switch(action){
        case 0:
            centralPrint(name + " atacou!" + "\n");
            break;
        case 1:
            centralPrint(name + " se defendeu!" + "\n");
            break;
        case 2:
            centralPrint(name + " curou-se!" + "\n");
            break;
        case 3:
            centralPrint(name + " fugiu!" + "\n");
            break;
        case -1:
            centralPrint(name + " tentou se defender, mas nao conseguiu!" + "\n");
            break;
        default:
            centralPrint("Acao desconhecida!\n");
    }
    pressSpaceToContinue();
}