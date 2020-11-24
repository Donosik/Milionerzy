#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include "structures.h"

/// Funkcja, która przyjmuje parametry programu i wstawia do struktury FilesPath ścieżki do odpowiednich plików
/// @param argc Ilość argumentów, które przyjmuje program
/// @param argv Tablica argumentów, które przyjmuje program
/// @param filesPath Zmienna, która jest strukturą, w której znajdują się ścieżki do odpowiednich plików
bool Arguments(int argc, char *argv[], std::string &playerDataFile, std::string &gameDataFile);

bool GameDataInput(const std::string gameDataFile, std::vector<Question> &questions);

void Debug(std::vector<Question> &question);

#endif FUNCTION_H
