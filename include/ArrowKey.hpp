#ifndef ARROWKEY_HPP
#define ARROWKEY_HPP

enum class Key {
    None,
    Up,
    Down,
    Left,
    Right,
    Backspace,
    Enter,
    Quit
};

struct Charrow {
    char key;
    Key arrowKey;
};

void initKeyboard();
void restoreKeyboard();
Key getArrowKey();
Charrow getCharKey();

#endif // ARROW_KEY_HPP

