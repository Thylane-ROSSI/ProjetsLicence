#ifndef CARTES_FONCTIONS_H
#define CARTES_FONCTIONS_H

#include "Joueur.h"
#include "Plateau.h"

// Déclaration des fonctions des cartes
/**
 * @brief Cette fonction est associée à la carte "Erreur de la banque".
 * 
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
    void erreur_de_la_banque(Joueur* joueur_qui_joue);
    /**
 * @brief Cette fonction est associée à la carte "Banque verse dividende".
 * 
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
    void banque_verse_dividende(Joueur* joueur_qui_joue);

 /**
 * @brief cette fonction est associée à la carte "Aller en prison".
 * 
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void aller_prison(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Aller à la case départ".
 * 
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void aller_case_départ(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Héritage".
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void héritage(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Accident de voiture".
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void accident_de_voiture(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Libéré de prison".
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void libéré_de_prison(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Gare université Lyon 1".
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void gare_univ_lyon_1(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Vente de stock".
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void vente_stock(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Vétérinaire".
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void veterinaire(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Intérêt sur obligation".
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void interet_sur_obligation(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Hôpital".
 * @param joueur_qui_joue Le joueur qui joue la carte.
 * @param P Le plateau de jeu.
 */
void hopital(Joueur* joueur_qui_joue, Plateau &P);

/**
 * @brief Cette fonction est associée à la carte "Deuxième prix concours".
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void deuxieme_prix_concours(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Premier prix mots croisés".
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void premier_prix_mot_croisés(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Deambu 3".
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void deambu_3(Joueur* joueur_qui_joue);

/**
 * @brief Cette fonction est associée à la carte "Anniversaire du poisson". 
 * @param joueur_qui_joue Le joueur qui joue la carte.
 */
void anniv_poisson(Joueur* joueur_qui_joue);

#endif // CARTES_FONCTIONS_H
