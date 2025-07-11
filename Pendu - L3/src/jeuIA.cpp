#include "jeuIA.hpp"
#include "ia.hpp"
#include "jeuHumain.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>

// Lance une partie contre l’IA avec gestion du mot, des erreurs et du comportement selon la difficulté
int jouerContreIA(sf::RenderWindow& window, sf::Font& font, GADDAG& gaddag, int difficulte) {
    std::string mot_secret = "";
    std::string input = "";
    std::string message = "";
    bool en_attente_du_mot = true;
    std::set<char> lettres_essayees;
    int erreurs = 0, max_erreurs = 10;
    FinPartie etat = EN_COURS;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return -1;

            // Saisie du mot par l'utilisateur
            if (event.type == sf::Event::TextEntered) {
                char c = static_cast<char>(event.text.unicode);

                if (en_attente_du_mot) {
                    if (isalpha(c)) input += toupper(c);
                    else if (c == 8 && !input.empty()) input.pop_back(); 
                    else if ((c == 13 || c == '\r') && !input.empty()) { 
                        mot_secret = input;
                        mot_secret.erase(std::remove_if(mot_secret.begin(), mot_secret.end(),
                                                        [](char x) { return !isalpha(x); }), mot_secret.end());
                        for (char& ch : mot_secret) ch = toupper(ch);

                        if (gaddag.recherche(mot_secret)) {
                            en_attente_du_mot = false;
                            message = "";
                        } else {
                            message = "Mot inconnu dans le dictionnaire !";
                            input = "";
                        }
                    }
                } else if (etat != EN_COURS) {
                    if (c == 'R' || c == 'r') return 1;   // Rejouer
                    if (c == 'M' || c == 'm') return 2;   // Retour menu
                    if (c == 'Q' || c == 'q') return -1;  // Quitter
                }
            }

        }

        if (en_attente_du_mot) {
            window.clear(sf::Color::White);
            dessinerPendu(window, 0);
            sf::Text texte;
            texte.setFont(font);
            texte.setCharacterSize(32);
            texte.setFillColor(sf::Color::Black);

            std::string message_utf8 = "Mot à faire deviner par l'IA : " + input;
            texte.setString(sf::String::fromUtf8(message_utf8.begin(), message_utf8.end()));
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

        // Jeu de l'IA
        if (etat == EN_COURS) {
            std::string masque = mask_word(mot_secret, lettres_essayees);
            char lettre;

            if (difficulte == 2)
                lettre = choisirLettreIAFacile(lettres_essayees);
            else if (difficulte == 3)
                lettre = choisirLettreIAMoyenne(lettres_essayees, masque);
            else{
                lettre = choisirLettreIADifficile(lettres_essayees, masque);
                std::vector<std::string> debug_candidats = getCandidatsIADifficile();
            }
            lettres_essayees.insert(lettre);

            if (mot_secret.find(lettre) == std::string::npos)
                erreurs++;

            bool toutes_trouvees = true;
            for (char c : mot_secret)
                if (!lettres_essayees.count(c))
                    toutes_trouvees = false;

            if (toutes_trouvees)
                etat = GAGNE;
            else if (erreurs >= max_erreurs)
                etat = PERDU;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // Affichage 
        window.clear(sf::Color::White);
        dessinerPendu(window, erreurs);

        sf::Text texte;
        texte.setFont(font);
        texte.setCharacterSize(32);
        texte.setFillColor(sf::Color::Black);

        texte.setString("Mot : " + mask_word(mot_secret, lettres_essayees));
        texte.setPosition(50, 80);
        window.draw(texte);

        std::string essais = "Lettres testées :";
        for (char c : lettres_essayees) essais += c;
        texte.setString(sf::String::fromUtf8(essais.begin(), essais.end()));
        texte.setPosition(50, 180);
        window.draw(texte);

        texte.setString("Erreurs : " + std::to_string(erreurs) + " / " + std::to_string(max_erreurs));
        texte.setPosition(50, 260);
        window.draw(texte);

        if (etat == GAGNE) {
            std::string message_utf8 = "L'IA a gagné !";
            texte.setString(sf::String::fromUtf8(message_utf8.begin(), message_utf8.end()));
            texte.setFillColor(sf::Color::Green);
            texte.setPosition(50, 340);
            window.draw(texte);
        } else if (etat == PERDU) {
            texte.setString("L'IA a perdu !");
            texte.setFillColor(sf::Color::Red);
            texte.setPosition(50, 340);
            window.draw(texte);

            texte.setString("Le mot secret : ");
            texte.setFillColor(sf::Color::Black);
            texte.setPosition(50, 420);
            window.draw(texte);

            texte.setString(mot_secret);
            texte.setFillColor(sf::Color::Green);
            texte.setPosition(315, 420);
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