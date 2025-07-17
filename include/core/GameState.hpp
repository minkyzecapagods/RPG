#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include "systems/Battle.hpp"
#include "entities/Character.hpp"
#include "entities/Enemy.hpp"
#include "systems/ItemRegistry.hpp"
#include "systems/Save.hpp"
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
    SHOW_ITEM,
    IN_GAME,
    EXIT
};

struct indexedSave {
    Save save;
    int index;
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
    extern indexedSave currentSave;

    void handleInput();
    void render();
    void render(Character player, Enemy enemy);
}

#define CLEAR_COMMAND "clear"

#endif