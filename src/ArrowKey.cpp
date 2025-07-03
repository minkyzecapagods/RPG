#include "ArrowKey.hpp"

#ifdef _WIN32

void initKeyboard() {
    // Não precisa configurar
}

void restoreKeyboard() {
    // Não precisa restaurar
}

Key getArrowKey() {
    if (_kbhit()) {
        int c = _getch();
        if (c == 224) {
            int code = _getch();
            if (code == 72) return Key::Up;
            if (code == 80) return Key::Down;
            if (code == 75) return Key::Left;
            if (code == 77) return Key::Right;
        } else if (c == ' ') return Key::Enter;
        else if (c == 'q') return Key::Quit;
    }
    return Key::None;
}

#else // POSIX

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

#endif
