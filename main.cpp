#include <vector>
#include "function.h"
#include "structures.h"

int main(int argc, char *argv[])
{
    std::string playerDataFile;
    std::string gameDataFile;
    std::vector<Question> questions;
    if(!Arguments(argc, argv, playerDataFile, gameDataFile))
    {
        return 0;
    }
    if(!GameDataInput(gameDataFile,questions))
    {
        return 0;
    }
    Debug(questions);
    return 0;
}
