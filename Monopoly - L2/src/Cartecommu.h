#ifndef _CARTE_CO
#define _CARTE_CO

#include <string>
using namespace std;
/**
 *@class Cartecommmu 
 *@brief Cartecommmu est une classe qui représente les cartes communautaires du jeu de Monopoly. 
*/
class Cartecommu
{
    private: 
    string action;
    int id;

    public:
    /**
     * @brief Constructeur de la classe Cartecommu .
     * @param a une chaîne de caractère qui représente l'action de la carte communautaires .
     * @param i un entier qui représente l'identifiant de la carte communautaires .
    */
    Cartecommu(string a , int i);// constructeur
    /**
     * @brief Cette fonction renvoie l'identifiant de la carte .
     * @return l'identifiant de la carte. 
    */
    int get_id(); 
    /**
     * @brief Cette fonction renvoie l'action de la carte .
     * @return l'action de la carte .
    */
    string get_action();

};


#endif 