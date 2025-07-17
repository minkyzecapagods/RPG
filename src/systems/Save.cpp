#include "systems/Save.hpp"
#include "helpers/utils.hpp"
#include "core/GameState.hpp"
#include "systems/ItemRegistry.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

vector<Save> saveVector = {Save(), Save(), Save()};
const int numSaves = saveVector.size();

Save::Save() : hero(), currentEnemyIndex(0), isWritten(false) {}

const Character& Save::getHero() const{ return hero; }

int Save::getCurrentEnemyIndex() const { return currentEnemyIndex; }

bool Save::getIsWritten() const { return isWritten; }

bool Save::saveToFile(const Character& hero, const ItemRegistry& registry, const int saveIndex) {
    // Determina índice do save no vetor (por subtração de vetores)
    int index = saveIndex + 1; // +1 porque o vetor começa em 0, mas os saves começam em 1

    if (saveIndex < 0 || saveIndex >= numSaves) {
        cout << "PROBLEMA DE INT: " << index;
        return false;
    }
    
    string filename = "data/saves/save" + to_string(index) + "/save.txt";
    ofstream file(filename);
    if (!file.is_open()) {
      cout << "PROBLEMA DE SAVE";
      return false;
    }
    
    // Salva os dados do personagem
    file << hero.getName() << ";" << hero.getDefense() << ";" 
         << hero.getAttack() << ";" << hero.getMagic() << ";"
         << Game::currentEnemyIndex << ";";

    // Salva equipamentos do herói
    for (size_t i = 0; i < hero.getEquipment().size(); ++i) {
        file << hero.getEquipment()[i];
        if (i != hero.getEquipment().size() - 1)
            file << ",";
    }
    file << "\n";
    
    file << registry.getNumItems() << ";\n";
    
    file.close();

    // Salva os itens do herói em um arquivo separado
    addSavedItensInfo(saveIndex);

    // Atualiza o objeto Save
    saveVector[saveIndex].saveToVector(hero, Game::currentEnemyIndex);
    return true;
}

bool Save::saveToVector(const Character& hero, int enemyIndex)  {
    // Atualiza o objeto Save
    this->hero = hero;
    this->currentEnemyIndex = enemyIndex;
    isWritten = true;

    return true;
}

void loadFromFile() {
    for (int i = 0; i < numSaves; ++i) {
        string filename = "data/saves/save" + to_string(i + 1) + "/save.txt";
        ifstream file(filename);

        if (!file.is_open()) continue;

        try {
            string line;
            // Lê linha do herói
            if (getline(file, line)) {
                stringstream ss(line);
                string name, defense, attack, magic, equipStr, enemyIndexStr;
                getline(ss, name, ';');
                getline(ss, defense, ';');
                getline(ss, attack, ';');
                getline(ss, magic, ';');
                getline(ss, enemyIndexStr, ';');
                getline(ss, equipStr, ';');

                // Validação básica para campos vazios
                if (name.empty() || defense.empty() || attack.empty() || magic.empty() || enemyIndexStr.empty()) {
                    throw invalid_argument("Campo de herói faltando ou save corrompido.");
                }

                vector<int> equipment;
                stringstream equipSS(equipStr);
                string id;
                while (getline(equipSS, id, ',')) {
                    if (!id.empty()) equipment.push_back(stoi(id));
                }

                Character hero(name, stoi(defense), stoi(attack), stoi(magic), equipment);

                // Lê a linha final de contagem de itens (ignora o valor, não é mais usado)
                if (getline(file, line)) {
                    // Apenas lê a linha para manter compatibilidade com saves antigos
                }
                
                saveVector[i].saveToVector(hero, stoi(enemyIndexStr));
            }
        } catch (const exception& e) {
            cerr << "Erro ao carregar o save " << filename << ": " << e.what() << ". O save será ignorado." << endl;
            // Garante que o save seja resetado para um estado vazio e não escrito
            saveVector[i] = Save(); 
        }
        file.close();
    }
}

// Função utilitária para limpar equipamentos inválidos
void removeInvalidEquipment(Character& hero) {
    auto& equipment = hero.getEquipment();
    equipment.erase(
        std::remove_if(equipment.begin(), equipment.end(), [](int itemId) {
            return !items.isUnlocked(itemId);
        }),
        equipment.end()
    );
}

void loadSave(const Save& save, int saveId) {
    items.loadUnlockedItems(saveId); // Primeiro, restaura os itens desbloqueados
    Game::player = save.getHero();   // Depois, restaura o personagem
    removeInvalidEquipment(Game::player); // Limpa equipamentos inválidos
    Game::currentEnemyIndex = save.getCurrentEnemyIndex(); // Atualiza o índice do inimigo
}

bool Save::deleteSave() {
    // Determina índice do save no vetor (por subtração de vetores)
    int index = this - &saveVector[0] + 1; // +1 porque o vetor começa em 0, mas os saves começam em 1
    if (index < 0 || index > numSaves) return false;

    // Reseta o objeto Save
    saveVector[index - 1] = Save();
    isWritten = false;

    // Remove os arquivos correspondentes
    string saveDir = "data/saves/save" + to_string(index) + "/";
    remove((saveDir + "save.txt").c_str());
    remove((saveDir + "saved_items.txt").c_str());

    return true;
}