#include <vector>
#include "function.h"
#include "Question.h"

int main(int argc, char *argv[])
{
    /// Ścieżka do pliku z graczami
    std::string playerDataFile;
    /// Ścieżka do pliku z pytaniami
    std::string gameDataFile;
    /// Zmienna zawierająca nazwę gracza
    std::string playerName;
    /// Vector zawierający wszystkie pytania z pliku
    std::vector<Question> questions;
    /// Koła ratunkowe gracza
    Lifelines lifelines;

    // Sprawdza czy argumenty zostały podane poprawnie, jeśli nie to kończy program
    if (!Arguments(argc, argv, playerDataFile, gameDataFile))
    {
        return 0;
    }
    // Sprawdza czy można otworzyć plik z pytaniami, jeśli tak to wszystkie wczytuje do zmiennje questions
    if (!GameDataInput(gameDataFile, questions))
    {
        return 0;
    }
    // Sprawdza czy mozna poprawnie otworzyc plik z graczami, jeśli tak to pyta o imie gracza
    if (!PlayerDataInput(playerDataFile, playerName))
    {
        return 0;
    }

    int score = 0;
    // Funkcja odpowiada za główną rozgrywkę, zwraca wynik
    score = MainGame(playerName, questions, lifelines);

    if (SaveToFile(playerDataFile, playerName, score))
    {
        return 0;
    }
    return 0;
}
