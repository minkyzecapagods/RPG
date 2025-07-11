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
    "Status"
};


void renderBattleMenu() {
    string spc = string(4, ' ');
    cout << spc << " ╭──────────────── ⋆ ♱ ✮ ♱ ⋆ ────────────────╮\n"
         << spc << "▕┘                                           └▏\n";
    for (size_t i = 0; i < battleMenuOptions.size(); ++i) {
        string prefix = (i == Game::selectedOption) ? "• " : "  ";
        size_t spaces = 42 - battleMenuOptions[i].size();
        cout << spc << "▕ " << prefix << battleMenuOptions[i] << string(spaces, ' ') << "▏\n";
    }
    cout << spc << "▕┐                                           ┌▏\n"
         << spc <<" ╰──────────────── ⋆ ♱ ✮ ♱ ⋆ ────────────────╯\n\n"
         << "Use ↑ ↓ para mover, espaço para selecionar, q para sair.\n";
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
        default:
            break;
    }
}

void pressSpaceToContinue(){ //Temporario, enquanto não temos o sistema que fala "fulaninho te atacou"
    bool i = true;
    cout << "Aperte espaço para continuar : " << endl;
    while(i){
        Key key = getArrowKey();
        switch(key){
            case Key::Enter:
                i = false;
                break;
            default:
                continue;
        }
    }
}


void renderBattleStatus(Character player, Character enemy) {
    system(CLEAR_COMMAND);
    cout << string((56 - enemy.getName().length())/2, ' ') << enemy.getName() << "\n"
         << " " << setfill(' ') << setw(3) << enemy.getHp() << ": "
         << "\033[31m" << repeat(enemy.getHp()/2, "▇") << repeat(50 - enemy.getHp()/2, "◫") << "\n\n"  
         << "\033[0m" << "Player attack: " << player.getAttack() << std::endl
         << "Player defense: " << player.getDefense() << std::endl
         << string((56 - player.getName().length())/2, ' ') << player.getName() << "\n"
         <<  " " << setfill(' ') << setw(3) << player.getHp() << ": "
         << "\033[32m" << repeat(player.getHp()/2, "▇") << repeat(50 - player.getHp()/2, "◫") << "\n"
         << "\033[0m" << "Enemy attack: " << enemy.getAttack() << std::endl;
}

void announceAction(string name, int action){
    switch(action){
        case 0:
            cout << name << " atacou!" << endl;
            break;
        case 1:
            cout << name << " se defendeu!" << endl;
            break;
        case 2:
            cout << name << " curou-se!" << endl;
            break;
        case 3:
            cout << name << "verificou o status!" << endl;
            break;
        case -1:
            cout << name << " tentou se defender, mas não conseguiu!" << endl;
            break;
        default:
            cout << "Ação desconhecida!" << endl;
    }
    pressSpaceToContinue();
}