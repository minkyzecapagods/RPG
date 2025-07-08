#include <vector>
#include <string>
#include <iostream>

#include "CreateMenu.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"
#include "utils.hpp"
#include "Save.hpp"

using namespace std;

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

vector<DefaultCharacter> defaults = {tank, healer, assassin};

DefaultCharacter chosen;

vector<string> defaultChar = {
" .-/|           \\ /           |\\-. ",
" ||||{NAME}| Ataque: {ATK} |||| ",
" ||||     {THE}      | Defesa: {DEF} |||| ",
" ||||{TITLE}| Mana:   {MAG} |||| ",
" ||||            |            |||| ",
" ||/============\\|/============\\|| ",
" `-------------~___------------~'' ",};

vector<string> createChar = 
{
"  (`\\ \\_..-~~-._   _.-~--.._       ",
"   `=\\/\\        \\ /        \\\\      ",
"    `=\\/         V          \\\\     ",
"     //\\_.-~-._  |  _.-~-..__\\\\   ",
"    //) (--~~._\\ | /_.~~--..._\\\\   ",
"   =(_INK_)====\\\\|//============   ",
"                                   ",
};

vector<string> createSaveOptions = {
  "Salvar",
  "Deletar",
  "Voltar",
};

vector<string> getStrs() {
    string sel1 = " ", sel2 = " ", sel3 = " ", sel4 = " ", sel5 = " ";
    string c1 = normalText, c2 = normalText, c3 = normalText, c4 = normalText, c5 = normalText;

    if (Game::selectedOption == 0) sel1 = "▾", c1 = greenText;
    if (Game::selectedOption == 1) sel2 = "▾", c2 = greenText;
    if (Game::selectedOption == 2) sel3 = "▾", c3 = greenText;
    if (Game::selectedOption == 3) sel4 = "▾", c4 = greenText;
    if (Game::selectedOption > 3) sel5 = "▷", c5 = greenText;

    string str1 = c1 + "    ____________ " + sel1 + " ___________    " + c2 + "     ____________ " + sel2 + " ___________     " + normalText;
    string str2 = c3 + "    ____________ " + sel3 + " ___________    " + c4 + "                  " + sel4 + "                 " + normalText;
    string str3 = c5 + "                              " + sel5 + " Voltar                                " + normalText;
    
    return {str1, str2, str3};
}

vector<string> formatCharacterCard(DefaultCharacter character) {
    vector<string> result = defaultChar;
    
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

    string sel1 = "", sel2 = "", sel3 = "", sel4 = "", sel5 = "";
    if (Game::selectedOption == 0) sel1 = greenText;
    if (Game::selectedOption == 1) sel2 = greenText;
    if (Game::selectedOption == 2) sel3 = greenText;
    if (Game::selectedOption == 3) sel4 = greenText;
    if (Game::selectedOption > 3) sel5 = greenText;
    
    system(CLEAR_COMMAND);

    cout << "\n\n";
    centralPrint(sel1 + str[0] + normalText +"\n", chars); 
    for (int i = 0; i < 7; i++) centralPrint(sel1 + frstCard[i] + normalText +
                                             sel2 + scdCard[i] + normalText + "\n", chars);
    cout << "\n\n";
    centralPrint(sel3 + str[1] + normalText + "\n", chars);
    for (int i = 0; i < 7; i++) centralPrint(sel3 + trdCard[i] + normalText +
                                             sel4 + createChar[i] + normalText + "\n", chars);
    cout << "\n\n";
    centralPrint(sel5 + str[2] + "\n", chars);
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
            } else if (Game::selectedOption > 3) {
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