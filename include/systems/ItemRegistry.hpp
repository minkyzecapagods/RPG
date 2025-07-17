#ifndef ITEMREGISTRY_HPP
#define ITEMREGISTRY_HPP

#include <map>
#include <vector>
#include <string>
#include "entities/Item.hpp"

using namespace std;

class ItemRegistry {
private:
  map<int, Item> itemMap;
  vector<int> unlockedItems;
  string itemsFilePath;
  
public:
  ItemRegistry(const string& itemsFilePath);
  // Carregar todos os itens do arquivo
  void loadItemsFromFile();
  void loadUnlockedItems(int saveId);
  
  // Obter item por ID
  Item getItem(int id);

  // Total de itens
  int getNumItems() const;

  // Retorna a lista de itens desbloqueados
  const vector<int>& getUnlockedItems() const;
  
  // Listar todos os itens (com status de desbloqueio)
  vector<pair<Item, bool>> getAllItems();
  
  // Adicionar novo item ao registro
  void addItem(const Item& item);
  
  // Marcar item como desbloqueado
  void unlockItem(int id);

  // Marcar item como bloqueado
  void lockItem(int id);
  
  // Verificar se item está desbloqueado
  bool isUnlocked(int id);

  int getIdByName(const std::string& name) const;
};

// Declarações externas
void addSavedItensInfo(int index);
extern ItemRegistry items;
void resetItemRegistry();

#endif