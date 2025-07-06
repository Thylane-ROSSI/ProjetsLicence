#include "Joueur.h"

#include <iostream>
#include <stdlib.h>

using namespace std;


Joueur::Joueur(){
    pseudo = " ";
    argent = 1500; 
    etat_prison = 0; 
    position = 0;
    carte_prison = 0;
    position_x = 900; 
    position_y = 900;
    joueur_neg = 0; // Le joueur_neg passe à 1 quand son argent passe en négatif, du moment qu'il passe à 1, il ne peut plus jouer
}


 
string Joueur:: get_pseudo(){ return pseudo; } 
int Joueur::get_argent(){ return argent; }
int Joueur::get_etat_prison(){ return etat_prison; } 
int Joueur::get_position(){ return position; }
TableauDynamique Joueur::get_carte_joueur(){ return carte_joueur; } 
TableauDynamique Joueur::get_carte_gare(){ return carte_gare; }
TableauDynamique Joueur::get_carte_services_publics(){ return carte_services_publics; }
int Joueur::get_carte_prison(){ return carte_prison; }
int Joueur::get_position_x (){ return position_x; }
int Joueur::get_position_y (){ return position_y; }
int Joueur::get_joueur_neg(){ return joueur_neg; }


void Joueur::set_pseudo(string p){ pseudo = p; }
void Joueur::set_argent(int a){ argent = argent + a; }
void Joueur::set_etat_prison(int ep){ etat_prison = ep; }
void Joueur::set_position(int c){ position = c; }
void Joueur::set_carte_joueur(ElementTD cj){ carte_joueur.ajouterElement(cj); }
void Joueur:: set_carte_gare(ElementTD cg){ carte_gare.ajouterElement(cg); }
void Joueur::set_carte_services_publics(ElementTD csp){carte_services_publics.ajouterElement(csp);}
void Joueur::ajouter_carte_prison(){ carte_prison ++; }
void Joueur::retirer_carte_prison(){ carte_prison --; }
void Joueur::set_position_x (int x){ position_x = position_x + x; }
void Joueur::set_position_y (int y){ position_y = position_y + y; }
void Joueur::set_joueur_neg(int e){ joueur_neg = e; }