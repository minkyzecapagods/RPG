#ifndef ITEM_ACTIONS_HPP
#define ITEM_ACTIONS_HPP

#include "entities/Item.hpp"
#include <vector>

// Equipa um item pelo ID. Retorna true se sucesso.
bool equipItem(int itemId);
// Desequipa o item de um tipo específico. Retorna true se sucesso.
bool unequipItem(ItemType type);
// Descarta um item do inventário pelo ID. Retorna true se sucesso.
bool discardItem(int itemId);

#endif // ITEM_ACTIONS_HPP 