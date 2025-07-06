#include"Gare.h"

#include<iostream>
#include<string>

using namespace std; 

Gare::Gare (string t, string n , int l1, int l2, int l3, int l4, int pa, int posi,int p_a){
    etat=nullptr;
    type=t;
    nom=n;
    loyer_1=l1;
    loyer_2=l2;
    loyer_3=l3;
    loyer_4=l4;
    prix_achat=pa;
    position= posi;
    prix_actuel=p_a;

}
string Gare::get_type(){ return type;} //Renvoie le type de gare , qui est gare 

string Gare::get_nom(){ return nom;} //Renvoie le nom de la gare

int Gare::get_prixactuel(){ return prix_actuel;} //Renvoie le prix actuel à payer 

Joueur* Gare::get_etat(){return etat;} //Renvoie l'état de la gare

int Gare::get_prix_achat(){return prix_achat;}//Renvoie le prix d'achat de la gare

int Gare::get_loyer_1(){return loyer_1;}//Renvoie le loyer d'une gare

int Gare::get_loyer_2(){return loyer_2;}//Renvoie le loyer de deux gares

int Gare::get_loyer_3(){return loyer_3;} //Renvoie le loyer de trois gares

int Gare::get_loyer_4(){return loyer_4;}//Renvoie le loyer de quatres gares

int Gare::get_position(){return position;} //renvoie la position 
        

void Gare::change_e(Joueur* e){ if (etat == nullptr) { etat = e; } 
                                    else etat = nullptr;}

void Gare::set_prixactuel(int p_a){prix_actuel=p_a;}

void Gare::set_position(int posi){position=posi;};






    













    





