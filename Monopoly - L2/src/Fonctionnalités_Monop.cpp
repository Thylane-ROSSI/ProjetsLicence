#include "Fonctionnalités_Monop.h"
#include <iostream>
#include <stdlib.h>

#include <string>
#include <cstdlib>
#include <cassert>
#include <random>
#include <time.h>
#include <fstream>

#include <vector>

#include <jsoncpp/json/json.h>


void tout_supprimer(Plateau &P)
{
    for(int i=0; i<P.get_nbjoueur(); i++)
    {
        // Supprimer tous les tableaux dynamiques de la classe joueur
        delete P.get_joueur(i)->get_carte_gare().ad; 
        delete P.get_joueur(i)->get_carte_joueur().ad;
        delete P.get_joueur(i)->get_carte_services_publics().ad;
    }    
    delete[] P.get_j().ad;
}

int lancer_les_dés() {
    int dé1 = rand() % 6 + 1; 
    int dé2 = rand() % 6 + 1;
    int res = dé1 + dé2;
    return res;
}


void piocher_carteschances(Plateau &P, Joueur* joueur_qui_joue,SDL_Renderer* renderer, TTF_Font* font){

    vector<Cartechance*> Cartechance;
    ifstream cartechance("data/Carte_chance.json");
    if(!cartechance.is_open()){
        cout << "Impossible d'ouvrir le fichier JSON de cartes chance." <<endl;

    }
    Json::Value root;
    Json::CharReaderBuilder reader;
    Json::parseFromStream(reader, cartechance , &root, nullptr);

    int tab[] = {3, 3, 3, 5, 5, 6, 6, 2, 2, 2, 16, 16, 14, 14, 15, 15, 8, 10, 10, 12, 12, 12, 9, 9, 1, 7, 4, 4, 4, 11, 11, 13};
    int n = rand()% 31 + 0 ; 
    int ac = tab [n];
    
    for(const auto& elt : root){

        int i=elt["id"].asInt();

        if (i==ac && i==1){ aller_case_départ_2(joueur_qui_joue);  afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==2){ libéré_de_prison_2(joueur_qui_joue);  afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==3){ remboursement_impot(joueur_qui_joue); afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==4){ erreur_hopital(joueur_qui_joue);  afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==5){ frais_scolarité(joueur_qui_joue);  afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==6){ salaire(joueur_qui_joue); afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==7){ par_terre(joueur_qui_joue);  afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==8){ braquage(joueur_qui_joue);  afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==9){ nautibus(joueur_qui_joue); afficher_carte_chance(P,renderer,font, i); cout<<"ici"<<flush;}

        else if (i==ac && i==10){ BU(joueur_qui_joue); afficher_carte_chance(P,renderer,font, i);} 

       else if (i==ac && i==11){ dentiste(joueur_qui_joue); afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==12){ code_route(joueur_qui_joue); afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==13){ soudoyez(joueur_qui_joue);  afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==14){ anniversaire(joueur_qui_joue);  afficher_carte_chance(P,renderer,font, i);}

        else if (i==ac && i==15){ vol_passeport(joueur_qui_joue);  afficher_carte_chance(P,renderer,font, i);}
        
       else if (i==ac && i==16){ voyage(joueur_qui_joue);  afficher_carte_chance(P,renderer,font, i);}

    }
    
}


