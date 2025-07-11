#include "gaddag.hpp"
#include "joueur.hpp"
#include "board.hpp"

/* état */

class Etat{
    public:
     
    char main_joueur[7]; // Copie de la main du Joueur pour pouvoir la modifier sans casser la main du Joueur
    Noeud* noeud_courant_gaddag; 
    //Spot* position_courante; // A initialiser à la cas 112 du plateau car c'est le milieu du plateau et c'est là où la partie commence
    int index_actuel; 
    int index_départ; // Index de départ pour la gestion du +, savoir où se trouvait au début la première case a analyser
    Board b; 
    int direction_h;
    int direction_v; 
    int score_perpendiculaire; // Score du mot perpendiculaire formé par le coup joué

    Etat(char main_actuelle[7], Noeud* noeud_courant, int index, Board new_b, int horizon, int verticale, int depart, int score_perp );

}; 
