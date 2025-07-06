#include "Accueil.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include <string>

using namespace std;

const int LARGEUR_ECRAN = 1920;
const int HAUTEUR_ECRAN = 1080;
/*const int LARGEUR_BOUTON = 200;
const int HAUTEUR_BOUTON = 50;*/

SDL_Window* fenetre = NULL;
SDL_Renderer* rendu = NULL;
TTF_Font* police = NULL;

SDL_Texture* chargerTexture(const char* chemin) {
    SDL_Surface* surface = IMG_Load(chemin);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void dessinerImage(SDL_Texture* texture, int x, int y, int largeur, int hauteur) {
    SDL_Rect destRect = {x, y, largeur, hauteur};
    SDL_RenderCopy(rendu, texture, NULL, &destRect);
}

void dessinerBouton(SDL_Rect rect, const string& texte) {
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
    SDL_RenderFillRect(rendu, &rect);

    SDL_Color couleurTexte = {0, 0, 0, 255};
    SDL_Surface* surfaceTexte = TTF_RenderText_Solid(police, texte.c_str(), couleurTexte);
    SDL_Texture* textureTexte = SDL_CreateTextureFromSurface(rendu, surfaceTexte);

    int largeurTexte, hauteurTexte;
    SDL_QueryTexture(textureTexte, NULL, NULL, &largeurTexte, &hauteurTexte);

    SDL_Rect rectTexte = {rect.x + (rect.w - largeurTexte) / 2, rect.y + (rect.h - hauteurTexte) / 2, largeurTexte, hauteurTexte};
    SDL_RenderCopy(rendu, textureTexte, NULL, &rectTexte);

    SDL_FreeSurface(surfaceTexte);
    SDL_DestroyTexture(textureTexte);
}

void togglePleinEcran() {
    Uint32 pleinEcranActuel = SDL_GetWindowFlags(fenetre) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(fenetre, pleinEcranActuel ? 0 : SDL_WINDOW_FULLSCREEN);
}

void dessinerBoutons() {
    int boutonX = (LARGEUR_ECRAN - LARGEUR_BOUTON) / 2;
    int boutonY = (HAUTEUR_ECRAN - HAUTEUR_BOUTON * 2 - 20) / 2 + 200;

    SDL_Rect boutonNouvellePartie = {boutonX, boutonY, LARGEUR_BOUTON, HAUTEUR_BOUTON};
    SDL_Rect boutonQuitter = {boutonX, boutonY + HAUTEUR_BOUTON + 20, LARGEUR_BOUTON, HAUTEUR_BOUTON};

    dessinerBouton(boutonNouvellePartie, "Nouvelle partie");
    dessinerBouton(boutonQuitter, "Quitter le jeu");
}

void afficherMenu(SDL_Texture* textureFond) {
    SDL_RenderClear(rendu);
    dessinerBoutons();
    dessinerImage(textureFond, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN);
    SDL_RenderPresent(rendu);
}

int Choix_nombre_joueurs() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    fenetre = SDL_CreateWindow("Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR_ECRAN, HAUTEUR_ECRAN, SDL_WINDOW_SHOWN);
    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    police = TTF_OpenFont("/mnt/c/Windows/Fonts/arial.ttf", 24);
    SDL_Texture* textureFond = chargerTexture("data/menu1.png");


    SDL_Event e;
    bool quitter = false;

 while (!quitter) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quitter = true;
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F11) {
                togglePleinEcran();
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int sourisX, sourisY;
                SDL_GetMouseState(&sourisX, &sourisY);

                int boutonX = (LARGEUR_ECRAN - LARGEUR_BOUTON) / 2;
                int boutonY = (HAUTEUR_ECRAN - HAUTEUR_BOUTON * 2 - 20) / 2 + 200;

                if (sourisX >= boutonX && sourisX <= boutonX + LARGEUR_BOUTON) {
                    if (sourisY >= boutonY && sourisY <= boutonY + HAUTEUR_BOUTON) {
                        // Action pour "Nouvelle partie"
                        return choisirNombreJoueurs();
                    }
                    else if (sourisY >= boutonY + HAUTEUR_BOUTON + 20 && sourisY <= boutonY + 2 * HAUTEUR_BOUTON + 20) {
                        quitter = true; // Action pour "Quitter le jeu"
                        return 0;
                    }
                }
            }
        }
        afficherMenu(textureFond);
    }

    SDL_DestroyTexture(textureFond);
    TTF_CloseFont(police);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
