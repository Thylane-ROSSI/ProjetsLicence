#include "CarteImmo.h"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

CarteImmo::CarteImmo(string ty, string n, string coul, int prix_a, int prix_c, int prix_non_c,  int prix_1,  int prix_2,
    int prix_3,  int prix_4, int prix_avec_h, int prix_m, int prix_h, int pos, int prix_actu){
    etat = nullptr;
    type = ty; 
    nom = n; 
    couleur = coul; 
    prix_1maison = prix_1;
    prix_2maisons = prix_2;
    prix_3maisons = prix_3;
    prix_4maisons =prix_4;
    prix_achat = prix_a;
    prix_avec_hotel= prix_avec_h;
    prix_complet= prix_c;
    prix_non_complet= prix_non_c;
    prix_hotel= prix_h;
    prix_maison= prix_m;

    position = pos; 

    prix_actuel_a_payer = prix_actu;

}

string CarteImmo:: get_type(){ return type; }

string CarteImmo:: get_nom(){ return nom; }

string CarteImmo:: get_couleur(){ return couleur; }

Joueur* CarteImmo:: get_etat(){ return etat; }

int CarteImmo:: get_prix_achat() { return prix_achat; }

int CarteImmo:: get_prix_complet() { return prix_complet; }

int CarteImmo:: get_prix_non_complet() { return prix_non_complet; }

int CarteImmo:: get_prix_1maison() { return prix_1maison; }

int CarteImmo:: get_prix_2maisons() { return prix_2maisons; }

int CarteImmo:: get_prix_3maisons() { return prix_3maisons; }

int CarteImmo:: get_prix_4maisons() { return prix_4maisons; }

int CarteImmo:: get_prix_avec_hotel() { return prix_avec_hotel; }

int CarteImmo:: get_prix_maison() { return prix_maison; }

int CarteImmo:: get_prix_hotel() { return prix_hotel; }

int CarteImmo::get_position() { return position; }

void CarteImmo:: change_etat(Joueur* p) { if (etat == nullptr) { etat = p; } 
                                    else etat = nullptr;
                               }
int CarteImmo::get_prix_actuel_a_payer(){ return prix_actuel_a_payer; }

void CarteImmo::set_prix_actuel_a_payer(int prix_actu) { prix_actuel_a_payer = prix_actu; } 

void CarteImmo:: set_type(string t){ type = t; }

void CarteImmo:: set_nom(string n){ nom = n; }

void CarteImmo:: set_couleur(string coul){ couleur = coul; }

void CarteImmo:: set_prix_achat(int pa) { prix_achat = pa; }

void CarteImmo:: set_prix_complet(int pc) { prix_complet = pc; }

void CarteImmo:: set_prix_non_complet(int pnc ) { prix_non_complet = pnc; }

void CarteImmo:: set_prix_1maison(int p1m) { prix_1maison = p1m; }

void CarteImmo:: set_prix_2maisons(int p2m) { prix_2maisons = p2m; }

void CarteImmo:: set_prix_3maisons(int p3m) { prix_3maisons = p3m; }

void CarteImmo:: set_prix_4maisons(int p4m) { prix_4maisons = p4m; }

void CarteImmo:: set_prix_avec_hotel(int pah) { prix_avec_hotel = pah; }

void CarteImmo:: set_prix_maison(int pm) { prix_maison = pm; }

void CarteImmo:: set_prix_hotel(int ph) { prix_hotel = ph; }


