#include "jeuHumain.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include <algorithm>
#include <cctype>

// Transforme le mot secret en affichant les lettres devinées et des _ pour les autres
std::string mask_word(const std::string& word, const std::set<char>& guessed) {
    std::string result;
    for (char c : word) {
        if (guessed.count(toupper(c))) result += c;
        else result += "_ ";
    }
    return result;
}

// Gère toute la partie contre un autre humain, avec affichage et gestion des événements
int jouerContreHumain(sf::RenderWindow& window, sf::Font& font, GADDAG& gaddag) {
    std::string mot_secret, input = "";
    bool en_attente_du_mot = true;
    std::set<char> lettres_essayees;
    int erreurs = 0, max_erreurs = 10;
    std::string message = "";
    FinPartie etat = EN_COURS;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return -1;

            if (event.type == sf::Event::TextEntered) {
                char c = static_cast<char>(event.text.unicode);
                if (en_attente_du_mot) {
                    if (isalpha(c)) input += toupper(c);
                    else if (c == 8 && !input.empty()) input.pop_back();
                    else if (c == 13 && !input.empty()) {
                        mot_secret = input;
                        for (char& ch : mot_secret) ch = toupper(ch);
                        mot_secret.erase(std::remove_if(mot_secret.begin(), mot_secret.end(), [](char x) { return !isalpha(x); }), mot_secret.end());

                        if (gaddag.recherche(mot_secret)) {
                            en_attente_du_mot = false;
                            message = "";
                        } else {
                            message = "Mot inconnu dans le dictionnaire !";
                            input = "";
                        }
                    }
                } else if (etat == EN_COURS) {
                    char lettre = toupper(c);
                    if (lettre >= 'A' && lettre <= 'Z' && !lettres_essayees.count(lettre)) {
                        lettres_essayees.insert(lettre);
                        if (mot_secret.find(lettre) == std::string::npos)
                            erreurs++;
                    }
                } else {
                    if (c == 'R' || c == 'r') return 1;
                    if (c == 'M' || c == 'm') return 2;
                    if (c == 'Q' || c == 'q') return -1;
                }
            }
        }

        // Vérifie la fin de partie
        if (etat == EN_COURS && !mot_secret.empty()) {
            bool gagné = false;
            bool perdu = false;

            // Vérifie si toutes les lettres ont été trouvées
            bool toutes_trouvees = true;
            for (char c : mot_secret) {
                if (!lettres_essayees.count(c)) {
                    toutes_trouvees = false;
                    break;
                }
            }

            if (toutes_trouvees) {
                gagné = true;
            } else if (erreurs >= max_erreurs) {
                perdu = true;
            }

            if (gagné)
                etat = GAGNE;
            else if (perdu)
                etat = PERDU;
        }


        window.clear(sf::Color::White);
        dessinerPendu(window, erreurs);

        sf::Text texte;
        texte.setFont(font);
        texte.setCharacterSize(32);
        texte.setFillColor(sf::Color::Black);

        if (en_attente_du_mot) {
            texte.setString("Mot secret : " + input);
            texte.setPosition(50, 80);
            window.draw(texte);

            if (!message.empty()) {
                texte.setString(message);
                texte.setFillColor(sf::Color::Red);
                texte.setPosition(50, 160);
                window.draw(texte);
            }

            window.display();
            continue;
        }

        texte.setFillColor(sf::Color::Black);
        texte.setString("Mot : " + mask_word(mot_secret, lettres_essayees));
        texte.setPosition(50, 80);
        window.draw(texte);

        std::string essais = "Lettres testées : ";
        for (char c : lettres_essayees) essais += c;
        texte.setString(sf::String::fromUtf8(essais.begin(), essais.end()));
        texte.setPosition(50, 180);
        window.draw(texte);

        texte.setString("Erreurs : " + std::to_string(erreurs) + " / " + std::to_string(max_erreurs));
        texte.setPosition(50, 260);
        window.draw(texte);

        if (etat == GAGNE) {
            texte.setString("Bravo !");
            texte.setFillColor(sf::Color::Green);
            texte.setPosition(50, 340);
            window.draw(texte);
        } else if (etat == PERDU) {
            texte.setString("Perdu !");
            texte.setFillColor(sf::Color::Red);
            texte.setPosition(50, 340);
            window.draw(texte);
            std::string message_utf8 = "Le mot secret était: ";
            texte.setString(sf::String::fromUtf8(message_utf8.begin(), message_utf8.end()));
            texte.setFillColor(sf::Color::Black);
            texte.setPosition(190, 340);
            window.draw(texte);
            texte.setString(mot_secret);
            texte.setFillColor(sf::Color::Green);
            texte.setPosition(460, 340);
            window.draw(texte);
        }

        // Menu fin de partie
        if (etat != EN_COURS) {
            texte.setString("R - Rejouer");
            texte.setFillColor(sf::Color::Blue);
            texte.setPosition(600, 420);
            window.draw(texte);
            texte.setString("M - Menu");
            texte.setPosition(600, 465);
            window.draw(texte);
            texte.setString("Q - Quitter");
            texte.setPosition(600, 510);
            window.draw(texte);

        }

        window.display();
    }

    return -1;
}


