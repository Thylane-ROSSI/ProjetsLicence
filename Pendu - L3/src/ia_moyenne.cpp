#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "ia.hpp"
#include <random>

// Choisit une lettre aléatoire en se basant sur la fréquence des lettres en français
char choisirLettreIAMoyenne(const std::set<char>& lettresEssayees, const std::string& masque) {
    std::string lettres_frequentes = "AAAAAAAAABBCCDDDEEEEEEEEEEEEEEEFFGGHHIIIIIIIIJKLLLLLMMMNNNNNNOOOOOOPPQRRRRRRSSSSSSTTTTTTUUUUUUVVWXYZ";

    // Retire les lettres déjà essayées
    std::vector<char> pool;
    for (char c : lettres_frequentes)
        if (!lettresEssayees.count(c))
            pool.push_back(c);

    if (pool.empty()) return '\0';

    // Tirage aléatoire pondéré
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, pool.size() - 1);
    return pool[dist(gen)];
}
