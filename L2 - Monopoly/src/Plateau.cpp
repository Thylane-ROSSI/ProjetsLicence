#include "Plateau.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

Plateau::Plateau(int nb){
    nbre_joueur=nb;
    compteur_argent=0;
}


ElementTD Plateau::getcase(int pos){
    return c[pos];
}

Joueur* Plateau::get_joueur(int a) 
{

    ElementTD e = j.valeurIemeElement(a);
    return *static_cast<Joueur**>(static_cast<void *>(&e));

}



int Plateau::getcompteur_argent(){ return compteur_argent; }

int Plateau:: get_nbjoueur(){ return nbre_joueur; }

TableauDynamique Plateau::get_j(){ return j; }


void Plateau::setcompteur_argent(int c){ compteur_argent=c; }

void Plateau:: set_nbjoueur (int n){ nbre_joueur = n; }

void Plateau::ajouter_joueur(Joueur* p1){ 
    j.ajouterElement(const_cast<ElementTD>(static_cast<void*>(p1)));
    nbre_joueur++;
    }

void Plateau::ajouter_carte(ElementTD carte, int pos){ c[pos] = carte; }