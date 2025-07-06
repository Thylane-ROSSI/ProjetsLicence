#ifndef _GARE_H
#define _GARE_H

#include "Joueur.h"

#include <string>
#include<iostream>

using namespace std;

/**
 * @class Gare
 * @brief La classe gare représentant une gare dans le jeu Monopoly.
 */

class Gare {

    private:

        string type;
        Joueur*etat;
        string nom;
        int loyer_1;
        int loyer_2;
        int loyer_3;
        int loyer_4;
        int prix_achat;
        int position;
        int prix_actuel;

    public: 

    /**
     * @brief Constructeur de la classe Gare.
     * 
     * @param t Le type de la gare (gare).
     * @param n Le nom de la gare.
     * @param l1 Le loyer lorsque 1 gare est possédée.
     * @param l2 Le loyer lorsque 2 gares sont possédées.
     * @param l3 Le loyer lorsque 3 gares sont possédées.
     * @param l4 Le loyer lorsque 4 gares sont possédées.
     * @param pa Le prix d'achat de la gare.
     * @param posi La position de la gare sur le plateau.
     * @param p_a Le prix actuel à payer pour la gare.
     */
        Gare (string t, string n , int l1, int l2, int l3, int l4, int pa, int posi, int p_a);//constructeur par copie

    /**
     * @brief cette fonction renvoie le type de la gare.
     * 
     * @return Le type de la gare.
     */
    string get_type();

    /**
     * @brief cette fonction renvoie le nom de la gare.
     * 
     * @return Le nom de la gare.
     */
    string get_nom();

    /**
     * @brief  cette fonction renvoie le prix actuel à payer pour la gare.
     * 
     * @return Le prix actuel à payer pour la gare.
     */
    int get_prixactuel();

    /**
     * @brief cette fonction renvoie l'état de la gare (propriétaire).
     * 
     * @return Le propriétaire de la gare.
     */
    Joueur* get_etat();

    /**
     * @brief cette fonction renvoie le prix d'achat de la gare.
     * 
     * @return Le prix d'achat de la gare.
     */
    int get_prix_achat();

    /**
     * @brief cette fonction renvoie le loyer lorsque 1 gare est possédée.
     * 
     * @return Le loyer lorsque 1 gare est possédée.
     */
    int get_loyer_1();

    /**
     * @brief cette fonction renvoie le loyer lorsque 2 gares sont possédées.
     * 
     * @return Le loyer lorsque 2 gares sont possédées.
     */
    int get_loyer_2();

    /**
     * @brief cette fonction renvoie le loyer lorsque 3 gares sont possédées.
     * 
     * @return Le loyer lorsque 3 gares sont possédées.
     */
    int get_loyer_3();

    /**
     * @brief cette fonction renvoie le loyer lorsque 4 gares sont possédées.
     * 
     * @return Le loyer lorsque 4 gares sont possédées.
     */
    int get_loyer_4();

    /**
     * @brief cette fonction renvoie la position de la gare sur le plateau.
     * 
     * @return La position de la gare sur le plateau.
     */
    int get_position();

    /**
     * @brief cette fonction modifie le prix actuel à payer pour la gare.
     * 
     * @param p_a Le nouveau prix actuel à payer pour la gare.
     */
    void set_prixactuel(int p_a);

    /**
     * @brief cette fonction change le propriétaire de la gare.
     * 
     * @param e Le nouveau propriétaire de la gare.
     */
    void change_e(Joueur* e);

    /**
     * @brief cette fonction modifie la position de la gare sur le plateau.
     * 
     * @param posi La nouvelle position de la gare sur le plateau.
     */
    void set_position(int posi);
};


#endif




    






