#pragma once
#include <SFML/Graphics.hpp>
#include "gaddag.hpp"


// Fonction principale pour jouer contre une IA de difficulté 2 (facile), 3 (moyenne), 4 (difficile)
int jouerContreIA(sf::RenderWindow& window, sf::Font& font, GADDAG& gaddag, int difficulte);
