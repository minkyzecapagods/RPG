#include "menus/ItemsMenu.hpp"
#include "core/GameState.hpp"
#include "core/ArrowKey.hpp"
#include "helpers/utils.hpp"
#include "helpers/card_render.hpp"
#include "systems/ItemRegistry.hpp"
#include "entities/Item.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

pair<Item, bool> selectedItem = {Item(), false};

vector<string> itemsMenuOptions = {
    "Inspecionar",
    "Voltar"
};

vector<string> showItemOptions = {
    "Equipar",
    "Desequipar",
    "Descartar", // Estabelecer limite de 12 itens
    "Voltar"
};

void renderItemsMenu() {
    if (items.getNumItems() == 0) {
        cout << "\n\n";
        centralPrint("Nenhum item encontrado.\n");
        renderScroll({"Voltar"});
        return;
    }
    vector<vector<pair<Item, bool>>> vectorsOf3 = separateInVectorsOf3(items.getAllItems());
    cout << "\n\n";
    int index = Game::selectedHorizontal/3;
    string total = to_string(items.getNumItems()/3);
    renderGenericList(vectorsOf3[index], Game::selectedHorizontal%3);
    cout << "\n";
    centralPrint("Pagina " + to_string(index + 1) + "/" + total + "\n");
    renderScroll(itemsMenuOptions);
    cout << "\n";
    centralPrint("Use setas para mover, espaço para selecionar, pressione q para sair.\n");
}

void handleItemsMenuInput() {
    if (items.getNumItems() == 0) {
        Key key = getArrowKey();
        if (key == Key::Enter || key == Key::Quit) {
            Game::currentState = GameState::GAME_MENU;
        }
        return;
    }

    Key key = getArrowKey();
    int totalItems = items.getNumItems();

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 1 + itemsMenuOptions.size()) % itemsMenuOptions.size();
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % itemsMenuOptions.size();
            break;
        case Key::Left:
            Game::selectedHorizontal = (Game::selectedHorizontal - 1 + totalItems) % totalItems;
            break;
        case Key::Right:
            Game::selectedHorizontal = (Game::selectedHorizontal + 1) % totalItems;
            break;
        case Key::Enter: {
            if (itemsMenuOptions[Game::selectedOption] == "Inspecionar") {
                selectedItem = items.getAllItems()[Game::selectedHorizontal];
                Game::currentState = GameState::SHOW_ITEM; 
            } else if (itemsMenuOptions[Game::selectedOption] == "Voltar") {
                Game::currentState = GameState::GAME_MENU; 
                Game::selectedHorizontal = 0;
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

void renderShowItem() {
    renderItemCard(selectedItem);
    cout << "\n";
    renderScroll(showItemOptions);
    cout << "\n";
    centralPrint("Use setas para mover, espaço para selecionar, pressione q para sair.\n");
}

void handleShowItemInput() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 1 + showItemOptions.size()) % showItemOptions.size();
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % showItemOptions.size();
            break;
        case Key::Enter: {
            if (showItemOptions[Game::selectedOption] == "Equipar") {

            } else if (showItemOptions[Game::selectedOption] == "Desequipar") {
               
            } else if (showItemOptions[Game::selectedOption] == "Descartar") {

            } else if (showItemOptions[Game::selectedOption] == "Voltar") {
                Game::currentState = GameState::INVENTORY_MENU;
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