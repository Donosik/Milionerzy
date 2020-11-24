#include <iostream>
#include "function.h"

void Arguments(int argc, char *argv[])
{
    if (argc < 5)
    {
        std::cout << "Program do poprawnego dzialania wymaga uruchomienia z odpowiednimi przelacznikami:" << std::endl;
        std::cout << "-i plik wejsciowy z kategoriami i haslami" << std::endl;
        std::cout << "-w plik zawierajacy statystyki graczy" << std::endl;
    }
    for (int i = 1; i < argc; i += 2)
    {
        if ((std::string) argv[i] == "-i")
        {
            std::string playerDataFile=argv[i+1];
            std::cout << argv[i + 1] << std::endl;
        }
        else if ((std::string) argv[i] == "-w")
        {
            std::string gameDataFile=argv[i+1];
            std::cout << argv[i + 1] << std::endl;
        }
    }
}