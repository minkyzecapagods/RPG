#include "Save.hpp"

#include <fstream>
#include <sstream>

using namespace std;

Save::Save() {
  this -> hero = Character("boyy");
  vector<vector<int>> enemys_inventory(3);
  enemys_inventory[0] = {101, 102, 103};  
  enemys_inventory[1].push_back(201);
  enemys_inventory[2].push_back(202);
  this -> enemys_inventory = enemys_inventory;
  this -> isWritten = true;
}

Character& Save::getHero() { return hero; }

vector<vector<int>>& Save::getEnemysInventory() {return enemys_inventory;}

bool Save::getIsWritten() const { return isWritten; }

bool Save::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return false;

    // Salvar nome e atributos com ponto e vírgula
    out << hero.getName() << "; "
        << hero.getAttack() << "; "
        << hero.getMagic() << "; "
        << hero.getDefense() << ";"
        << "\n";

    // Salvar itens do personagem
    const vector<int>& items = hero.getEquipment();
    for (int id : items) {
        out << id << " ";
    }
    out << "\n";

    // Salvar inventário dos inimigos
    for (const auto& inv : enemys_inventory) {
        for (int item : inv) {
            out << item << " ";
        }
        out << "\n";
    }

    return true;
}