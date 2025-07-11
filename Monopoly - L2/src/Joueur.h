#ifndef _JOUEUR_H
#define _JOUEUR_H


#include "TableauDynamique.h"
#include <string>
using namespace std;

/**
 * @class Joueur 
 *@brief cette classe représente un joueur du Jeu de Monopoly 
*/
class Joueur{

    private: 
    string pseudo;
    int argent; 
    int etat_prison;
    int position; 
    TableauDynamique carte_joueur; 
    TableauDynamique carte_gare;
    TableauDynamique carte_services_publics;
    int carte_prison; //compteur de cartes libéré de prison
    int position_x;
    int position_y; 
    int joueur_neg;

    public: 
    /**
     * @brief constructeur de la classe Joueur . 
    */
    Joueur(); 
    /**
     * @brief cette fonction renvoie le pseudo du joueur .
     * @return le pseudo du joueur .
    */
    string get_pseudo(); 
    /**
     * @brief cette fonction renvoie l'argent que le joueur possède .
     * @return l'argent du joueur .
    */
    int get_argent();
    /**
     * @brief cette fonction renvoie l'état du prison du joueur .
     * @return l'état du prison du joueur .
    */ 
    int get_etat_prison(); 
    /**
     * @brief cette fonction renvoie la position du joueur sur le plateau .
     * @return la position du joueur sur le plateau.
    */
    int get_position(); 
    /**
     * @brief cette fonction renvoie les cartes que le joueur posséde .
     * @return les cartes que le joueur posséde .
    */
    TableauDynamique get_carte_joueur(); 
    /**
     * @brief cette fonction renvoie les cartes de gare que le joueur posséde .
     * @return les cartes de gare que le joueur posséde .
    */
    TableauDynamique get_carte_gare(); 
    /**
     * @brief cette fonction renvoie les cartes de services publics que le joueur posséde .
     * @return les cartes de service publics que le joueur posséde.
    */
    TableauDynamique get_carte_services_publics();
    /**
     * @brief Cette fonction renvoie le nombre de cartes que le joueur possède pour sortir de prison.
     * @return  le nombre de cartes que le joueur possède pour sortir de prison.
    */
    int get_carte_prison();
    /**
     * @brief cette fonction renvoie la position x .
     * @return la position x 
    */
    int get_position_x();
    /**
     * @brief cette fonction renvoie la position y . 
     * @return la position y .
    */
    int get_position_y();
    /**
     * @brief Cette fonction passele joueur à 1 quand son argent passe en négatif, du moment qu'il passe à 1, il ne peut plus jouer.
     * @return 1 si l'argent du joueur passe en négatif . 
    */
    int get_joueur_neg();

    /**
     * @brief cette fonction modifie le pseudo du joueur .
     * @param p le pseudo du joueur .
    */
    void set_pseudo(string p);
    /**
     * @brief cette fonction modifie l'argent que le joueur possède . 
     * @param a l'argent que le joueur possède .
    */
    void set_argent(int a);
    /**
     * @brief cette fonction modifie l'etat du prison du joueur. 
     * @param ep l'etat du prison du joueur . 
    */
    void set_etat_prison(int ep);
    /**
     * @brief cette fonction modifie la position du joueur su le plateau . 
     * @param c position du joueur sur le plateau . 
    */
    void set_position(int c);
    /**
     * @brief cette fonction modifie les cartes que le joueur posséde.
     * @param cj les cartes que le joueur posséde.
    */
    void set_carte_joueur(ElementTD cj); 
    /**
     * @brief cette fonction modifie les cartes de gare que le joueur posséde.
     * @param cg les cartes de gare que le joueur posséde.
    */
    void set_carte_gare(ElementTD cg); 
    /**
     * @brief cette fonction modifie les cartes de services publics que le joueur posséde. 
     * @param csp les cartes de services publics que le joueur posséde. 
    */
    void set_carte_services_publics(ElementTD csp);
    /**
     * @brief cette fonction ajoute une carte prison pour le joueur . 
    */
    void ajouter_carte_prison();
    /**
     * @brief cette fonction retire une carte prisom pour le joueur . 
    */
    void retirer_carte_prison();
    /**
     * @brief cette fonction modifie la valeur de la poistion x .
     * @param x la nouvelle valeur de la position x .
    */
    void set_position_x(int x);
    /**
     * @brief cette fonction modifie la valeur de la position y . 
     * @param y la nouvelle valeur de la position y . 
    */
    void set_position_y(int y);
    /**
     * @brief cette fonction modifie la valeur du joueur selon son argent . 
     * @param e la nouvelle valeur du joueur .
    */
    void set_joueur_neg(int e);

};

#endif