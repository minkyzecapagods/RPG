
#include "helpers/utils.hpp"
#include "core/GameState.hpp"
#include "systems/Save.hpp"
#include "entities/Item.hpp"
#include "systems/ItemRegistry.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

const string greenText = "\033[32;40m";
const string normalText = "\033[37;40m";

int getTerminalWidth() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col; // largura em colunas
}

void adjustWindow() {
    cout << "\033[8;60;100t";  // 50 linhas, 100 colunas
    flush(cout);
}

string repeat(int times, const string& str) {
    string res;
    for (int i = 0; i < times; ++i) {
        res += str;
    }
    return res;
}

string repeat(int times, const string& str, int selected) {
    string res;
    for (int i = 0; i < times; ++i) {
        if (i == selected) res += greenText + str + normalText;
        else res += str;
    }
    return res;
}

void centralPrint(const string& texto) {
    int largura = getTerminalWidth();
    int padding = (largura - texto.size()) / 2;
    if (padding < 0) padding = 0;
    cout << string(padding, ' ') << texto;
}

void centralPrint(const string& texto, int size) {
    int largura = getTerminalWidth();
    int padding = (largura - size) / 2;
    if (padding < 0) padding = 0;
    cout << string(padding, ' ') << texto;
}

void renderScroll(const vector<string>& options) {
    int chars = 25;
    centralPrint("   __________________\n", chars);
    centralPrint("/ \\                  ▏\n", chars);
    centralPrint("\\_,▏                 ▏\n", chars);
    for (size_t i = 0; i < options.size(); ++i) {
        string prefix = (i == Game::selectedOption) ? ("\033[32;40m• " + options[i] + "\033[0;40m") : ("  " + options[i] + "\033[0;40m");
        size_t spaces = 14 - options[i].size();
        centralPrint("   ▏ " + prefix + string(spaces, ' ') + "▏\n", chars);
    }
    centralPrint("   ▏  ________________\n", chars);
    centralPrint("   \\_/________________/\n\n", chars);
}

string formatField(const string& value, int width, char fill) {
    if (value.length() >= (size_t)width) return value;
    return string((width - value.length() + 1) / 2, fill) 
            + value 
            + string((width - value.length()) / 2, fill);
}

string replacePlaceholder(const string& str, const string& placeholder, const string& value) {
    string result = str;
    size_t pos = result.find(placeholder);
    if (pos != std::string::npos) {
        result.replace(pos, placeholder.length(), value);
    }
    return result;
}

string replacePlaceholder(const string& str, initializer_list<pair<string, string>> values) {
    string result = str;
    for (const auto& [placeholder, value] : values) {
        size_t pos = 0;
        while ((pos = result.find(placeholder, pos)) != std::string::npos) {
            result.replace(pos, placeholder.length(), value);
            pos += value.length();
        }
    }
    return result;
}

string getSelectionDisplay(bool isSelected) {
    return isSelected ? 
        greenText + " ↑        ◹◸        ↓ " + normalText :
        " ↑                  ↓ ";
}

vector<string> getRowDataDisplay(vector<Save> saves,int numItems, int selected) {
    vector<string> data = {"", ""};
    string color = "";
    for (int i = 0; i < numItems; i++) {
        string name, totalItems, partialItems;
        if (i == selected) color = greenText;
        else color = normalText;
        if (saves[i].getIsWritten()) {
            data[0] += color + " ↑ " + formatField(saves[i].getHero().getName(), 16, ' ')
             + " ↓ " + normalText;
            data[1] += color + " ↑   Items: " + formatField(to_string(saves[i].getHero().getEquipment().size()), 2, '0') 
            + "/" +
            formatField(to_string(saves[i].getexistingItems()), 2, '0') +
            "   ↓ " + normalText;
        }
        else {
            data[0] += color + " ↑       ----       ↓ " + normalText;
            data[1] += color + " ↑   Items: --/--   ↓ " + normalText;
        }
    }
    return data;
}

vector<string> getRowDataDisplay(vector<pair<Item, bool>> item, int numItems, int selected) {
    vector<string> data = {"", "", ""};
    string color = "";
    for (int i = 0; i < numItems; i++) {
        string name, bonusStr, lockStatus;
        if (i == selected) color = greenText;
        else color = normalText;
        data[0] += color + " ↑ " + formatField(item[i].first.getName(), 16, ' ')
         + " ↓ " + normalText;
        data[1] += color + " ↑     +" + formatField(to_string(item[i].first.getBonus()), 2, '0') 
        + "  " + itemTypeToStat(item[i].first.getType()) +
        "     ↓ " + normalText;
        string status = "     Perdido    ";
        if (items.isUnlocked(item[i].second)) status = "  Conquistado  ";
        data[2] += color + " ↑ " + status + " ↓ " + normalText;
    }
    return data;
}

template <typename T>
void renderGenericList(const vector<T>& data, int selectedIndex) {
    // Dados comuns a todos os tipos
    const int numItems = data.size();
    const int width = 23 * data.size(); // Largura fixa por item

    // Renderizar linha superior
    string topLine = repeat(numItems, " ↑→→→→→→→→→→→→→→→→→→↓ ", selectedIndex);
    centralPrint(topLine + "\n", width);
    
    // Renderizar linha de seleção
    string selectionLine;
    for (int i = 0; i < numItems; ++i) {
        selectionLine += getSelectionDisplay(i == selectedIndex);
    }
    centralPrint(selectionLine + "\n", width);
    
    // Renderizar dados específicos
    vector<string> dataLine = getRowDataDisplay(data, numItems, selectedIndex);
    for (const auto& line : dataLine) centralPrint(line + "\n", width);
    
    // Renderizar linhas inferiores
    centralPrint(repeat(numItems, " ↑                  ↓ ", selectedIndex) + "\n", width);
    centralPrint(repeat(numItems, " ↑→→→→→→→→→→→→→→→→→→↓ ", selectedIndex) + "\n", width);
}

template void renderGenericList<Save>(const vector<Save>&, int selectedIndex);
template void renderGenericList<pair<Item, bool>>(const vector<pair<Item, bool>>&, int selectedIndex);
