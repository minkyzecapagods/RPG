#include <iostream>
#include <vector>
#include <string>

#include "Battle.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"
#include "Character.hpp"

Battle::Battle(Character player, Character enemy){
    this->player = player;
    this->enemy = enemy;
};

void Battle::renderBattleMenu() {
    cout << "   __________________\n";
    cout << "/ \\                  ▏\n";
    cout << "\\_,▏                 ▏\n";
    for (size_t i = 0; i < battleMenuOptions.size(); ++i) {
        string prefix = (i == selectedOptionBattle) ? "• " : "  ";
        size_t spaces = 14 - battleMenuOptions[i].size();
        cout << "   ▏ " << prefix << battleMenuOptions[i] << string(spaces, ' ') << "▏\n";
    }
    cout << "   ▏  ________________\n";
    cout << "   \\_/________________/\n\n";
    cout << "Use ↑ ↓ para mover, espaço para selecionar, q para sair.\n";
}

void Battle::renderBattleStatus(){
    system(CLEAR_COMMAND);
    std::cout << "Player hp: " << player.getHp() << std::endl;
    std::cout << "Player attack: " << player.getAttack() << std::endl;
    std::cout << "Player defense: " << player.getDefense() << std::endl;
    std::cout << "Enemy hp: " << enemy.getHp() << std::endl;
}

bool Battle::handleBattleMenuInput() {
    Key key = getArrowKey();
    switch (key) {
        case Key::Up:
            selectedOptionBattle = (selectedOptionBattle - 1 + battleMenuOptions.size()) % battleMenuOptions.size();
            return false;
            break;
        case Key::Down:
            selectedOptionBattle = (selectedOptionBattle + 1) % battleMenuOptions.size();
            return false;
            break;
        case Key::Enter:
            return true;
        default:
            return true;
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

    while(true){
        renderBattleStatus();
        renderBattleMenu();
        if(handleBattleMenuInput()){
            renderBattleMenu();
            break;
        }
    }
    player.action(selectedOptionBattle, &enemy); //ação do player
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

