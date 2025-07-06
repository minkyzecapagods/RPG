#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

using namespace std;

#ifdef _WIN32
  #include <windows.h>
#else
  #include <sys/ioctl.h>
  #include <unistd.h>
  #include <cstdlib>
#endif

std::string repetir(int vezes, const string& str);

int getTerminalWidth();

void centralPrint(const string& texto);
void centralPrint(const string& texto, int size);
void renderScroll(const vector<string>& options);
void adjustWindow(); 
#endif