#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

/// Struktura opisująca jedno pyutanie z pliku
struct Question
{
    std::string question; /// Pytanie
    std::string answers[4]; /// -Tablica z 4 odpowiedziami do pytania
    int correctAnswer; /// Numer poprawnej odpowiedzi
};

#endif STRUCTURES_H
