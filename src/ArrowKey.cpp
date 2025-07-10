#include "ArrowKey.hpp"

#include <termios.h>
#include <unistd.h>
#include <cctype>
#include <string>

static struct termios _orig_termios;

void initKeyboard() {
    tcgetattr(STDIN_FILENO, &_orig_termios);
    termios raw = _orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void restoreKeyboard() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &_orig_termios);
}

Key getArrowKey() {
    char c;
    if (read(STDIN_FILENO, &c, 1) != 1) return Key::None;
    switch (c) {
        case '\x1B': {
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) != 1) return Key::None;
            if (read(STDIN_FILENO, &seq[1], 1) != 1) return Key::None;
            if (seq[0] == '[') {
                if (seq[1] == 'A') return Key::Up;
                if (seq[1] == 'B') return Key::Down;
                if (seq[1] == 'C') return Key::Right;
                if (seq[1] == 'D') return Key::Left;
            }
            return Key::None;
        }
        case ' ': return Key::Enter;
        case 'q': return Key::Quit;
        default: return Key::None;
    }
}

bool isValidChar(char c) {
    // Verifica se é alfanumérico (letras ou números)
    if(std::isalnum(c)) return true;
    
    // Lista negra de caracteres proibidos
    const std::string forbiddenChars = "\\'\"";
    
    // Verifica se o caractere está na lista negra
    return forbiddenChars.find(c) == std::string::npos;
}


Charrow getCharKey() {
    char c;
    if (read(STDIN_FILENO, &c, 1) != 1) return {'\0', Key::None}; // Retorna nulo se não leu nada
    switch (c){
    case '\x7F': return {'\0', Key::Backspace};
    case '\b': return {'\0', Key::Backspace};
    case '\x1B': {
        char seq[2];
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return {'\0', Key::None};
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return {'\0', Key::None};
        if (seq[0] == '[') {
            if (seq[1] == 'A') return {'\0', Key::Up};
            if (seq[1] == 'B') return {'\0', Key::Down};
            if (seq[1] == 'C') return {'\0', Key::Right};
            if (seq[1] == 'D') return {'\0', Key::Left};
        }
        break;
    } 
    case 'q': return {'q', Key::Quit};
    case ' ': return {' ', Key::Enter};
    case '\n': return {'\0', Key::None};
    default: break;
    }
    
    if (isValidChar(c)) return {c, Key::None};
    return {'\0', Key::None}; // Retorna nulo se não for válido ou não leu nada
}