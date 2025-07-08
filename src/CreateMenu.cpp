#include <vector>
#include <string>
#include <iostream>

#include "CreateMenu.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"
#include "utils.hpp"
#include "Save.hpp"

using namespace std;

vector<string> result = {
    " .-/|           \\ /           |\\-. ",
    " ||||{NAME}| Ataque: {ATK} |||| ",
    " ||||     {THE}      | Defesa: {DEF} |||| ",
    " ||||{TITLE}| Mana:   {MAG} |||| ",
    " ||||            |            |||| ",
    " ||/============\\|/============\\|| ",
    " `-------------~___------------~'' ",};
    

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
vector<DefaultCharacter> defaults = {tank, healer, assassin};

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

vector<string> getStrs() {
    vector<string> selected = {" ", " ", " ", " ", " "};
    vector<string> colorSelected = {normalText, normalText, normalText, normalText, normalText};
    if (Game::selectedOption < 4) selected[Game::selectedOption] = "▾", colorSelected[Game::selectedOption] = greenText;
    else selected[4] = "▷", colorSelected[4] = greenText;

    string str1 = colorSelected[0] + "    ____________ " + selected[0] +
                  " ___________    " + colorSelected[1] + 
                  "     ____________ " + selected[1] + " ___________     " + normalText;

                  
    string str2 = colorSelected[2] + "    ____________ " + selected[2] + 
                  " ___________    " + colorSelected[3] + 
                  "                  " + selected[3] + "                 " + normalText;

    string str3 = colorSelected[4] + "                              " + 
                  selected[4] + " Voltar" + normalText;
    

    return {str1, str2, str3};
}

vector<string> formatCharacterCard(DefaultCharacter character) {
    string name = formatField(character.name[0], 12, ' ');       
    string title = formatField(character.name[2], 12, ' ');
    string atk = formatField(to_string(character.attack), 2, '0');
    string def = formatField(to_string(character.defense), 2, '0');
    string mag = formatField(to_string(character.magic), 2, '0');
    result[1] = replacePlaceholder(result[1], {
    {"{NAME}", name},
    {"{ATK}", atk}
    });
    result[2] = replacePlaceholder(result[2], {
    {"{THE}", character.name[1]},
    {"{DEF}", def}
    });
    result[3] = replacePlaceholder(result[3], {
    {"{TITLE}", title},
    {"{MAG}", mag}
    });
    return result;
}

void renderCharacterChoice(){
    int chars = 71;
    vector<string> str = getStrs(),
                   frstCard = formatCharacterCard(defaults[0]),
                   scdCard = formatCharacterCard(defaults[1]),
                   trdCard = formatCharacterCard(defaults[2]);

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
                chosen = defaults[Game::selectedOption];
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

void renderCharStats() {
    int size = chosen.ascii.size();
    vector<string> titles = {"Nome: " + chosen.name[0] + "  " + chosen.name[1] + "  " + chosen.name[2],
                             "Atk:  " + formatField(to_string(chosen.attack), 2, '0'),
                             "Def:  " + formatField(to_string(chosen.defense), 2, '0'),
                             "Mag:  " + formatField(to_string(chosen.magic), 2, '0')};
    int j = (size / 2);
    string asciiLine;
    for (int i = 0; i < size; ++i) {
        if (i >= (j - 2) && i <= (j + 1)) {
            string spcs;
            if (chosen.ascii[i].size() > 34) spcs = " ";
            else spcs = string(34 - chosen.ascii[i].size(), ' ');
            asciiLine = chosen.ascii[i] + spcs + titles[i - (j - 2)];
        } else {
            asciiLine = chosen.ascii[i];
        }
        centralPrint(asciiLine + "\n", 41);
    }
    cout << "\n";
}

void renderCreateSaveMenu() {
  system(CLEAR_COMMAND);
  renderCharStats();
  renderSaves(Game::selectedHorizontal);
  renderScroll(createSaveOptions);
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

void renderCharCustom() {
    int size = custom.ascii.size();
    vector<string> selected = {"", "", "", "", "", ""};
    if (Game::selectedOption > 1) {
        if (Game::selectedHorizontal == 0) selected[Game::selectedOption - 2] = greenText;
        else selected[Game::selectedOption + 1] = greenText;
    } 
    vector<string> titles = {"Nome: " + custom.name[0],
                             "Atk:  " + selected[0] + "- "+ normalText + 
                             formatField(to_string(custom.attack), 2, '0') + selected[3] + " +",
                             "Def:  " + selected[1] + "- "+ normalText +
                             formatField(to_string(custom.defense), 2, '0') + selected[4] + " +",
                             "Mag:  " + selected[2] + "- "+ normalText +
                             formatField(to_string(custom.magic), 2, '0') + selected[5] + " +"};
    int j = (size / 2);
    string asciiLine;
    for (int i = 0; i < size; ++i) {
        if (i >= (j - 2) && i <= (j + 1)) {
            string spcs;
            if (custom.ascii[i].size() > 34) spcs = " ";
            else spcs = string(34 - custom.ascii[i].size(), ' ');
            asciiLine = custom.ascii[i] + spcs + titles[i - (j - 2)];
        } else {
            asciiLine = custom.ascii[i];
        }
        centralPrint(asciiLine + normalText + "\n", 41);
    }
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

void renderCharCreation() {
    system(CLEAR_COMMAND);
    renderCharCustom();
    cout << "\n";
    centralPrint("Distribua 30 pontos de atributo da forma que desejar\n", 51);
    renderScroll(createCustomOptions);
}

void handleCharCreation() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 1 + 5) % 5;
            Game::selectedHorizontal = 0;
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % 5;
            Game::selectedHorizontal = 0;
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
            } else {
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