#include"ServicePublic.h"

#include <string>
#include<iostream>

using namespace std;

Servicepublic::Servicepublic(int pa , int p, string n , string t){

    prix_achat=pa;
    position=p;
    nom=n;
    type=t;
    etat = nullptr; 
}


string Servicepublic::get_nom(){return nom;}

int Servicepublic::get_prixachat(){return prix_achat;} // renvoie le prix d'achat

int Servicepublic::get_position(){return position;} //renvoie la position du joueur

string Servicepublic::get_type(){return type;} //renvoie le type de la gare

Joueur* Servicepublic::get_etat(){ return etat; }
         
void Servicepublic::set_position(int p){position=p;}

void Servicepublic::set_prixachat(int pa){prix_achat=pa;}

void Servicepublic::change_e(Joueur* e){if (etat == nullptr) { etat = e; } 
                                    else etat = nullptr;}

            