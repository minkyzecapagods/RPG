#include <iostream>
#include <vector>
#include <string>

#include "menus/GameMenu.hpp"
#include "core/GameState.hpp"
#include "core/ArrowKey.hpp"
#include "helpers/utils.hpp"

using namespace std;

vector<string> gameMenuOptions = {
    "Batalhe",
    "Itens",
    "Voltar",
};


void renderGameMenu() {
    vector<vector<string>> title = {{
      "                                                              ",
      " ▄█▀▀▀█▄█                                                     ",
      "▄██    ▀█                                                     ",
      "▀███▄    ▄█▀██▄  ▄██▀███▀███  ▀███   ▄▄█▀██ ▄█▀██▄ ▀███▄███   ",
      "  ▀█████▄█   ██ ▄█▀   ██  ██    ██  ▄█▀   ███   ██   ██▀ ▀▀   ",
      "▄     ▀██▄█████ ██    ██  ██    ██  ██▀▀▀▀▀▀▄█████   ██       ",
      "██     ███   ██ ██▄   ██  ██    ██  ██▄    ▄█   ██   ██       ",
      "█▀█████▀▀████▀██▄▀██████  ▀████▀███▄ ▀█████▀████▀██▄████▄     ",
      "                      ██                                      ",
      "                   ▄████▄                                     "},
    { "                                              ",
      " ▄██▀██▄▀███  ▀███      ▄██▀███ ▄▄█▀██▀███▄███",
      "██▀   ▀██ ██    ██      ██   ▀▀▄█▀   ██ ██▀ ▀▀",
      "██     ██ ██    ██      ▀█████▄██▀▀▀▀▀▀ ██    ",
      "██▄   ▄██ ██    ██      █▄   ████▄    ▄ ██    ",
      " ▀█████▀  ▀████▀███▄    ██████▀ ▀█████▀████▄  "},
    { "                                                                                 ",
      "                                                          ▀███           ▄█▀▀▀█▄ ",
      "                                                            ██           ██▀  ▀█▄",
      "   ▄██▀███▄█▀██▄  ▄██▀███▀███  ▀███   ▄▄█▀██ ▄█▀██▄    ▄█▀▀███   ▄██▀██▄      ▄██",
      "   ██   ▀▀█   ██ ▄█▀   ██  ██    ██  ▄█▀   ███   ██  ▄██    ██  ██▀   ▀██  ████▀ ",
      "   ▀█████▄▄█████ ██    ██  ██    ██  ██▀▀▀▀▀▀▄█████  ███    ██  ██     ██  ██    ",
      "   █▄   ███   ██ ██▄   ██  ██    ██  ██▄    ▄█   ██  ▀██    ██  ██▄   ▄██  ▄▄    ",
      "   ██████▀████▀██▄▀██████  ▀████▀███▄ ▀█████▀████▀██▄ ▀████▀███▄ ▀█████▀   ██    ",
      "                       ██                                                        ",
      "                    ▄████▄                                                       "}};
                  
    
    for (const auto& subtitle : title) {
        int size = subtitle[0].size();
        for (const auto& line : subtitle) {
            centralPrint(line + "\n", size);
        }
    }
    cout << "\n";
    renderScroll(gameMenuOptions);
    centralPrint("Use setas para mover, espaço para selecionar, pressione q para sair.\n");
}

void handleGameMenuInput() {
    Key key = getArrowKey();

    switch (key) {
        case Key::Up:
            Game::selectedOption = (Game::selectedOption - 1 + gameMenuOptions.size()) % gameMenuOptions.size();
            break;
        case Key::Down:
            Game::selectedOption = (Game::selectedOption + 1) % gameMenuOptions.size();
            break;
        case Key::Enter: {
            if (gameMenuOptions[Game::selectedOption] == "Batalhe") {
                Game::currentState = GameState::INITIALIZE_BATTLE; 
            } else if (gameMenuOptions[Game::selectedOption] == "Itens") {
                cout << "Itens menu ainda não implementado.\n";
            } else if (gameMenuOptions[Game::selectedOption] == "Voltar") {
                Game::currentSave.saveToFile(Game::player, {{}}); // Salva o jogo atual antes de voltar
                resetItemRegistry(); // Reseta o registro de itens ao voltar ao menu principal  
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