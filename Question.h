#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

/// Struktura opisująca jedno pytanie z pliku
struct Question
{
    /// Pytanie
    std::string question;
    /// Tablica z 4 odpowiedziami do pytania
    std::string answers[4];
    /// Numer poprawnej odpowiedzi
    char correctAnswer;
};

#endif STRUCTURES_H
