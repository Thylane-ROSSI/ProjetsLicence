#include <stdlib.h>
#include <random>
#include <time.h>
#include <unistd.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mixer.h>


#include "Accueil.h"
#include "Demander_pseudo.cpp"
#include "Tour_joueur.h"
#include "Affichage.h"
#include "Menu_nb_joueurs.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    srand(time(NULL)); 
    int nombre_joueurs;
    Plateau P(0);

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Mix_Music* backgroundMusic; // Ajout de la variable pour la musique de fond

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    nombre_joueurs = Choix_nombre_joueurs();
    if (nombre_joueurs != 0) {
        entrer_les_pseudos(nombre_joueurs, P);
        créer_cartes(P);
        
        // Appel de la fonction init pour initialiser SDL, le rendu, la police et la musique de fond
        init(window, renderer, font, backgroundMusic);

        string gagnant = lancer_partie(P, renderer, font);
        // On est sorti de lancer la partie car elle est finie
        if (gagnant != "") {
            afficher_commentaire(P, renderer, font, "C'est la fin de la partie ! Bravo "+gagnant+" tu as gagné !", 5000);
        } else {
            afficher_commentaire(P, renderer, font, "à bientôt !", 3000);
        }
    }

    

    // Nettoyage et fermeture
    Mix_FreeMusic(backgroundMusic);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    tout_supprimer(P);
    return 0;
}