void piocher_cartescommu(Plateau &P, Joueur* joueur_qui_joue,SDL_Renderer* renderer, TTF_Font* font){

    vector<Cartecommu*> Cartecommu;

    ifstream cartecommu("data/Carte_commu.json");

    if(!cartecommu.is_open()){
        cout << "Impossible d'ouvrir le fichier JSON de cartes commu." <<endl;

    }
    Json::Value root;
    Json::CharReaderBuilder reader;
    Json::parseFromStream(reader, cartecommu , &root, nullptr);

    int tab[] = {3, 3, 3, 5, 5, 6, 6, 2, 2, 2, 16, 16, 14, 14, 15, 15, 8, 10, 10, 12, 12, 12, 9, 9, 1, 7, 4, 4, 4, 11, 11, 13};

    int c = rand() % 33 ; 

    int act = tab [c];


    if (root.empty()) {
    cout << "Le tableau root est vide." << endl;
    } else {
     for(const auto& elt : root){

        int id = elt["id"].asInt();

         if (id==act && id==1){ erreur_de_la_banque(joueur_qui_joue); afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==2){ banque_verse_dividende(joueur_qui_joue);  afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==3){ aller_prison(joueur_qui_joue); afficher_carte_commu(P,renderer,font, id);}
        
        else if (id==act && id==4) {aller_case_départ(joueur_qui_joue); afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==5){ héritage(joueur_qui_joue);  afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==6){ accident_de_voiture(joueur_qui_joue);  afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==7){ libéré_de_prison(joueur_qui_joue); afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==8){ gare_univ_lyon_1(joueur_qui_joue); afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==9){ vente_stock(joueur_qui_joue);  afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==10){ veterinaire(joueur_qui_joue);  afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==11){ interet_sur_obligation(joueur_qui_joue);  afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==12){ hopital(joueur_qui_joue, P);  afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==13){ deuxieme_prix_concours(joueur_qui_joue);  afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==14){ premier_prix_mot_croisés(joueur_qui_joue); afficher_carte_commu(P,renderer,font, id);}
        
       else if (id==act && id==15){ deambu_3(joueur_qui_joue); afficher_carte_commu(P,renderer,font, id);}

        else if (id==act && id==16){ anniv_poisson(joueur_qui_joue); afficher_carte_commu(P,renderer,font, id);}
     }
}
}

bool lancer_de_prison(Plateau &P, Joueur* joueur_qui_joue, SDL_Renderer* renderer, TTF_Font* font)
{
    int dé1 = rand() % 6 + 1; 
    int dé2 = rand() % 6 + 1;

    if (dé1==dé2){
            afficher_commentaire(P, renderer, font, "Bravo ! Vous avez fait un double ! Vous pouvez sortir de prison. ", 5000);
            joueur_qui_joue->set_etat_prison(0); // si l'état est 0 , le joueur est libéré
            return true;
        }

    else {
        afficher_commentaire(P, renderer, font, "Dommage ! Pas de double", 5000);
        joueur_qui_joue->set_etat_prison(joueur_qui_joue->get_etat_prison()-1);
        return false;
    }
}


void payer_50 (Joueur* joueur_qui_joue)
{
    joueur_qui_joue->set_argent(-50);
    joueur_qui_joue->set_etat_prison(0);
}


void utiliser_carte_prison(Joueur* joueur_qui_joue)
{
    joueur_qui_joue->retirer_carte_prison();
    joueur_qui_joue->set_etat_prison(joueur_qui_joue->get_etat_prison()-1);
}



