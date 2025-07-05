#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "BattleMenu.hpp"
#include "ArrowKey.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "SaveMenu.hpp"
#include "Character.hpp"
#include "Battle.hpp"
#include "CreateMenu.hpp"
#include "utils.hpp"

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
                system(CLEAR_COMMAND);
                i = false;
                break;
            default:
                continue;
        }
    }
}


void renderBattleStatus(Character enemy, Character player) {
    system(CLEAR_COMMAND);
    cout << string((56 - enemy.getName().length())/2, ' ') << enemy.getName() << "\n"
         << " " << setfill(' ') << setw(3) << enemy.getHp() << ": "
         << "\033[31m" << repetir(enemy.getHp()/2, "▇") << repetir(50 - enemy.getHp()/2, "◫") << "\n\n"  
         << "\033[0m" << "Player attack: " << player.getAttack() << std::endl
         << "Player defense: " << player.getDefense() << std::endl
         << string((56 - player.getName().length())/2, ' ') << player.getName() << "\n"
         <<  " " << setfill(' ') << setw(3) << player.getHp() << ": "
         << "\033[32m" << repetir(player.getHp()/2, "▇") << repetir(50 - player.getHp()/2, "◫") << "\n"
         << "\033[0m" << "Player attack: " << player.getAttack() << std::endl;
}   