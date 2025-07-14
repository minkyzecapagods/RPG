#include "menus/ItemsMenu.hpp"
#include "core/GameState.hpp"
#include "core/ArrowKey.hpp"
#include "helpers/utils.hpp"
#include "systems/ItemRegistry.hpp"
#include "entities/Item.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> itemsMenuOptions = {
    "Inspecionar",
    "Descartar", // Estabelecer limite de 12 itens
    "Voltar"
};

void renderItemsMenu() {

    renderGenericList(items.getAllItems(), Game::selectedHorizontal);
    renderScroll(itemsMenuOptions);
    cout << "\n";
    centralPrint("Use setas para mover, espaço para selecionar, pressione q para sair.\n");
}

void handleItemsMenuInput() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 1 + itemsMenuOptions.size()) % itemsMenuOptions.size();
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % itemsMenuOptions.size();
            break;
        case Key::Enter: {
            if (itemsMenuOptions[Game::selectedOption] == "Selecionar") {
               cout << "Selecionar opção ainda não implementado.\n";
            } else if (itemsMenuOptions[Game::selectedOption] == "Descartar") {
                cout << "Descartar opção ainda não implementado.\n";
            } else if (itemsMenuOptions[Game::selectedOption] == "Voltar") {
                Game::currentState = GameState::GAME_MENU; 
            }
            Game::selectedOption = 0;
            break;
        }
        case Key::Quit:
            Game::currentState = GameState::EXIT;
            break;
        default:
            break;
    }
}