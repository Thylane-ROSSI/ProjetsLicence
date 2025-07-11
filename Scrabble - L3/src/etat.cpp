
#include "etat.hpp"

/* état */

Etat::Etat(char main_actuelle[7], Noeud* noeud_courant, int index, Board nouveau_b, int horizon, int verticale, int depart , int score_perp) // A l'initialisation on donne forcément la racine en noeud courant et le spot 112 (milieu) pour le début
{
    for(int i=0; i<7; i++)
    {
        main_joueur[i] = main_actuelle[i];
    }
    noeud_courant_gaddag = noeud_courant; 
    index_actuel = index; 
    b = nouveau_b; 
    direction_h = horizon; 
    direction_v = verticale; 
    index_départ = depart;
    score_perpendiculaire = score_perp;

     
}
