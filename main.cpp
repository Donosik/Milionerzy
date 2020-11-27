#include <vector>
#include "function.h"
#include "structures.h"

int main(int argc, char *argv[])
{
    std::string playerDataFile; /// Ścieżka do pliku z graczami
    std::string gameDataFile; /// Ścieżka do pliku z pytaniami
    std::string playerName; /// Zmienna zawierająca nazwę gracza
    std::vector<Question> questions; /// Vector zawierający wszystkie pytania z pliku
    Lifelines lifelines; /// Koła ratunkowe gracza

    // Sprawdza czy argumenty zostały podane poprawnie, jeśli nie to kończy program
    if (!Arguments(argc, argv, playerDataFile, gameDataFile))
    {
        return 0;
    }
    //
    if (!GameDataInput(gameDataFile, questions))
    {
        return 0;
    }
    // Sprawdza czy mozna poprawnie otworzyc plik z graczami, jeśli tak to pyta o imie gracza
    if (!PlayerDataInput(playerDataFile, playerName))
    {
        return 0;
    }
    MainGame(playerName,questions,lifelines);
    return 0;
}
