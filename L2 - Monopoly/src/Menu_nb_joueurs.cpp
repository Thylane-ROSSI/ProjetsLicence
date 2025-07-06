#include "Menu_nb_joueurs.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include <iostream>

using namespace std;

int choisirNombreJoueurs() {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Erreur d'initialisation de SDL : " << SDL_GetError() << endl;
        return -1;
    }

    // Initialiser SDL_ttf
    if (TTF_Init() == -1) {
        cerr << "Erreur d'initialisation de SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    // Créer la fenêtre de sélection du nombre de joueurs
    SDL_Window* fenetre = SDL_CreateWindow("Choix du nombre de joueurs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);
    if (!fenetre) {
        cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    // Créer le rendu
    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!rendu) {
        cerr << "Erreur lors de la création du rendu : " << SDL_GetError() << endl;
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return -1;
    }

    // Charger l'image pour le fond
    SDL_Surface* surfaceFond = IMG_Load("data/menu2.png");
    if (!surfaceFond) {
        cerr << "Erreur lors du chargement de l'image de fond : " << SDL_GetError() << endl;
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return -1;
    }
    SDL_Texture* textureFond = SDL_CreateTextureFromSurface(rendu, surfaceFond);
    SDL_FreeSurface(surfaceFond);

    // Charger la police de caractères
    TTF_Font* police = TTF_OpenFont("/mnt/c/Windows/Fonts/arial.ttf", 24);
    if (!police) {
        cerr << "Erreur lors du chargement de la police de caractères : " << TTF_GetError() << endl;
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return -1;
    }

    // Boucle principale pour la gestion des événements
    bool enCours = true;
    int nombreJoueurs = 0;

    while (enCours) {
        SDL_Event evenement;
        while (SDL_PollEvent(&evenement)) {
            switch (evenement.type) {
                case SDL_QUIT:
                    enCours = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (x >= LARGEUR_FENETRE / 2 - LARGEUR_BOUTON / 2 && x <= LARGEUR_FENETRE / 2 + LARGEUR_BOUTON / 2) {
                        if (y >= HAUTEUR_FENETRE / 2 - HAUTEUR_BOUTON / 2 && y <= HAUTEUR_FENETRE / 2 + HAUTEUR_BOUTON / 2) {
                            nombreJoueurs = 2;
                            enCours = false;
                        } else if (y >= HAUTEUR_FENETRE / 2 - HAUTEUR_BOUTON / 2 + HAUTEUR_BOUTON + ESPACEMENT_BOUTONS &&
                                   y <= HAUTEUR_FENETRE / 2 + HAUTEUR_BOUTON / 2 + HAUTEUR_BOUTON + ESPACEMENT_BOUTONS) {
                            nombreJoueurs = 3;
                            enCours = false;
                        } else if (y >= HAUTEUR_FENETRE / 2 - HAUTEUR_BOUTON / 2 + 2 * (HAUTEUR_BOUTON + ESPACEMENT_BOUTONS) &&
                                   y <= HAUTEUR_FENETRE / 2 + HAUTEUR_BOUTON / 2 + 2 * (HAUTEUR_BOUTON + ESPACEMENT_BOUTONS)) {
                            nombreJoueurs = 4;
                            enCours = false;
                        }
                    }
                    break;
            }
        }

        // Modifier la couleur de rendu pour les boutons
        SDL_SetRenderDrawColor(rendu, 100, 100, 100, 255);
        
        // Dessiner les boutons
        SDL_Rect boutonDeuxJoueurs = {LARGEUR_FENETRE / 2 - LARGEUR_BOUTON / 2, HAUTEUR_FENETRE / 2 - HAUTEUR_BOUTON / 2, LARGEUR_BOUTON, HAUTEUR_BOUTON};
        SDL_Rect boutonTroisJoueurs = {LARGEUR_FENETRE / 2 - LARGEUR_BOUTON / 2, HAUTEUR_FENETRE / 2 - HAUTEUR_BOUTON / 2 + HAUTEUR_BOUTON + ESPACEMENT_BOUTONS, LARGEUR_BOUTON, HAUTEUR_BOUTON};
        SDL_Rect boutonQuatreJoueurs = {LARGEUR_FENETRE / 2 - LARGEUR_BOUTON / 2, HAUTEUR_FENETRE / 2 - HAUTEUR_BOUTON / 2 + 2 * (HAUTEUR_BOUTON + ESPACEMENT_BOUTONS), LARGEUR_BOUTON, HAUTEUR_BOUTON};

        SDL_RenderFillRect(rendu, &boutonDeuxJoueurs);
        SDL_RenderFillRect(rendu, &boutonTroisJoueurs);
        SDL_RenderFillRect(rendu, &boutonQuatreJoueurs);

        // Dessiner le fond
        SDL_RenderCopy(rendu, textureFond, NULL, NULL);

        // Modifier la couleur de rendu pour le texte
        SDL_Color couleurNoire = {0, 0, 0, 255}; // Couleur blanche

        SDL_RenderPresent(rendu);
    }

    // Nettoyer et quitter SDL_ttf
    TTF_CloseFont(police);
    TTF_Quit();

    // Nettoyer et quitter SDL
    SDL_DestroyTexture(textureFond);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return nombreJoueurs;
}
