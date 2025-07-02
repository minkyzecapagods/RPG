
#include "utils.hpp"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

string repetir(int vezes, const string& str) {
    string resultado;
    for (int i = 0; i < vezes; ++i) {
        resultado += str;
    }
    return resultado;
}

void printAsciiCentralizado(const vector<string>& arte) {
  size_t maior = 0;
  for (const auto& s : arte) {
    if (s.length() > maior) maior = s.length();
    }
  int espacos = 25 - (maior / 2);
  for (const auto& s : arte) cout << string(espacos, ' ') << s << endl;
  return;
}