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
                file.close();
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
    file.close();
    return true;
}

std::string GetPlayerName()
{
    std::string playerName;
    std::cout << "Witaj w Milionerach!" << std::endl;
    std::cout << "Podaj swoja nazwe: ";
    std::cin >> playerName; // Pyta o nazwe gracza
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

    playerName = GetPlayerName(); // Pobiera nazwe gracza
    std::string line;
    // Pętla pobiera wszystkich graczy z pliku i sprawdza czy dany gracz już grał, czy to jego pierwszy raz
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string x;
        ss >> x; // Wczytuje do zmiennej x kolejnego gracza z pliku
        if (x == playerName) // Sprawdza czy gracz już grał
        {
            std::cout << "Cieszymy sie, ze znowu nas odwiedziles!" << std::endl;
            break;
        }
    }
    file.close();
    return true;
}

int MainGame(std::string playerName, std::vector<Question> questions, Lifelines lifelines)
{
    int maxRounds = 15;
    int score = 0;
    // Wykonuje sie tyle ile ma być pytań
    for (int i = 0; i < maxRounds; i++)
    {
        // Czysci ekran
        system("cls");
        int x = Random(0, questions.size() - 1); // Losowanie, które pytanie z puli zostanie wylosowane
        // Wczytanie odpowiedzi
        std::cout << "Informacja do gry." << std::endl;
        std::cout << "Po wybraniu znaku P, zostanie wyswietlone okno wyboru kol ratunkowych." << std::endl;
        char odpowiedz = ShowQuestion(questions[x], i);
        if (toupper(odpowiedz) == 'P') // Gdy gracz wybierze koła pomocy
        {
            // Wczytanie odpowiedzi po uzyskaniu pomocy

            odpowiedz = Help(playerName, questions[x], lifelines, i);
        }
        if (toupper(odpowiedz) == questions[x].correctAnswer) // Gdy poprawna odpowiedz
        {
            if (i + 1 == maxRounds) // Sprawdza czy to bylo ostatnie pytanie
            {
                std::cout << "Gratulacje, to byla poprawna odpowiedz na ostatnie pytanie" << std::endl;
                std::cout << "Jestes milionerem " << playerName << "!" << std::endl;
                score = i + 1;
            }
            else // Gdy odpowiedz byla poprawna ale bedzie nastepne pytanie
            {
                std::cout << "Gratulacje, to byla poprawna odpowiedz" << std::endl;
                std::cout << "Przechodzimy do nastepnego pytania" << std::endl;
            }
        }
        else // Gdy odpowiedz niepoprawna
        {
            std::cout << "Przykro mi, ale twoja odpowiedz jest niepoprawna" << std::endl;
            std::cout << "Poprawna odpowiedzia na to pytanie jest odpowiedz " << questions[x].correctAnswer
                      << std::endl;
            std::cout << "Dziekujemy za twoj udzial " << playerName << ". Udalo ci sie dotrzec do " << i + 1
                      << " pytania"
                         "." << std::endl;
            std::cout << "Powodzenia nastepnym razem!" << std::endl;
            score = i;
            break;
        }
        questions.erase(questions.begin() + x); // Usunięcoe pytania z puli, by się już nie powtórzyło
        std::cout << std::endl;
    }
    return score;
}

