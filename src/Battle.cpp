#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "Battle.hpp"
#include "GameState.hpp"
#include "ArrowKey.hpp"
#include "Character.hpp"
#include "utils.hpp"

using namespace std;

//teste
vector<string> n = {
"              _,-'|",
"           ,-'._  |",
" .||,      |####\\ |",
"\\.`',/     \\####| |",
"= ,. =      |###| |",
"/ || \\    ,-'\\#/,'`.",
"  ||     ,'   `,,. `.",
"  ,|____,' , ,;' \\| |",
" (3|\\    _/|/'   _| |",
"  ||/,-''  | >-'' _,\\",
"  ||'      ==\\ ,-'  ,'",
"  ||       |  V \\ ,|",
"  ||       |    |` |",
"  ||       |    |   \\",
"  ||       |    \\    \\",
"  ||       |     |    \\",
"  ||       |      \\_,-'",
"  ||       |___,,--')_\\",
"  ||         |_|   ccc/",
"  ||        ccc/",
"  ||"};

Battle::Battle(Character player, Character enemy){
    this->player = player;
    this->enemy = enemy;
};

void Battle::playerTurn() {
    player.action(Game::selectedOption, &enemy);
}

void Battle::enemyTurn() {
    enemy.action(&player);
}

void Battle::checkBattleStatus() {
    if (enemy.getHp() <= 0) {
        setBattleOver();
        cout << "Você venceu a batalha!" << endl;
    } else if (player.getHp() <= 0) {
        setBattleOver();
        cout << "Você foi derrotado!" << endl;
    }
}
