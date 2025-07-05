#ifndef GAMETATE_H
#define GAMESTATE_H

#include <string>
#include "Battle.hpp"

using namespace std;

// Estados possíveis do jogo
enum class GameState {
    MAIN_MENU,
    SAVE_MENU,
    CREATE_MENU_CHOICE,
    CREATE_MENU_CUSTOM,
    INITIALIZE_BATTLE,
    BATTLE_MENU,
    INVENTORY_MENU,
    IN_GAME,
    EXIT
};

namespace Game {
    extern GameState currentState;
    extern size_t selectedOption;
    extern bool isBattleActive;
    extern bool isBattleOver;

    void handleInput();
    void render();
    void render(Battle currentBattle);
    void startBattle();
}

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

#endif