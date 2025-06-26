#include <iostream>
#include <vector>
#include <string>

#include "Battle.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"
#include "Character.hpp"

size_t selectedOptionBattle = 0;

vector<string> battleMenuOptions = {
    "Atacar",
    "Defender",
    "Curar"
};

void renderBattleMenu() {
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

void renderBattleStatus(Character* player, Character* enemy){
    system(CLEAR_COMMAND);
    std::cout << "Player hp: " << player->getHp() << std::endl;
    std::cout << "Enemy hp: " << enemy->getHp() << std::endl;
}

size_t handleBattleMenuInput() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
            selectedOptionBattle = (selectedOptionBattle - 1 + battleMenuOptions.size()) % battleMenuOptions.size();
            break;
        case Key::Down:
            selectedOptionBattle = (selectedOptionBattle + 1) % battleMenuOptions.size();
            break;
        case Key::Enter:
            return selectedOptionBattle;
        default:
            break;
    }
}

int advanceBattleLogic(Character* player, Character* enemy){

    renderBattleStatus(player, enemy);
    renderBattleMenu();
    handleBattleMenuInput();
    player->action(selectedOptionBattle, enemy);
    renderBattleStatus(player, enemy);
    if (enemy->getHp() <= 0){
        return 1; //flag de vitória
    }

    size_t enemyAction = 0; // inimigo sempre atacando
    enemy->action(enemyAction, player);
    renderBattleStatus(player, enemy);
    if(player->getHp() <= 0){
        return 2; //flag derrota
    }

    return 0; //a batalha deve continuar
}

