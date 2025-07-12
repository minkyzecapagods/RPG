#include "menus/CustomMenu.hpp"
#include "menus/CreateMenu.hpp"
#include "core/GameState.hpp"
#include "core/ArrowKey.hpp"
#include "helpers/utils.hpp"
#include "systems/Save.hpp"
#include "helpers/card_render.hpp"

DefaultCharacter custom = {{"", "", "", ""}, 10, 10, 10, {
"                 __           ",
"             ___/ /\\          ",
"            /,  /  _\\         ",
"         _/   / / / \\\\        ",
"        /__    / /   \\       ",
"       ||  |  ( (     ))      ",
"        '  \\_  \\ \\   //       ",
"             \\ ,\\_\\_//        ",
"            /  ___  /         ",
"          _/  /   | \\______   ",
"         /   |    |_/      \\  ",
"        / ,  |         ____ / ",
"       /    \\ \\     __/   (/  ",
"     _/      \\ \\___/ /        ",
"    /  /     \\     |         ",
"   / ///            /         ",
"  / //             |          ",
" / //              |          ",}};

vector<string> createCustomOptions = {
  "Confirmar",
  "Voltar",
};

void changeAttribute() {
    if (Game::selectedHorizontal == 0) {
        switch (Game::selectedOption) {
            case 2: // Attack
                if (custom.attack >= 5) custom.attack-= 5;
                break;
            case 3: // Defense
                if (custom.defense >= 5) custom.defense-= 5;
                break;  
            case 4: // Magic
                if (custom.magic >= 5) custom.magic-= 5;
                break;
        default:
            break;
        }} else {
        if (custom.attack + custom.defense + custom.magic >= 30) return;
        switch (Game::selectedOption) {
            case 2: // Attack
                custom.attack+= 5;
                break;
            case 3: // Defense
                custom.defense+= 5;
                break;  
            case 4: // Magic
                custom.magic+= 5;
                break;
        default:
            break;
        }
    }
}

void renderCharCreation() {
    renderCharCustom(custom);
    cout << "\n";
    vector<string> title = {
      "░█▀▄░█░▄▀▀░▀█▀▒█▀▄░█░██▄░█▒█▒▄▀▄░░░▄▀▀▒██▀░█▒█░▄▀▀░░▒█▀▄░▄▀▄░█▄░█░▀█▀░▄▀▄░▄▀▀",
      "▒█▄▀░█▒▄██░▒█▒░█▀▄░█▒█▄█░▀▄█░█▀█▒░▒▄██░█▄▄░▀▄█▒▄██▒░░█▀▒░▀▄▀░█▒▀█░▒█▒░▀▄▀▒▄██"};
    for (const auto& line : title) centralPrint(line + "\n", 73);
    cout << "\n";
    renderScroll(createCustomOptions);
    cout << "\n";
    centralPrint("Use setas para mover, espaço para selecionar, pressione q para sair.\n");
}

void handleCharCreation() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 1 + 5) % 5;
            if (Game::selectedOption == 0) Game::selectedHorizontal = 0;
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % 5;
            if (Game::selectedOption == 0) Game::selectedHorizontal = 0;
            break;
        case Key::Left:
            Game::selectedHorizontal = (Game::selectedHorizontal - 1 + 2) % 2;
            break;
        case Key::Right:
            Game::selectedHorizontal = (Game::selectedHorizontal + 1) % 2;
            break;
        case Key::Enter: {
            if (Game::selectedOption > 1) {
                changeAttribute();
                break;
            } 
            if (createCustomOptions[Game::selectedOption] == "Confirmar") 
              Game::currentState = GameState::GIVE_NAME;
            else if (createCustomOptions[Game::selectedOption] == "Voltar")
              Game::currentState = GameState::CREATE_MENU_CHOICE;

            Game::selectedOption = 0;
            Game::selectedHorizontal = 0;
            break;
        }
        case Key::Quit:
            Game::currentState = GameState::EXIT;
            break;
        default:
            break;
    }
}

void renderNameInput() {
    renderCharStats(custom);
    vector<string> title = {
        "░█▀▄░█░▄▀▒░█░▀█▀▒██▀░░░▄▀▄░░░█▄░█░▄▀▄░█▄▒▄█▒██▀░░░█▀▄░▄▀▄░░░▄▀▀▒██▀░█▒█░",
        "▒█▄▀░█░▀▄█░█░▒█▒░█▄▄▒░░▀▄▀▒░░█▒▀█░▀▄▀░█▒▀▒█░█▄▄▒░▒█▄▀░▀▄▀▒░▒▄██░█▄▄░▀▄█▒",
        "              ░▒█▀▄▒██▀▒█▀▄░▄▀▀░▄▀▄░█▄░█▒▄▀▄░▄▀▒▒██▀░█▄▒▄█              ",
        "              ░░█▀▒░█▄▄░█▀▄▒▄██░▀▄▀░█▒▀█░█▀█░▀▄█░█▄▄░█▒▀▒█              ",};

    for (const auto& line : title) centralPrint(line + "\n", 72);
    string color = "";
    if (Game::selectedOption == 2) color = greenText;
    centralPrint(color +"┏━━━━━━━━━━━━━━┓" + normalText + "\n", 16);
    centralPrint(color + "┃ ", 16);
    cout << formatField(custom.name[0], 12, ' ') << " ┃\n" << normalText;
    centralPrint(color + "┗━━━━━━━━━━━━━━┛\n\n" + normalText, 16);
    renderScroll(createCustomOptions);
    cout << "\n";
    centralPrint("Use setas para mover, espaço para selecionar, pressione q para sair.\n");
}

void handleNameInput() {
  Charrow key = getCharKey();

  switch (key.arrowKey) {
    case Key::Backspace:
      if (!custom.name[0].empty()) custom.name[0].pop_back();
      return;
    case Key::Up:
      Game::selectedOption = (Game::selectedOption - 1 + 3) % 3;
      return;
    case Key::Down:
      Game::selectedOption = (Game::selectedOption + 1) % 3;
      return;
    case Key::Enter: {
      if (createCustomOptions[Game::selectedOption] == "Confirmar") {
        chosen = custom;
        Game::currentState = GameState::CREATE_SAVE;
      } else if (createCustomOptions[Game::selectedOption] == "Voltar") {
        custom.name[0] = "";
        Game::currentState = GameState::CREATE_CHARACTER;
      } else break;
      Game::selectedOption = 0;
      return; }
    case Key::Quit:
      if (Game::selectedOption != 2) {
        Game::currentState = GameState::EXIT;
        return;
      }
      break;
    default: break;
  }

    char c = key.key;
    if (c == '\b' || c == 127) { // Backspace
      if (!custom.name[0].empty()) custom.name[0].pop_back();
      return;
    }
    if (custom.name[0].size() < 12 && c != '\0') {
      custom.name[0] += c;
      return;
    }
}