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

/// Struktura opisująca czy dane koło ratunkowe jest do wykorzystania
struct Lifelines
{
    bool AskAudience = true; /// Koło ratunkowe - pomoc publiczności
    bool fiftyFifty = true; /// Koło ratunkowe - Pół na pół
    bool phoneToFriend = true; /// Koło ratunkowe - Telefon do przyjaciela
};

#endif STRUCTURES_H
