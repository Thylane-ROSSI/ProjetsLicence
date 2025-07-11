#ifndef GADDAG_HPP
#define GADDAG_HPP

#include "noeud.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>   
#include <set>

class GADDAG {
private:
    Noeud racine;
public:

    // Charge tous les mots du fichier dictionnaire et les insère dans la structure
    void initialiser_GADDAG();

    // Ajoute un mot caractère par caractère dans le GADDAG
    void ajouter_mot(std::string mot);

    // Vérifie si un mot est présent dans le GADDAG
    bool recherche(std::string mot);

    // Tableau dynamique des mots
    std::vector<std::string> tous_les_mots;

};

#endif // GADDAG_HPP
