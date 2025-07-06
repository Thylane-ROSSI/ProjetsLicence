#ifndef _CARTE_IMMO_H
#define _CARTE_IMMO_H

#include "Joueur.h"
#include <string>
using namespace std;
/**
 * @class CarteImmo
 * @brief La classe CarteImmo représente une carte immobilière dans un jeu.
 */
class CarteImmo {

    private: 
    string type; 
    string nom; 
    string couleur; 
    Joueur* etat; 
    int prix_achat, prix_complet, prix_non_complet, prix_1maison, prix_2maisons,
    prix_3maisons, prix_4maisons, prix_avec_hotel, prix_maison, prix_hotel, prix_actuel_a_payer;
    int position;

    public:
    /**
     * @brief Constructeur de la classe CarteImmo.
     * @param ty Type de la carte.
     * @param n Nom de la carte.
     * @param coul Couleur de la carte.
     * @param prix_a Prix d'achat de la carte.
     * @param prix_c Prix avec le groupe complet de la carte.
     * @param prix_non_c Prix avec le groupe non complet de la carte.
     * @param prix_1 Prix avec 1 maison de la carte.
     * @param prix_2 Prix avec 2 maisons de la carte.
     * @param prix_3 Prix avec 3 maisons de la carte.
     * @param prix_4 Prix avec 4 maisons de la carte.
     * @param prix_avec_h Prix avec un hôtel de la carte.
     * @param prix_m Prix d'une maison de la carte.
     * @param prix_h Prix d'un hôtel de la carte.
     * @param pos Position de la carte sur le plateau.
     * @param prix_actu Prix actuel à payer pour la carte.
     */
    CarteImmo(string ty, string n, string coul, int prix_a, int prix_c, int prix_non_c,  int prix_1,  int prix_2,
    int prix_3,  int prix_4, int prix_avec_h, int prix_m, int prix_h, int pos, int prix_actu); //constructeur

     /**
     * @brief Cette fonction recupére le type de la carte.
     * @return Le type de la carte.
     */

    string get_type();
  /**
     * @brief Cette fonction recupére le nom de la carte.
     * @return Le nom de la carte.
     */
    string get_nom(); 
    /**
     * @brief Cette fonction recupére la couleur de la carte.
     * @return La couleur de la carte.
     */

    string get_couleur(); 
    /**
     * @brief Cette fonction recupére l'état de la carte.
     * @return L'état de la carte.
     */
    Joueur* get_etat();
    /**
     * @brief Cette fonction recupére le prix d'achat de la carte.
     * @return le prix d'achat de la carte.
     */
    int get_prix_achat(); 
    /**
     * @brief Cette fonction recupére le prix avec le groupe complet de la carte.
     * @return le prix avec le groupe complet de la carte.
     */
    int get_prix_complet(); 
    /**
     * @brief Cette fonction recupére le prix avec le groupe non complet de la carte.
     * @return le prix avec le groupe non complet de la carte.
     */
    int get_prix_non_complet(); 
    /**
     * @brief Cette fonction recupére le prix avec une maison de la carte.
     * @return le prix avec 1 maison de la carte.
     */
    int get_prix_1maison(); 
    /**
     * @brief Cette fonction recupére le prix avec deux maisons de la carte.
     * @return le prix avec 2 maisons de la carte.
     */
    int get_prix_2maisons(); 
     /**
     * @brief Cette fonction recupére le prix avec trois maisons de la carte.
     * @return le prix avec trois maisons de la carte.
     */
    int get_prix_3maisons(); 
     /**
     * @brief Cette fonction recupére le prix avec quatre maisons de la carte.
     * @return le prix avec quatre maisons de la carte.
     */

    int get_prix_4maisons(); 
    /**
     * @brief Cette fonction recupére le prix avec un hotel de la carte.
     * @return le prix avec un hotel de la carte.
     */

    int get_prix_avec_hotel(); 
    /**
     * @brief Cette fonction recupére le prix d'une maison de la carte.
     * @return le prix d'une maison de la carte.
     */
    int get_prix_maison(); 
    /**
     * @brief Cette fonction recupére le prix d'un hotel de la carte.
     * @return le prix d'un hotel de la carte.
     */
    int get_prix_hotel(); 
     /**
     * @brief Cette fonction recupére la position de la carte.
     * @return le prix la positionde la carte.
     */
    int get_position();
     /**
     * @brief Cette fonction recupére le prix actuel à payer de la carte.
     * @return le prix actuel à payer de la carte.
     */
    int get_prix_actuel_a_payer();
     /**
     * @brief Cette fonction recupére Modifie le prix actuel à payer pour la carte.
     * @param prix_actu Le nouveau prix actuel à payer pour la carte.
     */
    void set_prix_actuel_a_payer(int prix_actu); 
    /**
     * @brief Cette fonction change l'état de la carte en lui assignant un nouveau propriétaire.
     * @param p Un pointeur vers le nouveau propriétaire de la carte.
     */
    void change_etat(Joueur* p);
    /**
     * @brief Cette fonction modifie le type de la carte.
     * @param t Le nouveau type de la carte.
     */
    void set_type(string t);
    /**
     * @brief Cette fonction modifie le nom de la carte.
     * @param n Le nouveau nom de la carte.
     */
    void set_nom(string n);
    /**
     * @brief Cette fonction modifie la couleur de la carte.
     * @param coul La nouvelle couleur de la carte.
     */
    void set_couleur(string coul);
    /**
     * @brief Cette fonction modifie le prix d'achat de la carte.
     * @param pa Le nouveau prix d'achat de la carte.
     */
    void set_prix_achat(int pa);
     /**
     * @brief Cette fonction modifie le prix complet de la carte.
     * @param pc Le nouveau prix complet de la carte.
     */
    void set_prix_complet(int pc);
     /**
     * @brief Cette fonction modifie le prix non complet de la carte.
     * @param pnc Le nouveau prix non complet de la carte.
     */
    void set_prix_non_complet(int pnc );
     /**
     * @brief Cette fonction modifie le prix avec une maison de la carte.
     * @param p1m Le nouveau prix avec une maison de la carte.
     */
    void set_prix_1maison(int p1m);
     /**
     * @brief Cette fonction modifie le prix avec deux maisons de la carte.
     * @param p2m Le nouveau prix avec deux maisons de la carte.
     */
    void set_prix_2maisons(int p2m);
     /**
     * @brief Cette fonction modifie le prix avec trois maisons de la carte.
     * @param p3m Le nouveau prix avec trois maisons de la carte.
     */
    void set_prix_3maisons(int p3m);
    /**
     * @brief Cette fonction modifie le prix avec quatre maisons de la carte.
     * @param p4m Le nouveau prix avec quatre maisons de la carte.
     */
    void set_prix_4maisons(int p4m);
    /**
     * @brief Cette fonction modifie le prix avec hotel de la carte.
     * @param pah Le nouveau prix avec hotel de la carte.
     */
    void set_prix_avec_hotel(int pah);
    /**    
     * @brief Cette fonction modifie le prix d'une maison de la carte.
     * @param pm Le nouveau prix d'une maison de la carte.
     */
    void set_prix_maison(int pm);
    /**    
     * @brief Cette fonction modifie le prix d'un hotel de la carte.
     * @param ph Le nouveau prix d'un hotel de la carte.
     */
    void set_prix_hotel(int ph);
};



#endif