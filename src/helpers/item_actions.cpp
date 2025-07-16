#include "helpers/item_actions.hpp"
#include "core/GameState.hpp"
#include "systems/ItemRegistry.hpp"
#include <algorithm>

// Equipa um item pelo ID
bool equipItem(int itemId) {
    if (!items.isUnlocked(itemId)) return false;
    Item item = items.getItem(itemId);
    auto& equipment = Game::player.getEquipment();
    // Verifica se já existe um item desse tipo equipado
    for (size_t i = 0; i < equipment.size(); ++i) {
        if (items.getItem(equipment[i]).getType() == item.getType()) {
            // Desequipa o item antigo (apenas remove do vetor)
            equipment[i] = itemId;
            return true;
        }
    }
    // Se não existe, adiciona
    equipment.push_back(itemId);
    return true;
}

// Desequipa o item de um tipo específico
bool unequipItem(ItemType type) {
    auto& equipment = Game::player.getEquipment();
    for (auto it = equipment.begin(); it != equipment.end(); ++it) {
        if (items.getItem(*it).getType() == type) {
            equipment.erase(it);
            return true;
        }
    }
    return false;
}

// Descarta um item do inventário
bool discardItem(int itemId) {
    if (!items.isUnlocked(itemId)) return false;
    // Se estiver equipado, desequipa
    auto& equipment = Game::player.getEquipment();
    auto it = std::find(equipment.begin(), equipment.end(), itemId);
    if (it != equipment.end()) {
        equipment.erase(it);
    }
    // Remove do inventário
    items.lockItem(itemId);
    // Salva a mudança imediatamente
    addSavedItensInfo(Game::currentSave.index);
    return true;
} 