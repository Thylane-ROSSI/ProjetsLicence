#ifndef _CARTE_C
#define _CARTE_C

#include <string>
using namespace std;

/**
 * @class CarteChance 
 * @brief Cartechane est  une classe qui représente les cartes chance du jeu de Monopoly..
*/

class Cartechance
{
    private: 
    string action;
    int id;

    public:
    /**
     *@class Constructeur de la classe Cartechance .
     *@param a une chaîne de caractère qui représente l'action de la carte.
     *@param i un entier qui représente l'identifiant unique à la carte .

    */
    Cartechance(string a , int i);// constructeur
      /**
     * @brief Cette fonction renvoie l'identifiant de la carte .
     * @return l'identifiant de la carte .
    */
    int get_id(); 
    /** 
     *@brief Cette fonction renvoie l'actin de la carte . 
     @return l'action de la carte .
    */
    string get_action();

};


#endif 
