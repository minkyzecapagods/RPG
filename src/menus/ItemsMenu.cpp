#include "menus/ItemsMenu.hpp"
#include "core/GameState.hpp"
#include "core/ArrowKey.hpp"
#include "helpers/utils.hpp"
#include "helpers/card_render.hpp"
#include "systems/ItemRegistry.hpp"
#include "entities/Item.hpp"
#include "helpers/item_actions.hpp" // ADICIONADO

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
    // Verifica se o item está equipado
    int itemId = items.getIdByName(selectedItem.first.getName());
    bool isEquipped = false;
    const auto& equipment = Game::player.getEquipment();
    for (int eqId : equipment) {
        if (eqId == itemId) {
            isEquipped = true;
            break;
        }
    }
    // Monta opções dinâmicas
    vector<string> dynamicOptions;
    if (!isEquipped && selectedItem.second) dynamicOptions.push_back("Equipar");
    if (isEquipped) dynamicOptions.push_back("Desequipar");
    if (selectedItem.second) dynamicOptions.push_back("Descartar");
    dynamicOptions.push_back("Voltar");
    renderItemCard(selectedItem);
    cout << "\n";
    renderScroll(dynamicOptions);
    cout << "\n";
    centralPrint("Use setas para mover, espaço para selecionar, pressione q para sair.\n");
}

void handleShowItemInput() {
    // Repete a lógica de opções dinâmicas
    int itemId = items.getIdByName(selectedItem.first.getName());
    bool isEquipped = false;
    const auto& equipment = Game::player.getEquipment();
    for (int eqId : equipment) {
        if (eqId == itemId) {
            isEquipped = true;
            break;
        }
    }
    vector<string> dynamicOptions;
    if (!isEquipped && selectedItem.second) dynamicOptions.push_back("Equipar");
    if (isEquipped) dynamicOptions.push_back("Desequipar");
    if (selectedItem.second) dynamicOptions.push_back("Descartar");
    dynamicOptions.push_back("Voltar");

    Key key = getArrowKey();
    static string lastMessage = "";

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 1 + dynamicOptions.size()) % dynamicOptions.size();
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % dynamicOptions.size();
            break;
        case Key::Enter: {
            string selectedOpt = dynamicOptions[Game::selectedOption];
            if (itemId == -1) {
                lastMessage = "Erro: item não encontrado.";
                cout << "\n";
                centralPrint(lastMessage + "\n");
                lastMessage = "";
                std::cin.get();
                break;
            }
            if (selectedOpt == "Equipar") {
                if (equipItem(itemId)) {
                    lastMessage = "Item equipado com sucesso!";
                } else {
                    lastMessage = "Não foi possível equipar o item (não está desbloqueado).";
                    cout << "\n";
                    centralPrint(lastMessage + "\n");
                    lastMessage = "";
                    std::cin.get();
                }
            } else if (selectedOpt == "Desequipar") {
                if (unequipItem(selectedItem.first.getType())) {
                    lastMessage = "Item desequipado.";
                } else {
                    lastMessage = "Nenhum item desse tipo equipado.";
                    cout << "\n";
                    centralPrint(lastMessage + "\n");
                    lastMessage = "";
                    std::cin.get();
                }
            } else if (selectedOpt == "Descartar") {
                if (discardItem(itemId)) {
                    lastMessage = "Item descartado.";
                    Game::currentState = GameState::INVENTORY_MENU;
                } else {
                    lastMessage = "Não foi possível descartar o item.";
                    cout << "\n";
                    centralPrint(lastMessage + "\n");
                    lastMessage = "";
                    std::cin.get();
                }
            } else if (selectedOpt == "Voltar") {
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
    if (!lastMessage.empty()) {
        cout << "\n";
        centralPrint(lastMessage + "\n");
        lastMessage = "";
    }
}