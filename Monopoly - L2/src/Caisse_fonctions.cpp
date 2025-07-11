#include "Caisse_fonctions.h"
using namespace std;

void erreur_de_la_banque (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(200); 
}

void banque_verse_dividende (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(50); 
}

void aller_prison (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_position(10); 
    joueur_qui_joue->set_etat_prison(3);
    joueur_qui_joue->set_position_x(-joueur_qui_joue->get_position_x()+50); 
    joueur_qui_joue->set_position_y(-joueur_qui_joue->get_position_y()+900); 
    
}

void aller_case_départ (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_position(0); 
    joueur_qui_joue->set_argent(200);
    joueur_qui_joue->set_position_x(-joueur_qui_joue->get_position_x()+900); 
    joueur_qui_joue->set_position_y(-joueur_qui_joue->get_position_y()+900); 
}

void héritage(Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(100);
}

void accident_de_voiture (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(-150);
}

void libéré_de_prison(Joueur* joueur_qui_joue)
{
    joueur_qui_joue->ajouter_carte_prison();
}

void gare_univ_lyon_1 (Joueur* joueur_qui_joue)
{
    if (joueur_qui_joue->get_position()>25)
    {
        joueur_qui_joue->set_argent(200);
    }
    joueur_qui_joue->set_position(25);
    joueur_qui_joue->set_position_x(-joueur_qui_joue->get_position_x()+810); 
    joueur_qui_joue->set_position_y(-joueur_qui_joue->get_position_y()+50);
}

void vente_stock(Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(50);
}

void veterinaire(Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(-75);
}

void interet_sur_obligation (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(25);
}

void hopital (Joueur* joueur_qui_joue, Plateau &P)
{
    joueur_qui_joue->set_argent(-100);
    P.setcompteur_argent(100);
}

void deuxieme_prix_concours (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(10);
}

void premier_prix_mot_croisés (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(100);
}

void deambu_3 (Joueur* joueur_qui_joue)
{
    if (joueur_qui_joue->get_position()>1)
    {
        joueur_qui_joue->set_argent(200);
    }
    joueur_qui_joue->set_position(1);
    joueur_qui_joue->set_position_x(-joueur_qui_joue->get_position_x()+815); 
    joueur_qui_joue->set_position_y(-joueur_qui_joue->get_position_y()+900);
}

void anniv_poisson (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(-15);
}

