#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "ia.hpp"

// Choisit une lettre aléatoire parmi celles non encore essayées
char choisirLettreIAFacile(const std::set<char>& lettresEssayees) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<char> choix;
    for (char c : alphabet)
        if (!lettresEssayees.count(c))
            choix.push_back(c);

    if (choix.empty()) return '\0';
    return choix[rand() % choix.size()];
}
