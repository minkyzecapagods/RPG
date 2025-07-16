#ifndef ITEMREGISTRY_HPP
#define ITEMREGISTRY_HPP

#include <map>
#include <vector>
#include <string>
#include "entities/Item.hpp"

using namespace std;

class ItemRegistry;
class ItemRegistry {
private:
  map<int, Item> itemMap;
  vector<int> unlockedItems;
  string itemsFilePath;
  
public:
  ItemRegistry(const string& itemsFilePath);
  // Carregar todos os itens do arquivo
  void loadItemsFromFile();
  
  // Obter item por ID
  Item getItem(int id);

  // Atualiza o filepath
  void setItemsFilePath(const string& newFilePath);

  // Total de itens
  int getNumItems() const;

  // Para atualizar a lista de itens desbloqueados de acordo com o save
  void setUnlockedItems(const vector<int>& unlocked);
  
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

  bool saveItemsToFile();

  int getIdByName(const std::string& name) const;
};

void addSavedItensInfo(int index, const vector<int> &equipment);

extern ItemRegistry items;

void resetItemRegistry();

#endif