#include <string>
#include <vector>
#include <iostream>

#include "helpers/card_render.hpp"
#include "menus/CreateMenu.hpp"
#include "core/GameState.hpp"
#include "helpers/utils.hpp"
    
vector<string> getHeaders() {
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

vector<string> formatCharacterCard(const DefaultCharacter &character) {

    vector<string> result = {
      " .-/|           \\ /           |\\-. ",
      " ||||{NAME}| Ataque: {ATK} |||| ",
      " ||||     {THE}      | Defesa: {DEF} |||| ",
      " ||||{TITLE}| Mana:   {MAG} |||| ",
      " ||||            |            |||| ",
      " ||/============\\|/============\\|| ",
      " `-------------~___------------~'' ",};

    string name = formatField(character.name[0] + character.name[1], 12, ' ');       
    string title = formatField(character.name[3], 12, ' ');

    string atk = formatField(to_string(character.attack), 2, '0');
    string def = formatField(to_string(character.defense), 2, '0');
    string mag = formatField(to_string(character.magic), 2, '0');
    result[1] = replacePlaceholder(result[1], {
    {"{NAME}", name},
    {"{ATK}", atk}
    });
    result[2] = replacePlaceholder(result[2], {
    {"{THE}", character.name[2]},
    {"{DEF}", def}
    });
    result[3] = replacePlaceholder(result[3], {
    {"{TITLE}", title},
    {"{MAG}", mag}
    });
    return result;
}

void renderCharStats(const DefaultCharacter &chosen) {
    int size = chosen.ascii.size();
    vector<string> titles = {"Nome: " + chosen.name[0] + chosen.name[1] + chosen.name[1] + chosen.name[2] + chosen.name[3],
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

void renderCharCustom(const DefaultCharacter &custom) {
    int size = custom.ascii.size();
    vector<string> selected = {"", "", "", "", "", ""};
    if (Game::selectedOption > 1) {
        if (Game::selectedHorizontal == 0) selected[Game::selectedOption - 2] = greenText;
        else selected[Game::selectedOption + 1] = greenText;
    } 
    int remaining = 30 - (custom.attack + custom.defense + custom.magic);
    vector<string> titles = {"Pontos restantes: " + formatField(to_string(remaining), 2, '0'),
                             "Nome: " + custom.name[0],
                             selected[0] + selected[3] + "Atk:  " + normalText +
                             selected[0] + "- "+ normalText + 
                             formatField(to_string(custom.attack), 2, '0') + selected[3] + " +",
                             selected[1] + selected[4] + "Def:  " + normalText + 
                             selected[1] + "- "+ normalText +
                             formatField(to_string(custom.defense), 2, '0') + selected[4] + " +",
                             selected[2] + selected[5] + "Mag:  " + normalText +
                             selected[2] + "- "+ normalText +
                             formatField(to_string(custom.magic), 2, '0') + selected[5] + " +"};
    int j = (size / 2);
    string asciiLine;
    for (int i = 0; i < size; ++i) {
        if (i >= (j - 2) && i <= (j + 2)) {
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

vector<string> getAsciiFrame(const vector<string>& ascii) {
    vector<string> withFrame = {" _______________________ ", "|  ___________________  |"};

    for (const auto& line: ascii) {
        withFrame.push_back("| |" + line + "| |");
    }
    withFrame.push_back("|________________________|");
    return withFrame;
}

void renderItemCard(const pair<Item, bool>& item) {
    cout << "\n";
    string status =  redText + "  PERDIDO";
    if (item.second) status = greenText +"ENCONTRADO";
    centralPrint(status + normalText, 10);
    cout << "\n";
    centralPrint("+" + to_string(item.first.getBonus()) + " " + itemTypeToStat(item.first.getType()));
    cout << "\n";
    centralPrint(item.first.getName());
    cout << "\n\n";
    vector<string> asciiFrame = getAsciiFrame(item.first.getAscii());
    for (const auto& line: asciiFrame) {
        centralPrint(line + "\n", 26);
    }
    cout << "\n\n";
    centralPrint(item.first.getDescription());
    cout << "\n";
    centralPrint("Quest : " + item.first.getQuest());
    cout << "\n";
}