char Help(std::string playerName, Question question, Lifelines &lifelines, int whichQuestion)
{
    char odpowiedz;
    // Sprawdza czy są jakieś dostępne koła ratunkowe
    if (!lifelines.AskAudience && !lifelines.fiftyFifty && !lifelines.phoneToFriend)
    {
        std::cout << "Niestety nie masz juz zadnych kol ratunkowych!" << std::endl;
        std::cout << "Musisz odpowiedziec na pytanie bez pomocy!" << std::endl;
        odpowiedz = ShowQuestion(question, whichQuestion);
    }
    else
    {
        std::cout << "Masz nadal dostepne te kola:" << std::endl;

        if (lifelines.phoneToFriend) // Czy dostepny telefon do przyjaciela
        {
            std::cout << "- (1) Telefon do przyjaciela" << std::endl;
        }
        if (lifelines.AskAudience) // Czy dostepne pytanie do publicznosci
        {
            std::cout << "- (2) Pytanie do publicznosci" << std::endl;
        }
        if (lifelines.fiftyFifty) // Czy dostepne 50:50
        {
            std::cout << "- (3) Pol na pol" << std::endl;
        }
        // Wybór koła do pomocy
        std::cout << "Wybierz, ktore kolo chcesz wybrac:";
        std::cin >> odpowiedz;

        system("cls");
        // Koło telefon do przyjaciela
        if ((odpowiedz == '1') && (lifelines.phoneToFriend))
        {
            lifelines.phoneToFriend = false;
            std::cout << "Twoj przyjaciel powiedzial, ze wydaje mu sie, ze poprawna odpowiedz to:" << question
                    .correctAnswer << std::endl;
            // Wyświetlenie ponownie pytania i zapytanie o odpowiedź
            odpowiedz = ShowQuestion(question, whichQuestion);
        }
        // Koło pytanie do publiczności
        if ((odpowiedz == '2') && (lifelines.AskAudience))
        {
            lifelines.AskAudience = false;
            // Dla poprawnej odpowiedzi wyswietla wynik 55%
            std::cout << "Wyniki publicznosci to:" << std::endl;
            if (question.correctAnswer == 'A')
            {
                std::cout << "Odpowiedz A: 55%" << std::endl;
            }
            else
            {
                std::cout << "Odpowiedz A: 15%" << std::endl;
            }
            if (question.correctAnswer == 'B')
            {
                std::cout << "Odpowiedz B: 55%" << std::endl;
            }
            else
            {
                std::cout << "Odpowiedz B: 15%" << std::endl;
            }
            if (question.correctAnswer == 'C')
            {
                std::cout << "Odpowiedz C: 55%" << std::endl;
            }
            else
            {
                std::cout << "Odpowiedz C: 15%" << std::endl;
            }
            if (question.correctAnswer == 'D')
            {
                std::cout << "Odpowiedz D: 55%" << std::endl;
            }
            else
            {
                std::cout << "Odpowiedz D: 15%" << std::endl;
            }
            odpowiedz = ShowQuestion(question, whichQuestion);
        }
        // Koło 50 na 50
        if ((odpowiedz == '3') && (lifelines.fiftyFifty))
        {
            // Zostawia tylko odpowiedzi A,B lub C,D
            if (question.correctAnswer < 'C')
            {
                question.answers[2] = "";
                question.answers[3] = "";
            }
            else if (question.correctAnswer > 'B')
            {
                question.answers[0] = "";
                question.answers[1] = "";
            }
            // Pyta ponownie o odpowiedź już tylko dla 2 odpowiedzi
            odpowiedz = ShowQuestion(question, whichQuestion);
            lifelines.fiftyFifty = false;
        }
    }

    return odpowiedz;
}

char ShowQuestion(Question question, int whichQuestion)
{
    std::cout << std::endl;
    std::cout << "Twoje " << whichQuestion + 1 << " pytanie brzmi: " << std::endl;
    std::cout << question.question << std::endl;
    std::cout << "Odpowiedzi sa nastepujace: " << std::endl;
    std::cout << question.answers[0] << std::endl;
    std::cout << question.answers[1] << std::endl;
    std::cout << question.answers[2] << std::endl;
    std::cout << question.answers[3] << std::endl;
    std::cout << "Jaka jest twoja odpowiedz na to pytanie?" << std::endl;
    char odpowiedz;
    std::cin >> odpowiedz; // Wczytywanie odpowiedzi uzytkownika
    return odpowiedz;
}

bool SaveToFile(std::string filePath, std::string playerName, int playerScore)
{
    std::ifstream fileIn(filePath);
    // Sprawdza czy plik się poprawnie otworzył
    if (!fileIn.is_open())
    {
        std::cout << "Nie mozna otworzyc pliku!" << std::endl;
        return false;
    }

    bool isAdded = false;
    std::string line;
    std::vector<std::pair<std::string, int>> scores;
    // Wczytuje po kolei linijki do stringa line
    while (std::getline(fileIn, line))
    {
        std::stringstream str(line);
        std::string name;
        int score;
        str >> name >> score;
        // Sprawdza czy gracz juz byl w pliku
        if (name == playerName)
        {
            // Sprawdza czy obecny wynik jest lepszy niz poprzedni, jesli tak to podmienia
            if (playerScore > score)
            {
                score = playerScore;
            }
            isAdded = true;
            return true;
        }
        scores.push_back(std::make_pair(name, score));
    }
    // Jeśli nie było wcześniej go na liście to jest dodawany do wektora z wszystkimi graczami
    if (!isAdded)
    {
        scores.push_back(std::make_pair(playerName, playerScore));
    }
    fileIn.close();
    // Otwarcie pliku do zapisu danych
    std::ofstream fileOut(filePath);
    if (!fileOut.is_open())
    {
        std::cout << "Nie mozna otworzyc pliku!" << std::endl;
        return false;
    }
    // Zapisanie całego wektora do pliku z graczami
    for (int i = 0; i < scores.size(); i++)
    {
        fileOut << scores[i].first << " " << scores[i].second << std::endl;
    }
    fileOut.close();
    return true;
}

int Random(int min, int max)
{
    std::default_random_engine silnik;
    silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> rozklad(min, max);
    return rozklad(silnik);
}