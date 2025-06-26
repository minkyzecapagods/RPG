#ifndef ARROWKEY_HPP
#define ARROWKEY_HPP

#ifdef _WIN32
  #include <conio.h>
#else
  #include <termios.h>
  #include <unistd.h>
#endif

enum class Key {
    None,
    Up,
    Down,
    Left,
    Right,
    Enter,
    Quit
};

void initKeyboard();
void restoreKeyboard();
Key getArrowKey();

#endif // ARROW_KEY_HPP

