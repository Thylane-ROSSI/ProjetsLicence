#pragma once
#include <set>
#include <string>
#include "gaddag.hpp"

// Choisit une lettre aléatoire parmi celles non encore essayées
char choisirLettreIAFacile(const std::set<char>& lettresEssayees);

// Choisit une lettre aléatoire en se basant sur la fréquence des lettres en français
char choisirLettreIAMoyenne(const std::set<char>& lettresEssayees, const std::string& masque);

// Choisit la meilleure lettre à proposer en fonction du masque et des mots filtrés
char choisirLettreIADifficile(const std::set<char>& lettresEssayees, const std::string& masque);

// Réinitialise les mots candidats pour recommencer depuis zéro
void resetIADifficile();

// Retourne la liste actuelle des mots candidats
const std::vector<std::string>& getCandidatsIADifficile();

