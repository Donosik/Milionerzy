#include "function.h"

bool Arguments(int argc, char *argv[], std::string &playerDataFile, std::string &gameDataFile)
{
    if (argc < 5) // Sprawdza czy liczba argumentów jest mniejsza niż 5, wtedy zatrzymuje aplikacje
    {
        std::cout << "Program do poprawnego dzialania wymaga uruchomienia z odpowiednimi przelacznikami:" << std::endl;
        std::cout << "-i plik wejsciowy z kategoriami i haslami" << std::endl;
        std::cout << "-w plik zawierajacy statystyki graczy" << std::endl;
        return false;
    }
    // Pętla, która przypisuje do zmiennych ścieżki do poszczególnych plików
    for (int i = 1; i < argc; i += 2)
    {
        // Sprawdza czy przełącznik się zgadza i przypisuje odpowiedni plik do zmiennej
        if ((std::string) argv[i] == "-i")
        {
            gameDataFile = argv[i + 1];
        }
            // Sprawdza czy przełącznik się zgadza i przypisuje odpowiedni plik do zmiennej
        else if ((std::string) argv[i] == "-w")
        {
            playerDataFile = argv[i + 1];
        }
    }
    return true;
}

bool GameDataInput(const std::string &gameDataFile, std::vector<Question> &questions)
{
    std::ifstream file(gameDataFile);
    // Sprawdza czy plik został poprawnie otwarty, jeśli nie zatrzymuje aplikacje
    if (!file.is_open())
    {
        std::cout << "Nie mozna otworzyc pliku z pytaniami, program zostanie zatrzymany!" << std::endl;
        return false;
    }

    std::string line;
    Question question;
    int i = 0;
    // Przechodzi po kolei przez plik po czym przypisuje odpowiednie dane do nowej struktury Question. Na końcu
    // każdego pytania dodaje zmienną question do Vectora zawierającego wszystkie pytania
    while (std::getline(file, line))
    {
        if (i % 6 == 0)
        {
            question.question = line;
        }
        else if (i % 6 == 5)
        {
            char x;
            std::stringstream str(line);
            str >> x;
            // Sprawdza czy poprawna odpowiedz do pytania jest w poprawnym zakresie i formacie
            if ((int) x < 65 || (int) x > 68)
            {
                std::cout << "W pliku z pytaniami niepoprawnie okresloną odpowiedz do pytania nr " << ((i - 5) / 6) + 1
                          << std::endl;
                return false;
            }
            question.correctAnswer = x;
            questions.push_back(question); // Dodaje zmiennej lokalnej question do głównego vectora
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

std::string GetPlayerName()
{
    std::string playerName;
    std::cout << "Witaj w Milionerach!" << std::endl;
    std::cout << "Podaj swoja nazwe: ";
    std::cin >> playerName;
    return playerName;
}

bool PlayerDataInput(const std::string &playerDataFile, std::string &playerName)
{
    std::ifstream file(playerDataFile);
    // Sprawdza czy plik z graczami może zostać poprawnie otwarty
    if (!file.is_open())
    {
        std::cout << "Nie można otworzyc pliku z danymi graczy, program zostanie zatrzymany!" << std::endl;
        return false;
    }

    playerName = GetPlayerName();
    std::string line;
    // Pętla pobiera wszystkich graczy z pliku i sprawdza czy dany gracz już grał, czy to jego pierwszy raz
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string x;
        ss >> x;
        if (x == playerName)
        {
            std::cout << "Cieszymy sie, ze znowu nas odwiedziles!" << std::endl;
            break;
        }
    }
    return true;
}

void MainGame(std::string playerName, std::vector<Question> questions, Lifelines lifelines)
{
    int maxRounds = 2;
    for (int i = 0; i < maxRounds; i++)
    {
        //TODO: dodać ewentualnie rezygnowanie z gry na danej kwocie
        std::cout << "Informacja do gry." << std::endl;
        std::cout << "Po wybraniu znaku P, zostanie wyswietlone okno wyboru kol ratunkowych." << std::endl;
        std::cout<<std::endl;
        int x = Random(0, questions.size() - 1);
        std::cout << "Twoje " << i + 1 << " pytanie brzmi: " << std::endl;
        std::cout << questions[x].question << std::endl;
        std::cout << "Odpowiedzi sa nastepujace: " << std::endl;
        std::cout << questions[x].answers[0] << std::endl;
        std::cout << questions[x].answers[1] << std::endl;
        std::cout << questions[x].answers[2] << std::endl;
        std::cout << questions[x].answers[3] << std::endl;
        std::cout << "Jaka jest twoja odpowiedz na to pytanie?" << std::endl;
        char odpowiedz;
        std::cin >> odpowiedz;
        if (toupper(odpowiedz) == 'P')
        {
            Help(playerName,questions[x],lifelines);
        }
        else if (toupper(odpowiedz) == questions[x].correctAnswer)
        {
            if (i + 1 == maxRounds)
            {
                std::cout << "Gratulacje, to byla poprawna odpowiedz na ostatnie pytanie" << std::endl;
                std::cout << "Jestes milionerem " << playerName << "!" << std::endl;
            }
            else
            {
                std::cout << "Gratulacje, to byla poprawna odpowiedz" << std::endl;
                std::cout << "Przechodzimy do nastepnego pytania" << std::endl;
            }
        }
        else
        {
            std::cout << "Przykro mi, ale twoja odpowiedz jest niepoprawna" << std::endl;
            std::cout << "Poprawna odpowiedzia na to pytanie jest odpowiedz " << questions[x].correctAnswer
                      << std::endl;
            std::cout << "Dziekujemy za twoj udział " << playerName << ". Udalo ci sie dotrzec do " << i + 1
                      << " pytania"
                         "." << std::endl;
            std::cout << "Powodzenia nastepnym razem!" << std::endl;
        }
        questions.erase(questions.begin() + x);
        std::cout << std::endl;
    }
}

void Help(std::string playerName, Question question, Lifelines lifelines)
{
    if(!lifelines.AskAudience&&!lifelines.fiftyFifty&&!lifelines.phoneToFriend)
    {
        std::cout<<"Niestety nie masz juz zadnych kol ratunkowych!"<<std::endl;
        std::cout<<"Musisz odpowiedziec na pytanie bez pomocy!"<<std::endl;
    }
    std::cout<<"Ktorego kola ratunkowego chcialbys uzyc?"<<std::endl;
}

int Random(int min, int max)
{
    std::default_random_engine silnik;
    silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> rozklad(min, max);
    return rozklad(silnik);
}