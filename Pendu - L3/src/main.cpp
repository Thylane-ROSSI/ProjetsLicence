#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "jeuHumain.hpp"
#include "gaddag.hpp"
#include "ia.hpp"
#include "jeuIA.hpp"


// Affiche le menu principal et permet de choisir le mode de jeu
int lancerMenu(sf::RenderWindow& window, sf::Font& font) {
    std::vector<std::string> options = {
        "1. Jouer contre un humain",
        "2. IA facile",
        "3. IA moyenne",
        "4. IA difficile"
    };

    int selection = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up && selection > 0)
                    selection--;
                else if (event.key.code == sf::Keyboard::Down && selection < (int)options.size() - 1)
                    selection++;
                else if (event.key.code == sf::Keyboard::Enter)
                    return selection + 1;
            }
        }

        window.clear(sf::Color::White);
        for (int i = 0; i < static_cast<int>(options.size()); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(options[i]);
            text.setCharacterSize(36);
            text.setPosition(100, 100 + i * 60);
            text.setFillColor(i == selection ? sf::Color::Blue : sf::Color::Black);
            window.draw(text);
        }
        dessinerPenduMenu(window, 6);

        window.display();
    }

    return -1;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Pendu");
    sf::Font font;
    if (!font.loadFromFile("data/alpha_echo.ttf")) {
        std::cerr << "Erreur chargement police\n";
        return 1;
    }

    
    GADDAG gaddag;
    gaddag.initialiser_GADDAG();

    int mode = lancerMenu(window, font);

    while (mode >= 1 && mode <= 4) {
        int resultat = -1;

        if (mode == 1) {
            resultat = jouerContreHumain(window, font, gaddag);
        } else {
            if (mode == 4) resetIADifficile();
            resultat = jouerContreIA(window, font, gaddag, mode);
        }

        if (resultat == 1) {
            // Rejouer : on garde le même mode
            continue;
        } else if (resultat == 2) {
            // Retour au menu
            mode = lancerMenu(window, font);
        } else {
            // Quitter
            break;
        }
    }


    return 0;
}
