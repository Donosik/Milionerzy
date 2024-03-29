#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <random>
#include "Question.h"
#include "Lifelines.h"

/// Funkcja, która przyjmuje parametry programu i wstawia do struktury FilesPath ścieżki do odpowiednich plików
/// @param argc Ilość argumentów, które przyjmuje program
/// @param argv Tablica argumentów, które przyjmuje program
/// @param playerDataFile Ścieżka do pliku z graczami, zwracana przez referencję
/// @param gameDataFileŚcieżka do pliku z pytaniami, zwracana przez referencję
/// @return Zwraca false, gdy któryś z argumentów jest niepoprawny lub liczba argumentów jest mniejsza niż oczekiwana
bool Arguments(int argc, char *argv[], std::string &playerDataFile, std::string &gameDataFile);

/// Funkcja sprawdza czy plik z pytaniami jest poprawny, jeśli tak to zapisuje dane do vectora questions
/// @param gameDataFile Ścieżka do pliku z pytaniami
/// @param questions Vector z wszystkimi pytaniami wczytanymi z pliku razem z odpowiedziami
/// @return Zwraca false, gdy plik z pytaniami jest niepoprawny lub gdy odpowiedź do pytania została określona w
/// błędny sposób
bool GameDataInput(const std::string &gameDataFile, std::vector<Question> &questions);

/// Funckja pyta gracza o nazwę
/// @return Zwraca nazwę gracza
std::string GetPlayerName();

/// Funkcja pobiera dane z pliku z graczami i sprawdza czy już grał
/// @param playerDataFile Ścieżka do pliku z graczami
/// @param playerName Nazwa gracza, jest zwracana przez rekurencję
bool PlayerDataInput(const std::string &playerDataFile, std::string &playerName);

/// Funkcja odpowiadająca za zarządzanie właściwą częścią gry
/// @param playerName Nazwa gracza uczestniczącego w grze
/// @param questions Wektor wszystkich pytań wraz z odpowiedziami
/// @param lifelines Struktura, która pokazuje ile kół pomocniczych zostało jeszcze graczowi
int MainGame(std::string playerName, std::vector<Question> questions, Lifelines lifelines);

/// Funckja odpowiada za zarządzanie kołami ratunkowymi
/// @@param playerName Nazwa gracza
/// @param question Pytanie, do którego jest użyte koło ratunkowe
/// @param lifelines Jakie koła ratunkowe są jeszcze dostępne dla gracza
char Help(std::string playerName, Question question, Lifelines &lifelines, int whichQuestion);

/// Funkcja pokazująca pytanie i możliwe odpowiedzi
/// @param question Pytanie, które ma być wyświetlone
/// @param whichQuestion numer wyświetlanego pytania
/// @return Odpowiedź na zadane pytanie
char ShowQuestion(Question question, int whichQuestion);

/// Funkcja zapisuje wynik gracza, jesli juz gral sprawdza czy to był lepszy wynik
/// @param filePath Ścieżka do pliku do zapisu
/// @param playerName Nazwa gracza grającego
/// @param playerScore Wynik gracza grajacego
/// @return Funkcja zwraca false, w przypadku, gdy nie moze otworzyc pliku
bool SaveToFile(std::string filePath, std::string playerName, int playerScore);

/// Funckja zwracająca losowa wartość z zakresu od min do max
/// @param min Wartość minimalna jaka może zostać wylosowana
/// @param max Wartość maksymalna jaka może zostać wylosowana
/// @return Losowa wartość z podanego zakresu jako liczba całkowita
int Random(int min, int max);

#endif FUNCTION_H
