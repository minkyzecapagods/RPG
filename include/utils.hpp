#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

using namespace std;
std::string repetir(int vezes, const string& str);
void printAsciiCentralizado(const vector<string>& arte);

void renderMenu(const vector<string>& options, int selectedIndex, int width, const string& padding, 
                const vector<string>& borderTop, const vector<string>& borderBottom);

#endif