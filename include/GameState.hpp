#ifndef GAMETATE_H
#define GAMESTATE_H

#include <string>

using namespace std;

// Estados possíveis do jogo
enum class GameState {
    MAIN_MENU,
    SAVE_MENU,
    CREATE_MENU_CHOICE,
    CREATE_MENU_CUSTOM,
    BATTLES_MENU,
    INVENTORY_MENU,
    IN_GAME,
    EXIT
};

namespace Game {
    extern GameState currentState;
    extern size_t selectedOption;

    void handleInput();
    void render();
}

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

#endif