void acheter_maison(Joueur* joueur_qui_joue, Plateau &P, SDL_Renderer* renderer, TTF_Font* font) {

    

    afficher_commentaire(P, renderer, font, "Voulez-vous mettre une maison sur cette case ? Appuyer sur Appuyez sur O pour oui et N pour non.", 3000); //Durée indéterminée

    ElementTD case_du_joueur = P.getcase(joueur_qui_joue->get_position());
    SDL_Event immobi;
    string input_text = "";

    CarteImmo* carte_du_joueur = static_cast<CarteImmo*>(static_cast<void*>(case_du_joueur));

     bool choix_fait = false;
                        bool oui = false, non = false;
                        while (!choix_fait) {
                            SDL_PumpEvents(); // Mettre à jour l'état du clavier
                            const Uint8* keystates = SDL_GetKeyboardState(nullptr);
                            if (keystates[SDL_SCANCODE_O])
                            {   // L'utilisateur a appuyé sur la touche O
                                //afficher_commentaire(P, renderer, font, "Super !", 5000);
                                choix_fait = true;
                                oui = true; 
                            } 
                            else if (keystates[SDL_SCANCODE_N]) 
                            {   // L'utilisateur a appuyé sur la touche N
                                //afficher_commentaire(P, renderer, font, "OK", 5000);
                                choix_fait = true;
                                non = true;
                            }
                            SDL_Delay(100); // Délai pour éviter la surconsommation de ressources, processeur en "pause" pendant qu'il attend une touche 100ms à chaque fois
                        }

                        // Effacer le commentaire quand le joueur a fait son choix
                        SDL_RenderClear(renderer);
                        afficher_jeu_static(P, renderer, font);
                        SDL_RenderPresent(renderer);

                        //*** Il veut acheter la carte ***//
                        if (oui) 
                        {

                        /*** Le joueur a le groupe complet, il veut acheter la première maison ***/
                        if (carte_du_joueur->get_prix_actuel_a_payer() == carte_du_joueur->get_prix_complet())
                            {
                                if (assez_dargent_pour_maison_ou_hotel(joueur_qui_joue, carte_du_joueur->get_prix_1maison()))
                                {

                                    joueur_qui_joue->set_argent(-carte_du_joueur->get_prix_maison());
                                    carte_du_joueur->set_prix_actuel_a_payer(carte_du_joueur->get_prix_1maison()); 
                                    afficher_commentaire(P, renderer, font, "Vous avez 1 maison !", 5000);
                                }
                                else { afficher_commentaire(P, renderer, font, "Vous n'avez pas assez d'argent", 5000); }
                            }

                        /*** Le joueur a 1 maisons, il veut acheter la deuxième maison ***/
                        else if (carte_du_joueur->get_prix_actuel_a_payer() == carte_du_joueur->get_prix_1maison())
                            {
                                if (assez_dargent_pour_maison_ou_hotel(joueur_qui_joue, carte_du_joueur->get_prix_2maisons()))
                                {
                                    joueur_qui_joue->set_argent(-carte_du_joueur->get_prix_maison());
                                    carte_du_joueur->set_prix_actuel_a_payer(carte_du_joueur->get_prix_2maisons()); 
                                    afficher_commentaire(P, renderer, font, "Vous avez 2 maisons !", 5000);
                                }
                                else { afficher_commentaire(P, renderer, font, "Vous n'avez pas assez d'argent", 5000); }
                            }

                        /*** Le joueur a 2 maisons, il veut acheter la troisième maison ***/
                        else if (carte_du_joueur->get_prix_actuel_a_payer() == carte_du_joueur->get_prix_2maisons())
                            {
                                if (assez_dargent_pour_maison_ou_hotel(joueur_qui_joue, carte_du_joueur->get_prix_3maisons()))
                                {
                                    joueur_qui_joue->set_argent(-carte_du_joueur->get_prix_maison());
                                    carte_du_joueur->set_prix_actuel_a_payer(carte_du_joueur->get_prix_3maisons());
                                    afficher_commentaire(P, renderer, font, "Vous avez 3 maisons !", 5000);
                                }
                                else { afficher_commentaire(P, renderer, font, "Vous n'avez pas assez d'argent", 5000); }
                            }

                        /*** Le joueur a 3 maisons, il veut acheter la quatrième maison ***/
                        else if (carte_du_joueur->get_prix_actuel_a_payer() == carte_du_joueur->get_prix_3maisons())
                            {
                                if (assez_dargent_pour_maison_ou_hotel(joueur_qui_joue, carte_du_joueur->get_prix_4maisons()))
                                {
                                    joueur_qui_joue->set_argent(-carte_du_joueur->get_prix_maison());
                                    carte_du_joueur->set_prix_actuel_a_payer(carte_du_joueur->get_prix_4maisons()); 
                                    afficher_commentaire(P, renderer, font, "Vous avez 4 maisons !", 5000);
                                }
                                else { afficher_commentaire(P, renderer, font, "Vous n'avez pas assez d'argent", 5000); }
                            }

                        /*** Le joueur a 4 maisons, il veut acheter l'hôtel ***/
                        else if (carte_du_joueur->get_prix_actuel_a_payer() == carte_du_joueur->get_prix_4maisons())
                            {
                                if (assez_dargent_pour_maison_ou_hotel(joueur_qui_joue, carte_du_joueur->get_prix_hotel()))
                                {
                                    joueur_qui_joue->set_argent(-carte_du_joueur->get_prix_hotel());
                                    carte_du_joueur->set_prix_actuel_a_payer(carte_du_joueur->get_prix_avec_hotel()); 
                                    afficher_commentaire(P, renderer, font, "Vous avez 1 hôtel !", 5000); 
                                }
                                else { afficher_commentaire(P, renderer, font, "Vous n'avez pas assez d'argent", 5000); }
                            }
                        }
                        else if (non)
                        {
                            afficher_commentaire(P, renderer, font, "OK", 4000);
                        }
       

                    
    }




