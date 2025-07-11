#include <vector>
#include <string>
#include <iostream>

#include "menus/CreateMenu.hpp"
#include "menus/CustomMenu.hpp"
#include "core/GameState.hpp"
#include "core/ArrowKey.hpp"
#include "helpers/utils.hpp"
#include "systems/Save.hpp"
#include "helpers/card_render.hpp"

using namespace std;

vector<string> createChar = {
    "  (`\\ \\_..-~~-._   _.-~--.._       ",
    "   `=\\/\\        \\ /        \\\\      ",
    "    `=\\/         V          \\\\     ",
    "     //\\_.-~-._  |  _.-~-..__\\\\   ",
    "    //) (--~~._\\ | /_.~~--..._\\\\   ",
    "   =(_INK_)====\\\\|//============   ",
    "                                   "};


// Nome, defesa, ataque, magia e arte ASCII dos personagens
const DefaultCharacter tank = {{"Magnolia", ", ", "a", " escudeira"}, 16, 6, 8,{
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
const DefaultCharacter healer = {{"Cesar", ", ", "o", " curandeiro"}, 3, 12, 15, {
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

 DefaultCharacter assassin = {{"Cahara", ", ", "o", " assassino"}, 20, 6, 4, {
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

vector<DefaultCharacter> choices = {tank, healer, assassin};

DefaultCharacter chosen;

vector<string> createSaveOptions = {
  "Salvar",
  "Deletar",
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
    cout << "\n";
    centralPrint("Use setas para mover, espaço para selecionar, pressione q para sair.\n");
}

void renderCreateSaveMenu() {
  renderCharStats(chosen);
  renderSaves(Game::selectedHorizontal);
  renderScroll(createSaveOptions);
  cout << "\n";
  centralPrint("Use setas para mover, espaço para selecionar, pressione q para sair.\n");
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
            if (Game::selectedOption < 3) {  //Defaults
                Game::currentState = GameState::CREATE_SAVE;
                chosen = choices[Game::selectedOption];
            } else if (Game::selectedOption == 3) { //Custom
                Game::currentState = GameState::CREATE_CHARACTER;
            } else { //Voltar
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

Character chosenCharacter() {
    Character hero(chosen.name[0], chosen.defense, chosen.attack, chosen.magic, {});
    return hero;
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
        case Key::Enter: {
            if (createSaveOptions[Game::selectedOption] == "Salvar") {
                saveVector[Game::selectedHorizontal].saveToFile(chosenCharacter(), {});

                loadSave(saveVector[Game::selectedHorizontal]);
                Game::player = chosenCharacter();
                Game::currentState = GameState::GAME_MENU;

            } else if (createSaveOptions[Game::selectedOption] == "Deletar") {
                saveVector[Game::selectedHorizontal].deleteSave();
                break;
            } else if (createSaveOptions[Game::selectedOption] == "Voltar") {
                chosen = {};
                custom.name[0] = "";
                Game::currentState = GameState::CREATE_MENU_CHOICE;
            }
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