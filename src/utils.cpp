
#include "utils.hpp"
#include "GameState.hpp"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

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

string repetir(int vezes, const string& str) {
    string resultado;
    for (int i = 0; i < vezes; ++i) {
        resultado += str;
    }
    return resultado;
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
        string prefix = (i == Game::selectedOption) ? "• " : "  ";
        size_t spaces = 14 - options[i].size();
        centralPrint("   ▏ " + prefix + options[i] + string(spaces, ' ') + "▏\n", chars);
    }
    centralPrint("   ▏  ________________\n", chars);
    centralPrint("   \\_/________________/\n\n", chars);
}