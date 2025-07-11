#ifndef _SERV_H
#define _SERV_H

#include "Joueur.h"

#include <string>
#include<iostream>
using namespace std;

/**
 * @class Servicepublic
 * @brief La classe Servicepublic représente une carte de service public dans Monopoly .
 */
class Servicepublic {

    private:

        int prix_achat;
        Joueur*etat;
        int position;
        string nom;
        string type;
    
    public:
    
        /**
         * @brief Constructeur de la classe Servicepublic.
         * @param pa Le prix d'achat de la carte de service public.
         * @param p La position de la carte de service public sur le plateau.
         * @param n Le nom de la carte de service public.
         * @param t Le type de la carte de service public.
         */
        Servicepublic(int pa , int p, string n , string t );
        
        // Destructeur
        
        /**
         * @brief Cette fonction obtient le nom de la carte de service public.
         * @return Le nom de la carte de service public.
         */
        string get_nom(); 

        /**
         * @brief Cette fonction obtient le prix d'achat de la carte de service public.
         * @return Le prix d'achat de la carte de service public.
         */
        int get_prixachat(); 

        /**
         * @brief Cette fonction obtient la position de la carte de service public sur le plateau.
         * @return La position de la carte de service public.
         */
        int get_position(); 

        /**
         * @brief Cette fonction obtient le type de la carte de service public.
         * @return Le type de la carte de service public.
         */
        string get_type(); 

        /**
         * @brief Cette fonction obtient l'état actuel de la carte de service public.
         * @return L'état actuel de la carte de service public.
         */
        Joueur* get_etat(); 
         
        /**
         * @brief Cette fonction modifie la position de la carte de service public.
         * @param p La nouvelle position de la carte de service public.
         */
        void set_position(int p);

        /**
         * @brief Cette fonction modifie le prix d'achat de la carte de service public.
         * @param pa Le nouveau prix d'achat de la carte de service public.
         */
        void set_prixachat(int pa);

        /**
         * @brief Cette fonction change l'état de la carte de service public.
         * @param e Le nouveau joueur propriétaire de la carte de service public.
         */
        void change_e(Joueur* e);

};







#endif