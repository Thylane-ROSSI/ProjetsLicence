#ifndef JEU_HPP
#define JEU_HPP

#pragma once
#include <string>
#include <set>  // AJOUT ICI
#include <SFML/Graphics.hpp>
#include "gaddag.hpp"

enum FinPartie { EN_COURS, GAGNE, PERDU };

// Transforme le mot secret en affichant les lettres devinées et des _ pour les autres
std::string mask_word(const std::string& word, const std::set<char>& guessed);

// Gère toute la partie contre un autre humain, avec affichage et gestion des événements
int jouerContreHumain(sf::RenderWindow& window, sf::Font& font, GADDAG& gaddag);

// Dessine l’état du pendu selon le nombre d’erreurs
void dessinerPendu(sf::RenderWindow& window, int erreurs);

// Dessine un pendu simplifié pour le menu principal
void dessinerPenduMenu(sf::RenderWindow& window, int erreurs);


#endif
