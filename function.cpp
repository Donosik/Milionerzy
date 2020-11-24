#include "function.h"

bool Arguments(int argc, char *argv[], std::string &playerDataFile, std::string &gameDataFile)
{
    if (argc < 5)
    {
        std::cout << "Program do poprawnego dzialania wymaga uruchomienia z odpowiednimi przelacznikami:" << std::endl;
        std::cout << "-i plik wejsciowy z kategoriami i haslami" << std::endl;
        std::cout << "-w plik zawierajacy statystyki graczy" << std::endl;
        return false;
    }
    for (int i = 1; i < argc; i += 2)
    {
        if ((std::string) argv[i] == "-i")
        {
            gameDataFile = argv[i + 1];
        }
        else if ((std::string) argv[i] == "-w")
        {
            playerDataFile = argv[i + 1];
        }
    }
    return true;
}

bool GameDataInput(const std::string gameDataFile, std::vector<Question> &questions)
{
    std::ifstream file(gameDataFile);
    if (!file.is_open())
    {
        return false;
    }
    std::string line;
    Question question;
    int i = 0;
    while (std::getline(file, line))
    {
        if (i % 6 == 0)
        {
            question.question = line;
        }
        else if (i % 6 == 5)
        {
            int x = std::stoi(line);
            if (x < 0 || x > 4)
            {
                std::cout << "W pliku z pytaniami niepoprawnie okresloną odpowiedz do pytania nr " << ((i - 5) / 6) + 1
                          << std::endl;
                return false;
            }
            question.correctAnswer = x;
            questions.push_back(question);
        }
        else
        {
            int j = i % 6 - 1;
            question.answers[j] = line;
        }
        i++;
    }
    return true;
}

void Debug(std::vector<Question> &question)
{
    std::cout << "Debug!" << std::endl;
    for (auto &x:question)
    {
        std::cout << x.question << std::endl;
        std::cout << x.answers[0] << std::endl;
        std::cout << x.answers[1] << std::endl;
        std::cout << x.answers[2] << std::endl;
        std::cout << x.answers[3] << std::endl;
        std::cout << x.correctAnswer << std::endl;
    }
}