// Dessine l’état du pendu selon le nombre d’erreurs
void dessinerPendu(sf::RenderWindow& window, int erreurs) {
    sf::RectangleShape ligne;
    const float baseX = 750;
    const float baseY = 150;

    // Étape 1 : sol
    if (erreurs > 0) {
        ligne.setSize(sf::Vector2f(150, 10));
        ligne.setPosition(baseX - 40, baseY + 200);
        ligne.setFillColor(sf::Color::Black);
        window.draw(ligne);
    }

    // Étape 2 : poteau vertical
    if (erreurs > 1) {
        ligne.setSize(sf::Vector2f(10, 200));
        ligne.setPosition(baseX, baseY);
        window.draw(ligne);
    }

    // Étape 3 : poutre horizontale
    if (erreurs > 2) {
        ligne.setSize(sf::Vector2f(100, 10));
        ligne.setPosition(baseX, baseY);
        window.draw(ligne);
    }

    // Étape 4 : petite corde verticale
    if (erreurs > 3) {
        ligne.setSize(sf::Vector2f(10, 30));
        ligne.setPosition(baseX + 90, baseY);
        window.draw(ligne);
    }

    // Étape 5 : tête
    if (erreurs > 4) {
        sf::CircleShape tete(15);
        tete.setFillColor(sf::Color::Magenta);
        tete.setPosition(baseX + 80, baseY + 30);
        window.draw(tete);
    }

    // Étape 6 : corps
    if (erreurs > 5) {
        ligne.setSize(sf::Vector2f(5, 60));
        ligne.setRotation(0);
        ligne.setPosition(baseX + 90, baseY + 60);
        window.draw(ligne);
    }

    // Étape 7 : bras gauche ↖
    if (erreurs > 6) {
        ligne.setSize(sf::Vector2f(40, 5));
        ligne.setRotation(-135);
        ligne.setPosition(baseX + 90, baseY + 80);
        window.draw(ligne);
    }

    // Étape 8 : bras droit ↗
    if (erreurs > 7) {
        ligne.setSize(sf::Vector2f(40, 5));
        ligne.setRotation(-45);
        ligne.setPosition(baseX + 90, baseY + 80);
        window.draw(ligne);
    }

    // Étape 9 : jambe gauche ↙
    if (erreurs > 8) {
        ligne.setSize(sf::Vector2f(40, 5));
        ligne.setRotation(135);
        ligne.setPosition(baseX + 96, baseY + 120);
        window.draw(ligne);
    }

    // Étape 10 : jambe droite ↘
    if (erreurs > 9) {
        ligne.setSize(sf::Vector2f(40, 5));
        ligne.setRotation(45);
        ligne.setPosition(baseX + 96, baseY + 120);
        window.draw(ligne);
    }
}

// Dessine un pendu simplifié pour le menu principal
void dessinerPenduMenu(sf::RenderWindow& window, int erreurs) {
    sf::RectangleShape ligne;
    const float baseX = 800;
    const float baseY = 360;

    // Poteau
    ligne.setSize(sf::Vector2f(10, 200));
    ligne.setPosition(baseX, baseY);
    ligne.setFillColor(sf::Color::Black);
    window.draw(ligne);

    ligne.setSize(sf::Vector2f(100, 10));
    ligne.setPosition(baseX, baseY);
    window.draw(ligne);

    ligne.setSize(sf::Vector2f(10, 30));
    ligne.setPosition(baseX + 90, baseY);
    window.draw(ligne);

    ligne.setSize(sf::Vector2f(150, 10));
    ligne.setPosition(baseX - 40, baseY + 200);
    window.draw(ligne);

    // Tête
    if (erreurs > 0) {
        sf::CircleShape tête(15);
        tête.setFillColor(sf::Color::Magenta);
        tête.setPosition(baseX + 80, baseY + 30);  // centré sous la corde
        window.draw(tête);
    }

    // Corps
    if (erreurs > 1) {
        ligne.setSize(sf::Vector2f(5, 60));
        ligne.setRotation(0);
        ligne.setPosition(baseX + 90, baseY + 60);  // juste sous la tête
        window.draw(ligne);
    }

    // Bras gauche ↖
    if (erreurs > 2) {
        ligne.setSize(sf::Vector2f(40, 5));
        ligne.setRotation(-135);
        ligne.setPosition(baseX + 90, baseY + 80);  // haut du torse
        window.draw(ligne);
    }

    // Bras droit ↗
    if (erreurs > 3) {
        ligne.setSize(sf::Vector2f(40, 5));
        ligne.setRotation(-45);
        ligne.setPosition(baseX + 90, baseY + 80);
        window.draw(ligne);
    }

    // Jambe gauche ↙
    if (erreurs > 4) {
        ligne.setSize(sf::Vector2f(40, 5));
        ligne.setRotation(135);
        ligne.setPosition(baseX + 96, baseY + 120);  // bas du torse
        window.draw(ligne);
    }

    // Jambe droite ↘
    if (erreurs > 5) {
        ligne.setSize(sf::Vector2f(40, 5));
        ligne.setRotation(45);
        ligne.setPosition(baseX + 96, baseY + 120);
        window.draw(ligne);
    }
}




