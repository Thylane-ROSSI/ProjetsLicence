#ifndef _PLATEAU_H
#define _PLATEAU_H
#include "Joueur.h"
#include "TableauDynamique.h"

/**
 * @class Plateau 
 * @brief cette classe represente le plateau du jeu de monopoly
*/
class Plateau {

private:
    int nbre_joueur;
    ElementTD c[40];
    TableauDynamique j;
    int compteur_argent; 

public:
     /**
     * @brief constructeur de la classe plateau. 
     * @param nb nombre de joueur sur le plateau . 
    */
    Plateau(int nb);
    /**
     * @brief cette fonction renvoie l'élément de la case à la position spécifiée sur le plateau
     * @param pos la position de la case sur le plateau 
     * @return l'élément de la case à la position spécifiée sur le plateau
    */
    ElementTD getcase(int pos);
    /**
     * @brief cette fonction renvoie le tableau dynamique des joueurs dans le plateau.
     * @return  le tableau dynamique des joueurs dans le plateau.
    */
    TableauDynamique get_j();
    /**
     * @brief cette fonction renvoie un pointeur sur le joueur .
     * @param a l'indice du joueur .
     * @return un pointeur sur joueur .
    */
    Joueur* get_joueur(int a);
    /**
     * @brief cette fonction renvoie le nombre de joueur sur le plateau . 
     * @return le nombre de joueur sur le plateau . 
    */
    int get_nbjoueur();
    /**
     * @brief cette fonction renvoie un compteur d'argent .
     * @return le compteur d'argent .
    */
    int getcompteur_argent();
    /**
     * @brief cette fonction modifie un compteur d'argent .
     * @param c la nouvelle valeur d'argent 
    */
    void setcompteur_argent(int c);
    /**
     * @brief cette fonction modifie le nombre de joueurs sur le plateau .
     * @param n le nouveau nombre de joueurs sur le plateau.
    */
    void set_nbjoueur(int n);
     /**
     * @brief Ajoute un joueur au tableau dynamique des joueurs sur le plateau.
     * @param p1 Le joueur à ajouter.
     */
    void ajouter_joueur(Joueur* p1);
    /**
     * @brief Ajoute une carte à la position spécifiée sur le plateau.
     * @param carte La carte à ajouter.
     * @param pos La position où ajouter la carte.
     */

    void ajouter_carte(ElementTD carte, int pos);
};
#endif
