#include "Chance_fonctions.h"
using namespace std;

void aller_case_départ_2 (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_position(0); 
    joueur_qui_joue->set_argent(200);
    joueur_qui_joue->set_position_x(-joueur_qui_joue->get_position_x()+900); 
    joueur_qui_joue->set_position_y(-joueur_qui_joue->get_position_y()+900); 
}

void libéré_de_prison_2(Joueur* joueur_qui_joue)
{
    joueur_qui_joue->ajouter_carte_prison();
}

void remboursement_impot (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(30);
}

void erreur_hopital (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(100);
}

void frais_scolarité (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(-50);
}

void salaire (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(100);
}

void par_terre (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(50);
}

void braquage(Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(350);
}

void nautibus (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_position(39);
    joueur_qui_joue->set_position_x(-joueur_qui_joue->get_position_x()+900); 
    joueur_qui_joue->set_position_y(-joueur_qui_joue->get_position_y()+815); 
}

void BU (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(-15); 
}
void dentiste (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(-75);
}

void code_route (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(-30);
}

void soudoyez (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(-50);
}

void anniversaire (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(100);
}

void vol_passeport (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(-50);
}

void voyage (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(100);
}


