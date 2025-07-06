#ifndef _TOUR_H
#define _TOUR_H

#include "Joueur.h"
#include "Plateau.h"
#include "Cartechance.h"
#include "Cartecommu.h"
#include "CarteImmo.h"
#include "Gare.h"
#include "ServicePublic.h"
#include "Caisse_fonctions.h"
#include "Chance_fonctions.h"
#include "Affichage.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

/**
 * @brief Fonction qui supprime la mémoire alloué aux tableaux dynamiques
 * 
 * @param P Référence vers le plateau de jeu
 */
void tout_supprimer(Plateau &P);

/**
 * @brief cette fonction permet de lancer les dés au début du tour du joueur
 * 
 * @return int La somme des valeurs obtenues en lançant les dés
 */

// Lancer les dés à chaque début du tour du joueur
int lancer_les_dés(); 

/**
 * @brief cette fonction permet de piocher une carte chance si le joueur est sur une case carte chance
 * 
 * @param P Référence vers le plateau de jeu
 * @param joueur_qui_joue Le joueur en cours
 * @param renderer Le renderer SDL pour l'affichage
 * @param font La police de caractères pour l'affichage
 */
void piocher_carteschances(Plateau &P, Joueur* joueur_qui_joue, SDL_Renderer* renderer, TTF_Font* font);

/**
 * @brief cette fonction permet de piocher une carte caisse de communauté si le joueur est sur une case carte caisse de communauté
 * 
 * @param P Référence vers le plateau de jeu
 * @param joueur_qui_joue Le joueur en cours
 * @param renderer Le renderer SDL pour l'affichage
 * @param font La police de caractères pour l'affichage
 */
void piocher_cartescommu(Plateau &P, Joueur* joueur_qui_joue, SDL_Renderer* renderer, TTF_Font* font);

/**
 * @brief cette fonction permet de lancer les dés pour voir si le joueur en prison fait un double
 * 
 * @param P Référence vers le plateau de jeu
 * @param joueur_qui_joue Le joueur en cours
 * @param renderer Le renderer SDL pour l'affichage
 * @param font La police de caractères pour l'affichage
 * @return bool True si le joueur a fait un double, sinon False
 */
bool lancer_de_prison(Plateau &P, Joueur* joueur_qui_joue, SDL_Renderer* renderer, TTF_Font* font);

/**
 * @brief cette fonction permet de payer 50€ pour sortir de prison
 * 
 * @param joueur_qui_joue Le joueur en cours
 */
void payer_50 (Joueur* joueur_qui_joue);

/**
 * @brief cette fonction permet d'utiliser une carte "libérer de prison" pour sortir de prison
 * 
 * @param joueur_qui_joue Le joueur en cours
 */
void utiliser_carte_prison(Joueur* joueur_qui_joue);

/**
 * @brief cette fonction permet d'acheter une maison
 * 
 * @param joueur_qui_joue Le joueur qui souhaite acheter la maison
 * @param P Référence vers le plateau de jeu
 * @param renderer Le renderer SDL pour l'affichage
 * @param font La police de caractères pour l'affichage
 */
void acheter_maison(Joueur* joueur_qui_joue, Plateau &P, SDL_Renderer* renderer, TTF_Font* font);

/**
 * @brief cette fonction permet de vérifier si le joueur a assez d'argent pour acheter une maison ou un hôtel
 * 
 * @param joueur_qui_joue Le joueur en cours
 * @param prix_a_payer Le prix à payer pour l'achat
 * @return bool True si le joueur a assez d'argent, sinon False
 */
bool assez_dargent_pour_maison_ou_hotel(Joueur* joueur_qui_joue, int prix_a_payer);

/**
 * @brief cette fonction permet de créer les cartes du plateau de jeu
 * 
 * @param P Référence vers le plateau de jeu
 */
void créer_cartes(Plateau &P);

/**
 * @brief Teste s'il reste au moins 2 joueurs en positif dans la partie.
 * @param P Le plateau de jeu.
 * @return true s'il reste au moins 2 joueurs en positif, sinon false.
 */
bool fin(Plateau &P);

/**
 * @brief Teste si le joueur en cours est en négatif ou pas.
 * @param joueur_qui_joue Le joueur dont on veut vérifier le solde.
 * @return true si le joueur est en négatif, sinon false.
 */
bool joueur_en_negatif(Joueur *joueur_qui_joue);



#endif