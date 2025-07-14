#ifndef CARD_RENDER_HPP
#define CARD_RENDER_HPP

#include <vector>
#include <string>

#include "menus/CreateMenu.hpp"
#include "entities/Item.hpp"

using namespace std;

vector<string> formatCharacterCard(const DefaultCharacter &character);
vector<string> getHeaders();

void renderCharStats(const DefaultCharacter &chosen);
void renderCharCustom(const DefaultCharacter &custom);
void renderItemCard(const pair<Item, bool>& item);

#endif 