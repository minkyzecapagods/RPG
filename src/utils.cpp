
#include "utils.hpp"
#include "GameState.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <map>

using namespace std;

const string greenText = "\033[32;40m";
const string normalText = "\033[37;40m";

#ifdef _WIN32

int getTerminalWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
} 

void adjustWindow() {
        // SOLUÇÃO WINDOWS
    HWND console = GetConsoleWindow();
    
    // Sair do modo tela cheia
    ShowWindow(console, SW_RESTORE);
    
    // Configurar tamanho e posição
    int width = 800;
    int height = 600;
    
    RECT rect;
    GetWindowRect(console, &rect);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int x = (screenWidth - width) / 2;
    int y = (screenHeight - height) / 2;
    
    MoveWindow(console, x, y, width, height, TRUE);
    
}

#else

int getTerminalWidth() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col; // largura em colunas
}

void adjustWindow() {
    cout << "\033[8;60;100t";  // 50 linhas, 100 colunas
    flush(cout);
}

#endif

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