bool assez_dargent_pour_maison_ou_hotel(Joueur* joueur_qui_joue, int prix_a_payer)
{
    if(joueur_qui_joue->get_argent()<prix_a_payer)
    {
        return false;
    }
    return true; 
}


void créer_cartes(Plateau &P)
{
    vector<CarteImmo*> CarteImmobiliere;
    vector<Gare*> CarteGare;
    vector<Servicepublic*> CarteSP;

    // Charger le fichier JSON
    ifstream les_cartes("data/Carte.json");

    if (!les_cartes.is_open()) {
        cout << "Impossible d'ouvrir le fichier JSON." <<endl;
}

    Json::Value root;
    Json::CharReaderBuilder reader;
    Json::parseFromStream(reader, les_cartes, &root, nullptr);

    for(const auto& elt : root){


        string typ = elt["type"].asString();

        if(typ == "Immo")
        {
            CarteImmo* ptr_cImmo = new CarteImmo(typ, elt["nom"].asString(), elt["couleur"].asString(),elt["prix_achat"].asInt(),elt["prix_complet"].asInt(),elt["prix_non_complet"].asInt(),elt["prix_1maison"].asInt(),elt["prix_2maisons"].asInt(),elt["prix_3maisons"].asInt(),
            elt["prix_4maisons"].asInt(),elt["prix_avec_hotel"].asInt(),elt["prix_maison"].asInt(),elt["prix_hotel"].asInt(),elt["position"].asInt(), elt["prix_non_complet"].asInt());

            CarteImmobiliere.push_back(ptr_cImmo);
        }
        else if( typ == "Gare"){ 
            Gare* ptr_gare = new Gare(typ,elt["nom"].asString(), elt["loyer_1"].asInt(),elt["loyer_2"].asInt(),elt["loyer_3"].asInt(), elt["loyer_4"].asInt(),elt["prix_achat"].asInt(), elt["position"].asInt(),elt["prix_actuel"].asInt());
            CarteGare.push_back(ptr_gare);

         }
         else if( typ == "Service_public"){ 
            Servicepublic* ptr_sp = new Servicepublic(elt["prix_achat"].asInt(), elt["position"].asInt(),elt["nom"].asString(),typ);
            CarteSP.push_back(ptr_sp);
         }

    }
            for (CarteImmo *carteIm : CarteImmobiliere) {
                ElementTD carte_a_mettre = const_cast<ElementTD>(static_cast<void*>(carteIm));
                P.ajouter_carte(carte_a_mettre,carteIm->get_position());

    }
            for (Gare *carteG : CarteGare) {
                ElementTD carte_a_mettre = const_cast<ElementTD>(static_cast<void*>(carteG));
                P.ajouter_carte(carte_a_mettre,carteG->get_position());
}

            for (Servicepublic *carteS : CarteSP) {
                ElementTD carte_a_mettre = const_cast<ElementTD>(static_cast<void*>(carteS));
                P.ajouter_carte(carte_a_mettre,carteS->get_position());
}
}



bool fin (Plateau &P){

    int cp ;

    for (int i=0 ; i<P.get_nbjoueur(); i++){

        if (P.get_joueur(i)->get_argent()>0){
            cp++;
        }

    }
    return cp<2;
}

bool joueur_en_negatif(Joueur * joueur_qui_joue){
    if (joueur_qui_joue->get_argent()<0)
    {
        joueur_qui_joue->set_joueur_neg(1);
    }
    return joueur_qui_joue->get_argent()>0;
}