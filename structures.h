#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

/// Struktura opisująca jedno pyutanie z pliku
struct Question
{
    std::string question; /// Pytanie
    std::string answers[4]; /// -Tablica z 4 odpowiedziami do pytania
    char correctAnswer; /// Numer poprawnej odpowiedzi
};

struct Lifelines
{
    bool AskAudience = true;
    bool fiftyFifty = true;
    bool phoneToFriend = true;
};

#endif STRUCTURES_H
