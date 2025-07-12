#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include "systems/Battle.hpp"
#include "entities/Character.hpp"
#include "entities/Enemy.hpp"
#include "systems/ItemRegistry.hpp"
using namespace std;

// Estados possíveis do jogo
enum class GameState {
    MAIN_MENU,
    SAVE_MENU,
    CREATE_MENU_CHOICE,
    CREATE_MENU_CUSTOM,
    GIVE_NAME,
    CREATE_SAVE,
    CREATE_CHARACTER,
    INITIALIZE_BATTLE,
    GAME_MENU,
    BATTLE_MENU,
    INVENTORY_MENU,
    IN_GAME,
    EXIT
};

namespace Game {
    extern GameState currentState;
    extern size_t selectedOption;
    extern Character player;
    extern bool isBattleActive;
    extern bool isBattleOver;
    extern int selectedHorizontal;
    extern int currentEnemyIndex;
    Enemy getEnemyByIndex(int index);
    size_t getTotalEnemies();
    extern Character player;
    extern Save currentSave;

    void handleInput();
    void render();
    void render(Character player, Character enemy);
}

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

#endif