#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "Battle.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"
#include "Character.hpp"
#include "utils.hpp"

using namespace std;

//teste
vector<string> n = {
"              _,-'|",
"           ,-'._  |",
" .||,      |####\\ |",
"\\.`',/     \\####| |",
"= ,. =      |###| |",
"/ || \\    ,-'\\#/,'`.",
"  ||     ,'   `,,. `.",
"  ,|____,' , ,;' \\| |",
" (3|\\    _/|/'   _| |",
"  ||/,-''  | >-'' _,\\",
"  ||'      ==\\ ,-'  ,'",
"  ||       |  V \\ ,|",
"  ||       |    |` |",
"  ||       |    |   \\",
"  ||       |    \\    \\",
"  ||       |     |    \\",
"  ||       |      \\_,-'",
"  ||       |___,,--')_\\",
"  ||         |_|   ccc/",
"  ||        ccc/",
"  ||"};

Battle::Battle(Character player, Character enemy){
    this->player = player;
    this->enemy = enemy;
};

void Battle::renderBattleMenu() {
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

void Battle::renderBattleStatus(){
    system(CLEAR_COMMAND);
    cout << string((56 - enemy.getName().length())/2, ' ') << enemy.getName() << "\n"
         << " " << setfill(' ') << setw(3) << enemy.getHp() << ": "
         << "\033[31m" << repeat(enemy.getHp()/2, "▇") << repeat(50 - enemy.getHp()/2, "◫") << "\n\n"  
         << "\033[0m" << "Player attack: " << player.getAttack() << std::endl
         << "Player defense: " << player.getDefense() << std::endl
         << string((56 - player.getName().length())/2, ' ') << player.getName() << "\n"
         <<  " " << setfill(' ') << setw(3) << player.getHp() << ": "
         << "\033[32m" << repeat(player.getHp()/2, "▇") << repeat(50 - player.getHp()/2, "◫") << "\n"
         << "\033[0m" << "Player attack: " << player.getAttack() << std::endl;
}   

bool Battle::handleBattleMenuInput() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
             Game::selectedOption = (Game::selectedOption - 1 + battleMenuOptions.size()) % battleMenuOptions.size();
            return false;
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % battleMenuOptions.size();
            return false;
            break;
        case Key::Enter:
            return true;
        default:
            return false;
            break;
    }
}

void Battle::pressSpaceToContinue(){ //Temporario, enquanto não temos o sistema que fala "fulaninho te atacou"
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

int Battle::advanceBattleLogic(){

    while(true){ //menu da batalha
        renderBattleStatus();
        renderBattleMenu();
        if(handleBattleMenuInput()){
            renderBattleMenu();
            break;
        }
    }
    
    player.action(Game::selectedOption, &enemy); //ação do player
    renderBattleStatus(); //atualização da vida dos jogadores

    if (enemy.getHp() <= 0){
        return 1; //flag de vitória
    }

    pressSpaceToContinue();

    enemy.action(&player); // por enquanto o inimigo só ataca msm
    renderBattleStatus();
    if(player.getHp() <= 0){
        return 2; //flag derrota
    }

    return 0; //a batalha deve continuar
}

