#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

/// Struktura opisująca jedno pytanie z pliku
struct Question
{
    /// Pytanie
    std::string question;
    /// -Tablica z 4 odpowiedziami do pytania
    std::string answers[4];
    /// Numer poprawnej odpowiedzi
    char correctAnswer;
};

/// Struktura opisująca czy dane koło ratunkowe jest do wykorzystania
struct Lifelines
{
    /// Koło ratunkowe - pomoc publiczności
    bool AskAudience = true;
    /// Koło ratunkowe - Pół na pół
    bool fiftyFifty = true;
    /// Koło ratunkowe - Telefon do przyjaciela
    bool phoneToFriend = true;
};

#endif STRUCTURES_H
