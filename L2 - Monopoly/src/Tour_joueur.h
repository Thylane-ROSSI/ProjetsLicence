#ifndef _TOUR_JOUEUR_H
#define _TOUR_JOUEUR_H

#include "Fonctionnalités_Monop.h"
using namespace std;

/**
 * @brief cette fonction effectue le tour d'un joueur dans le jeu.
 * @param P Référence vers l'objet Plateau représentant le plateau de jeu.
 * @param joueur_qui_joue Pointeur vers l'objet Joueur représentant le joueur dont c'est le tour.
 * @param renderer Pointeur vers le renderer SDL utilisé pour l'affichage graphique.
 * @param font Pointeur vers la police de caractères TTF utilisée pour l'affichage.
 * @param numero_du_joueur Le numéro du joueur en cours de jeu.
 */

int tour_joueur(Plateau &P, Joueur* joueur_qui_joue, SDL_Renderer* renderer, TTF_Font* font, int numero_du_joueur);

/**
 * @brief cette fonction lance la partie du jeu de Monopoly.
 * @param P Référence vers l'objet Plateau représentant le plateau de jeu.
 * @param renderer Pointeur vers le renderer SDL utilisé pour l'affichage graphique.
 * @param font Pointeur vers la police de caractères TTF utilisée pour l'affichage.
 */
string lancer_partie(Plateau &P, SDL_Renderer* renderer, TTF_Font* font);

#endif