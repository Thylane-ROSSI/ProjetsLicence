#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "Plateau.h"
#include "Joueur.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

// Prototypes des fonctions d'initialisation et de nettoyage
/**
 * @brief Cette fonction initialise la fenêtre SDL, le renderer SDL, la police de caractères TTF et la musique de fond.
 * @param window Référence à la fenêtre SDL.
 * @param renderer Référence au renderer SDL.
 * @param font Référence à la police de caractères TTF.
 * @param backgroundMusic Référence à la musique de fond.
 */
void init(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font*& font, Mix_Music*& backgroundMusic);

/**
 * @brief Cette fonction nettoie et libère la mémoire utilisée par la fenêtre SDL, le renderer SDL et la police de caractères TTF.
 * @param window Pointeur vers la fenêtre SDL.
 * @param renderer Pointeur vers le renderer SDL.
 * @param font Pointeur vers la police de caractères TTF.
 */

void cleanup(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);

// Les fonctions d'affichage
/**
 * @brief Cette fonction affiche le résultat d'un lancer de dés sur le plateau.
 * @param P Référence vers l'objet Plateau.
 * @param renderer Pointeur vers le renderer SDL.
 * @param font Pointeur vers la police de caractères TTF.
 * @param resultat Résultat du lancer de dés.
 */
void afficher_resultat_de(Plateau &P,SDL_Renderer* renderer, TTF_Font* font, int resultat);

/**
 * @brief Cette fonction affiche le plateau de jeu sur le renderer SDL.
 * @param renderer Pointeur vers le renderer SDL.
 */

void affiche_plateau(SDL_Renderer* renderer);

/**
 * @brief Cette fonction efface le commentaire précédemment affiché sur le renderer SDL.
 * @param renderer Pointeur vers le renderer SDL.
 */

void effacer_commentaire(SDL_Renderer* renderer);

/**
 * @brief cette fonction affiche un commentaire de demande sur le renderer SDL.
 * @param P Référence vers l'objet Plateau.
 * @param renderer Pointeur vers le renderer SDL.
 * @param font Pointeur vers la police de caractères TTF.
 * @param commentaire Commentaire à afficher.
 */

void afficher_commentaire_demande(Plateau &P, SDL_Renderer* renderer, TTF_Font* font, const string& commentaire);

/**
 * @brief Cette fonction affiche un commentaire sur le renderer SDL pour une durée spécifiée en millisecondes.
 * @param P Référence vers l'objet Plateau.
 * @param renderer Pointeur vers le renderer SDL.
 * @param font Pointeur vers la police de caractères TTF.
 * @param commentaire Commentaire à afficher.
 * @param duree_affichage_ms Durée d'affichage du commentaire en millisecondes.
 */

void afficher_commentaire(Plateau &P, SDL_Renderer* renderer, TTF_Font* font, const string& commentaire, int duree_affichage_ms);

/**
 * @brief Cette fonction affiche une carte chance sur le renderer SDL en fonction de son identifiant.
 * @param P Référence vers l'objet Plateau.
 * @param renderer Pointeur vers le renderer SDL.
 * @param font Pointeur vers la police de caractères TTF.
 * @param id_carte Identifiant de la carte chance.
 */

void afficher_carte_chance(Plateau &P, SDL_Renderer* renderer, TTF_Font* font, int id_carte);

/**
 * @brief Cette fonction affiche une carte communauté sur le renderer SDL en fonction de son identifiant.
 * @param P Référence vers l'objet Plateau.
 * @param renderer Pointeur vers le renderer SDL.
 * @param font Pointeur vers la police de caractères TTF.
 * @param id_carte Identifiant de la carte communauté.
 */

void afficher_carte_commu(Plateau &P, SDL_Renderer* renderer, TTF_Font* font, int id_carte);

/**
 * @brief Cette fonction avance le pion d'un joueur sur le plateau de jeu en fonction du résultat du lancer de dés.
 * @param renderer Pointeur vers le renderer SDL.
 * @param num_joueur Numéro du joueur.
 * @param font Pointeur vers la police de caractères TTF.
 * @param P Référence vers l'objet Plateau.
 * @param resultat_des Résultat du lancer de dés.
 */
void avancer_pion(SDL_Renderer* renderer, int num_joueur,  TTF_Font* font, Plateau &P, int resultat_des);

/**
 * @brief Cette fonction affiche le pion d'un joueur sur le plateau de jeu en fonction de sa position.
 * @param joueur_qui_joue Pointeur vers l'objet Joueur.
 * @param renderer Pointeur vers le renderer SDL.
 * @param num_joueur Numéro du joueur.
 */

void afficher_un_pion(Joueur * joueur_qui_joue,SDL_Renderer* renderer, int num_joueur);


/**
 * @brief Cette fonction affiche tous les pions des joueurs sur le plateau de jeu en fonction de leur position.
 * @param P Référence vers l'objet Plateau.
 * @param renderer Pointeur vers le renderer SDL.
 */

void afficher_les_pions(Plateau &P, SDL_Renderer* renderer);

/**
 * @brief Cette fonction affiche le plateau de jeu de manière statique, sans animation.
 * @param P Référence vers l'objet Plateau.
 * @param renderer Pointeur vers le renderer SDL.
 * @param font Pointeur vers la police de caractères TTF.
 */
void afficher_jeu_static(Plateau &P, SDL_Renderer* renderer, TTF_Font* font);

/**
 * @brief Cette fonction affiche les informations des joueurs (argent, position, etc.) sur le renderer SDL.
 * @param renderer Pointeur vers le renderer SDL.
 * @param font Pointeur vers la police de caractères TTF.
 * @param nb_joueur Nombre de joueurs.
 * @param P Référence vers l'objet Plateau.
 */
void Afficher_info_joueurs(SDL_Renderer* renderer, TTF_Font* font, int nb_joueur, Plateau &P);

/**
 * @brief Cette fonction affiche les cartes d'un joueur sur le renderer SDL. 
 * @param renderer Pointeur vers le renderer SDL.
 * @param joueur Pointeur vers l'objet Joueur.
 */
void affichercartes(SDL_Renderer* renderer, Joueur* joueur);

/**
 * @brief Cette fonction affiche une vidéo à l'écran.
 */
void afficher_video();

#endif // AFFICHAGE_H
