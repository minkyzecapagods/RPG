#include <vector>
#include <string>
#include <iostream>

#include "CreateMenu.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"
#include "utils.hpp"
#include "Save.hpp"
#include "card_render.hpp"

using namespace std;

vector<string> createChar = {
    "  (`\\ \\_..-~~-._   _.-~--.._       ",
    "   `=\\/\\        \\ /        \\\\      ",
    "    `=\\/         V          \\\\     ",
    "     //\\_.-~-._  |  _.-~-..__\\\\   ",
    "    //) (--~~._\\ | /_.~~--..._\\\\   ",
    "   =(_INK_)====\\\\|//============   ",
    "                                   "};


// Name, defense, attack, mana
const DefaultCharacter tank = {{"Magnolia,", "a", "escudeira"}, 16, 6, 8,{
    "       _,.",
    "     ,` -.)                   ",
    "    ( _/-\\-._                ",
    "   /,|`--._,-^                ",
    "   \\_| |`-._/|                ",
    "     |  `-, /|                ",
    "     |    || |                ",
    "     `r-._||/  _______        ",
    "  __,-<_   |__/       \\__",
    ",'  \\   `--/   )))))))   \\",
    "|    |    /  ))       ))  \\",
    "|    /   /  )           )  \\",
    " \\_/' \\ |  )       Θ     )  |",
    "  |    ||  )     Θ   Θ   )  | ",
    "  |    ,|  )       Θ     )  | ",
    "   \\,.->.\\  )           )  /",
    "   (  /   \\  ))       ))  /",
    "    `Y-.___\\__ ))))))) __/",
    "     |        \\_______/",}};
const DefaultCharacter healer = {{"Cesar,", "o", "curandeiro"}, 3, 12, 15, {
    "               _____          ",
    "              / \\   \\         ",
    "             / / \\   \\        ",
    "    .       / /   \\   \\       ",
    "   @        \\ \\___/  \\ ]      ",
    "  ,*       _/          \\__    ",
    "    ,     (____,__,______ )   ",
    "   * @     |   (++)  \\   \\\\   ",
    "  @  *    /|   ,   ,  \\   \\\\  ",
    "  * .    / |  ,     ,  \\   \\  ",
    "  (((( _/   \\,       , /'\\  \\ ",
    "   \\__\\    / \\________/  /  / ",
    "     [____/  (__(__)__) /   \\ ",
    "             /  /  \\  | \\___/ ",
    "            /       \\ | /  \\  ",
    "           /     '  \\  \\@__/  ",
    "           \\ '    \\  \\  \\     ",
    "           /   /'  \\  \\ /     ",
    "           \\  ' '   \\   \\     "}};

 DefaultCharacter assassin = {{"Cahara,", "o", "assassino"}, 20, 6, 4, {
    "⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⢸⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⢸⠈⠑⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⡜⠀⢃⠀⠀⠀⠀⠀⠀⠀⠀⢘⣆⣄⣀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⣷⠀⢸⠀⠀⠀⠀⠀⠀⠀⡴⠉⠀⠀⡽⠙⢮⢣⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⡇⠀⢸⠀⠀⠀⠀⠀⢠⣾⣤⣤⣒⣦⣽⣄⡀⣇⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⡇⠀⢸⠀⠀⠀⠀⠀⠀⣿⠇⠀⠀⢸⠙⢝⠯⢭⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⡇⠀⢸⠀⠀⠀⠀⠀⠀⣿⡄⠀⠀⠈⡄⠀⠙⢆⠙⢄⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⢹⠀⡏⠀⠀⠀⠀⠀⠀⡝⣷⢄⣤⣾⢔⣒⣒⣚⠦⣜⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⢸⠀⡇⠀⠀⠀⠀⠀⠀⠳⣾⣷⡼⠁⠓⠒⠒⠒⠭⣢⡙⡄⠀⠀⠀⠀⠀⠀  ",
    "⠀⢀⣀⣸⠀⣇⣀⣀⠀⠀⢀⡠⠒⣹⢽⢁⡖⠉⠉⠉⠉⠲⠈⢳⢸⠀⠀⠀⠀⠀⠀  ",
    "⠀⠈⢩⣿⠿⡿⡟⠻⡖⠉⠁⢀⡾⢃⢟⡾⠔⠒⠠⢄⡀⠀⡇⠀⡟⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⢻⣺⣩⣷⠇⣰⡕⣀⣤⠟⠁⠸⡄⡇⠀⠀⠀⠀⠹⢠⠁⡰⠁⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠠⡏⠉⢉⡿⢍⡀⠀⢸⡀⢀⣤⠞⢜⠦⣀⣀⣠⣼⠗⠊⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠐⢧⣀⡿⠀⠀⠈⠁⠒⠛⠛⠷⣄⠀⠉⠒⣲⠏⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⠀⠻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠃⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⢀⣀⣤⣴⡾⠯⠤⠄⠐⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⠀⠀⠸⣄⡀⠤⠔⠊⠁⡏⠀⠀⠀⠀⢀⣀⣀⡨⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡏⠉⠉⠉⠉⠁⠀⠀⠀⠘⣄⠀⠀⠀⠀⠀⠀⠀⠀  ",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢆⠀⠀⠀⠀⠀⠀⠀  ", 
}};

