#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

template <typename T>
void renderGenericList(const vector<T>& data, int selectedIndex);

template <typename T>
vector<vector<T>> separateInVectorsOf3(const vector<T>& data);

extern const string greenText;
extern const string redText;
extern const string normalText;

string repeat(int times, const string& str);
string repeat(int times, const string& str, int selected);

int getTerminalWidth();

void centralPrint(const string& texto);
void centralPrint(const string& texto, int size);
void renderScroll(const vector<string>& options);
void adjustWindow();
string replacePlaceholder(const string& str, const string& placeholder, const string& value);
string replacePlaceholder(const string& str, initializer_list<pair<string, string>> values);
string formatField(const string& value, int width, char fill);

#endif