#ifndef LIFELINES_H
#define LIFELINES_H

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

#endif LIFELINES_H