DefaultCharacter custom = {{"????", "", ""}, 10, 10, 10, {
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

vector<DefaultCharacter> choices = {tank, healer, assassin, custom};

DefaultCharacter chosen;

vector<string> createSaveOptions = {
  "Salvar",
  "Deletar",
  "Voltar",
};

vector<string> createCustomOptions = {
  "Confirmar",
  "Voltar",
};

void renderCharacterChoice(){
    int chars = 71;
    vector<string> str = getHeaders(),
                   frstCard = formatCharacterCard(choices[0]),
                   scdCard = formatCharacterCard(choices[1]),
                   trdCard = formatCharacterCard(choices[2]);

    vector<string> selected = {"", "", "", ""};
    if (Game::selectedOption < 4) selected[Game::selectedOption] = greenText;
    
    system(CLEAR_COMMAND);

    cout << "\n\n";
    centralPrint(str[0] +"\n", chars); 
    for (int i = 0; i < 7; i++) centralPrint(selected[0] + frstCard[i] + normalText +
                                             selected[1] + scdCard[i] + normalText + "\n", chars);
    cout << "\n\n";
    centralPrint(str[1] + "\n", chars);
    for (int i = 0; i < 7; i++) centralPrint(selected[2] + trdCard[i] + normalText +
                                             selected[3] + createChar[i] + normalText + "\n", chars);
    cout << "\n\n";
    centralPrint(str[2] + "\n", chars);
}

void renderCharCreation() {
    system(CLEAR_COMMAND);
    renderCharCustom(custom);
    cout << "\n";
    centralPrint("Distribua 30 pontos de atributo da forma que desejar\n", 51);
    renderScroll(createCustomOptions);
}

void renderCreateSaveMenu() {
  system(CLEAR_COMMAND);
  renderCharStats(chosen);
  renderSaves(Game::selectedHorizontal);
  renderScroll(createSaveOptions);
}

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

void handleChoiceMenuInput() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 2 + 6) % 6;
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 2) % 6;
            break;
        case Key::Left:
            Game::selectedOption = (Game::selectedOption - 1 + 5) % 5;
            break;
        case Key::Right:
            Game::selectedOption = (Game::selectedOption + 1) % 5;
            break;
        case Key::Enter: {
            if (Game::selectedOption < 3) {
                Game::currentState = GameState::CREATE_SAVE;
                chosen = choices[Game::selectedOption];
            } else if (Game::selectedOption == 3) {
                Game::currentState = GameState::CREATE_CHARACTER;
            } else {
                Game::currentState = GameState::MAIN_MENU;
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

void handleCreateSaveInput() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 1 + createSaveOptions.size()) % createSaveOptions.size();
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % createSaveOptions.size();
            break;
        case Key::Left:
            Game::selectedHorizontal = (Game::selectedHorizontal - 1 + numSaves) % numSaves;
            break;
        case Key::Right:
            Game::selectedHorizontal = (Game::selectedHorizontal + 1) % numSaves;
            break;
        case Key::Enter:
            if (createSaveOptions[Game::selectedOption] == "Salvar") {
                cout << "a implementar";
            } else if (createSaveOptions[Game::selectedOption] == "Deletar") {
                cout << "a implementar";
            } else if (createSaveOptions[Game::selectedOption] == "Voltar") {
                Game::currentState = GameState::CREATE_MENU_CHOICE;
            }
            Game::selectedOption = 0;
            Game::selectedHorizontal = 0;
            break;
        case Key::Quit:
            Game::currentState = GameState::EXIT;
            break;
        default:
            break;
    }
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
            } if (Game::selectedOption == 0) {
                Game::currentState = GameState::CREATE_SAVE;
                chosen = custom;
            } else Game::currentState = GameState::CREATE_MENU_CHOICE;

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