#include "Tour_joueur.h"

#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <string>
#include <cstdlib>
#include <cassert>
#include <random>
#include <time.h>
#include <fstream>

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>



using namespace std;

//Fonction qui réalise en fonction du plateau et d'un joueur donné, le tour de ce dernier et le met à jour

int tour_joueur(Plateau &P, Joueur* joueur_qui_joue, SDL_Renderer* renderer, TTF_Font* font, int numero_du_joueur)
{

    if(joueur_en_negatif(joueur_qui_joue)){
    bool garee = false, 
    prison = false, 
    eau_elec = false; 

    afficher_commentaire_demande(P, renderer, font, "Voulez-vous afficher vos cartes immobilères ? Appuyez sur O pour oui et N pour non.");

                    bool choix_fait = false;
                    bool oui = false, non = false;
                    while (!choix_fait) {
                        SDL_PumpEvents(); // Mettre à jour l'état du clavier
                        const Uint8* keystates = SDL_GetKeyboardState(nullptr);
                        if (keystates[SDL_SCANCODE_O]) 
                        {   // L'utilisateur a appuyé sur la touche O
                            choix_fait = true;
                            oui = true;
                            effacer_commentaire(renderer);
                        } 
                        else if (keystates[SDL_SCANCODE_N]) 
                        {   // L'utilisateur a appuyé sur la touche N
                            choix_fait = true;
                            non = true;
                            effacer_commentaire(renderer);
                        }
                    }

                    // Effacer le commentaire quand le joueur a fait son choix
                    afficher_jeu_static(P, renderer, font);
                    SDL_RenderPresent(renderer);

                    //*** Il veut acheter la carte ***//
                    if (oui) 
                        {
                            SDL_RenderClear(renderer);
                            SDL_RenderPresent(renderer);
                            affichercartes(renderer, joueur_qui_joue);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(10000);
                            SDL_RenderClear(renderer);
                            SDL_RenderPresent(renderer);
                            afficher_jeu_static(P, renderer, font);

                        }
                        else if(non){
                            afficher_commentaire(P, renderer,font, "OK !", 3000);
                        }


    // Première chose, tester si le joueur est en prison

if (joueur_qui_joue->get_etat_prison()>0){ 

        prison = true;

        //Initialisation des choix possibles pour sortir de prison
            bool choix_payer = false;
            bool choix_lancer = false;
            bool choix_carte = false;
            bool choix_fait = false;

            //Début des choix pendant le tour

            SDL_Event event;
            prison = true;
            while (prison)
            {

                if (SDL_PollEvent(&event))
                    {       
                        SDL_PumpEvents(); // Mettre à jour l'état du clavier
                        const Uint8* keystates = SDL_GetKeyboardState(nullptr);
                    
        /*** Le joueur a juste le choix de lancer les dés -> Il n'a pas de carte prison et pas assez d'argent pour payer 50€ ***/

                        if(joueur_qui_joue->get_argent()<50 && joueur_qui_joue->get_carte_prison()==0)
                        {
                             afficher_commentaire(P, renderer, font, "Vous avez qu'un seul choix pour sortir de prison! Lancez les dés, si vous faites un double vous sortez !", 5000);
                             lancer_de_prison(P,joueur_qui_joue, renderer, font);
                             prison = false;
                        }


        /*** Le joueur a 2 choix : lancer les dés et payer 50€ pour sortir de prison -> Il n'a pas de carte prison ***/

                        else if (joueur_qui_joue->get_argent()>50 && joueur_qui_joue->get_carte_prison()==0)
                        {

                            afficher_commentaire_demande(P, renderer, font, "Vous avez deux choix pour sortir de prison! Choisissez soit lancer les dés, pour tenter d'obtenir un double, appuyer sur la touche d. Ou payer 50€ pour sortir appuyer sur p.");

                            choix_fait = false;
                            while (!choix_fait) {
                                SDL_PumpEvents(); // Mettre à jour l'état du clavier
                                const Uint8* keystates = SDL_GetKeyboardState(nullptr);

                                if (keystates[SDL_SCANCODE_D]) 
                                {   // L'utilisateur a appuyé sur la touche d
                                    afficher_commentaire(P, renderer, font, "Vous voulez lancer les dés", 5000);
                                    choix_lancer = true;
                                    choix_fait = true;
                                    prison = false;
                                    effacer_commentaire(renderer); 

                                } 

                                else if (keystates[SDL_SCANCODE_P]) 
                                {   // L'utilisateur a appuyé sur la touche p
                                    afficher_commentaire(P, renderer, font, " Vous voulez payer 50€", 5000);
                                    choix_payer = true;
                                    choix_fait = true;
                                    prison = false;
                                    effacer_commentaire(renderer);
                                }

                            }
                            //Faire le choix du joueur
                                if (choix_payer)
                                { 
                                    payer_50(joueur_qui_joue);
                                }

                                else if (choix_lancer)
                                { 
                                    lancer_de_prison(P,joueur_qui_joue, renderer, font);
                                }

                        }

    

        /*** Le joueur a 2 choix de lancer les dés et utiliser une carte sortir -> Le joueur n'a pas assez d'argent pour payer 50€ ***/

            else if (joueur_qui_joue->get_argent()<50 && joueur_qui_joue->get_carte_prison()>0){ 

            afficher_commentaire_demande(P, renderer, font, "Vous avez 2 choix pour sortir de prison ! Choisissez entre utiliser une carte libérer de prison appuyer sur c . Ou lancer les dés et tenter de faire un double appuyer sur d.");

            choix_fait = false;
            while (!choix_fait) {
                SDL_PumpEvents(); // Mettre à jour l'état du clavier
                const Uint8* keystates = SDL_GetKeyboardState(nullptr);

                if (keystates[SDL_SCANCODE_D]) 
                {   // L'utilisateur a appuyé sur la touche d
                    afficher_commentaire(P, renderer, font, "Vous voulez lancer les dés", 5000);
                    choix_lancer = true;
                    choix_fait = true;
                    prison = false;
                    effacer_commentaire(renderer);
                } 

                else if (keystates[SDL_SCANCODE_C]) 
                {   // L'utilisateur a appuyé sur la touche c
                    afficher_commentaire(P, renderer, font, "Vous voulez utiliser une carte libérer de prison", 5000);
                    choix_carte = true;
                    choix_fait = true;
                    effacer_commentaire(renderer);
                }

            }
                
                //Faire le choix du joueur

                if(choix_carte)
                {
                    utiliser_carte_prison(joueur_qui_joue);   
                }

                if (choix_lancer)
                {
                    lancer_de_prison(P,joueur_qui_joue, renderer, font);
                }
            }


        /*** Le joueur a 3 choix de lancer les dés, payer 50€ pour sortir de prison et utiliser carte pour sortir de prison ***/

            else if (joueur_qui_joue->get_argent()>50 && joueur_qui_joue->get_carte_prison()>0){

            afficher_commentaire_demande(P, renderer, font, "Vous avez 3 choix pour sortir de prison ! Soit lancer les dés et tenter de faire un double. Apuyer sur d. Soit payer 50€ appuyer sur p. Soit utiliser une carte libérer de prison appuyer sur c.");

            choix_fait = false;
            while (!choix_fait) {
                SDL_PumpEvents(); // Mettre à jour l'état du clavier
                const Uint8* keystates = SDL_GetKeyboardState(nullptr);

                if (keystates[SDL_SCANCODE_D]) 
                {   // L'utilisateur a appuyé sur la touche d
                    afficher_commentaire(P, renderer, font, " Vous voulez lancer les dés", 5000);
                    choix_lancer = true;
                    choix_fait = true;
                    prison = false;
                    effacer_commentaire(renderer);
                } 
                else if (keystates[SDL_SCANCODE_P]) 
                {   // L'utilisateur a appuyé sur la touche p
                    afficher_commentaire(P, renderer, font, " Vous voulez payer 50€", 5000);
                    choix_payer = true;
                    choix_fait = true;
                    prison = false;
                    effacer_commentaire(renderer);

                }
                else if (keystates[SDL_SCANCODE_C]) 
                {   // L'utilisateur a appuyé sur la touche c
                    afficher_commentaire(P, renderer, font, " Vous voulez utiliser une carte libérer de prison", 5000);
                    choix_carte = true;
                    choix_fait = true;
                    prison = false;
                    effacer_commentaire(renderer);
                }
            }

                if(choix_carte)
                {
                    utiliser_carte_prison(joueur_qui_joue);
                }

                else if(choix_lancer)
                {
                    lancer_de_prison(P,joueur_qui_joue, renderer, font);
                }
                else if (choix_payer)
                {
                    payer_50(joueur_qui_joue);
                }

            }

        }
    }
    return 0; // On termine la fonction si le joueur a fini de jouer son tour prison ou qu'il est sorti de prison il doit attendre le prochain tour pour jouer 
}




/*** Le joueur n'est pas en prison ****/


if(joueur_qui_joue->get_etat_prison()==0){


     //Le joueur lance les dés
     int dé = lancer_les_dés();
     // Afficher la vidéo des dés
     afficher_video();
     afficher_resultat_de(P,renderer, font, dé); //Affichage pendant 5 secondes à l'écran du résulat des dés

    int nouvelle_pos = dé+joueur_qui_joue->get_position();

    if(nouvelle_pos>=40)
    {
        while (joueur_qui_joue->get_position()<40 && joueur_qui_joue->get_position()!=0)
        {
            avancer_pion(renderer,numero_du_joueur,font,P,40-joueur_qui_joue->get_position());
            joueur_qui_joue->set_position(0); 
            joueur_qui_joue->set_position_x(-joueur_qui_joue->get_position_x()+900);
            joueur_qui_joue->set_position_y(-joueur_qui_joue->get_position_y()+900);
        }
        nouvelle_pos = nouvelle_pos - 40;
        avancer_pion(renderer,numero_du_joueur,font,P,nouvelle_pos);
        joueur_qui_joue->set_position(nouvelle_pos); 
        if(nouvelle_pos != 0)
        {
            joueur_qui_joue->set_argent(200);
            afficher_commentaire(P, renderer, font,"Vous êtes passé sur la case départ ! Recevez 200€.",5000);
        }
        
    }
    else{
        avancer_pion(renderer, numero_du_joueur, font, P, dé); 
        joueur_qui_joue->set_position(nouvelle_pos); 
    }
    
    /*** Le joueur est sur la case de piocher une carte communautaire ***/
    if(joueur_qui_joue->get_position()==2 ||
    joueur_qui_joue->get_position()==17 ||
    joueur_qui_joue->get_position()==33)
    {
        afficher_commentaire(P, renderer, font, "Vous piochez une carte de caisse communautaire", 5000);
        piocher_cartescommu(P, joueur_qui_joue, renderer, font);
    }


    /*** Le joueur est sur la case de piocher une carte chance ***/
    else if(joueur_qui_joue->get_position()==7 ||
    joueur_qui_joue->get_position()==22 ||
    joueur_qui_joue->get_position()==36)
    {
        afficher_commentaire(P, renderer, font, "Vous piochez une carte chance", 5000);
        piocher_carteschances(P, joueur_qui_joue, renderer, font);
    }

    /*** Le joueur est sur la case départ ***/

    else if(joueur_qui_joue->get_position()==0)
    {
        joueur_qui_joue->set_argent(200);
        afficher_commentaire(P, renderer, font, "Vous êtes sur la case départ ! Recevez 200€.", 5000);
    }

 
    /*** Si le joueur est sur la case " Aller en prison " ***/

    else if(joueur_qui_joue->get_position()==30) 
    {
        joueur_qui_joue->set_etat_prison(3);
        joueur_qui_joue->set_position(10); 
        joueur_qui_joue->set_position_x(-joueur_qui_joue->get_position_x());
        joueur_qui_joue->set_position_y(-joueur_qui_joue->get_position_y());
        joueur_qui_joue->set_position_x(50); 
        joueur_qui_joue->set_position_y(900); 
        afficher_commentaire(P, renderer, font, "Oh non ! Vous devez aller en prison !", 4000);
    }


    /*** Calcul de la nouvelle case du joueur ***/
    ElementTD case_du_joueur = P.getcase(joueur_qui_joue->get_position());



    if (joueur_qui_joue->get_position() == 1 || /****La case est une case immobilière****/
    joueur_qui_joue->get_position() == 3 || 
    joueur_qui_joue->get_position() == 6 || 
    joueur_qui_joue->get_position() == 8 || 
    joueur_qui_joue->get_position() == 9 || 
    joueur_qui_joue->get_position() == 11 || 
    joueur_qui_joue->get_position() == 13 || 
    joueur_qui_joue->get_position() == 14 || 
    joueur_qui_joue->get_position() == 16 || 
    joueur_qui_joue->get_position() == 18 || 
    joueur_qui_joue->get_position() == 19 || 
    joueur_qui_joue->get_position() == 21 || 
    joueur_qui_joue->get_position() == 23 || 
    joueur_qui_joue->get_position() == 24 || 
    joueur_qui_joue->get_position() == 26 || 
    joueur_qui_joue->get_position() == 27 || 
    joueur_qui_joue->get_position() == 29 || 
    joueur_qui_joue->get_position() == 31 || 
    joueur_qui_joue->get_position() == 32 || 
    joueur_qui_joue->get_position() == 34 || 
    joueur_qui_joue->get_position() == 37 || 
    joueur_qui_joue->get_position() == 39) 
    {

        CarteImmo* carte_associée_a_la_pos = static_cast<CarteImmo*>(static_cast<void*>(case_du_joueur));
        SDL_Event immobi;

/*** Un joueur possède la carte ***/
if(carte_associée_a_la_pos->get_etat() != nullptr){

        /*** Le joueur qui joue possède la carte ***/
        if(joueur_qui_joue->get_pseudo() == carte_associée_a_la_pos->get_etat()->get_pseudo())
        {
            afficher_commentaire(P, renderer, font, "Vous êtes chez vous !",5000);

            //*** Il faut tester si le joueur possède le groupe complet ***//

            int cmpt = 0; //compteur du nombre de cartes du même groupe

            //Parcourir le tableau dynamique de cartes (d'éléments)
            for(int k=0; k<joueur_qui_joue->get_carte_joueur().taille_utilisee; k++)
            {
                CarteImmo* carte_du_joueur = static_cast<CarteImmo*>(static_cast<void*>(joueur_qui_joue->get_carte_joueur().ad[k]));
                if (carte_du_joueur->get_couleur() == carte_associée_a_la_pos->get_couleur())
                {
                    cmpt++;   
                }

            }
            //si la couleur est bleu_clair, rose, orange rouge, jaune ou vert
            //Et qu'il y en a 3  
            //Alors le groupe est complet

            
            //Sinon si la couleur est bleu_foncé ou marron 
            //Et qu'il y en a 2
            //Alors grp complet

            /***  Si le joueur a le groupe complet ***/
            if(((carte_associée_a_la_pos->get_couleur() == "bleu_clair" || 
            carte_associée_a_la_pos->get_couleur() == "rose" ||
            carte_associée_a_la_pos->get_couleur() == "orange" ||
            carte_associée_a_la_pos->get_couleur() == "rouge" ||
            carte_associée_a_la_pos->get_couleur() == "jaune" ||
            carte_associée_a_la_pos->get_couleur() == "vert") && cmpt == 3) || ((carte_associée_a_la_pos->get_couleur() == "bleu_fonce" || 
            carte_associée_a_la_pos->get_couleur() == "marron") && cmpt == 2)){
                        
                        afficher_commentaire_demande(P, renderer, font, "Voulez-vous acheter une maison ou un hôtel ? Appuyez sur O pour oui et N pour non."); // Durée indéfinie PB PAS INFINI ECRIRE FONCTION PARTICULIERE QUI EFFACE PAS SA DEMANDE

                        bool choix_fait = false;
                        bool oui = false, non = false;
                        while (!choix_fait) {
                            SDL_PumpEvents(); // Mettre à jour l'état du clavier
                            const Uint8* keystates = SDL_GetKeyboardState(nullptr);
                            if (keystates[SDL_SCANCODE_O])
                            {   // L'utilisateur a appuyé sur la touche O
                                choix_fait = true;
                                oui = true; 
                                effacer_commentaire(renderer);
                            } 
                            else if (keystates[SDL_SCANCODE_N]) 
                            {   // L'utilisateur a appuyé sur la touche N
                                choix_fait = true;
                                non = true;
                                effacer_commentaire(renderer);
                            }
                        }

                        //*** Il veut acheter la carte ***//
                        if (oui) 
                        {
                            acheter_maison(joueur_qui_joue, P, renderer, font); 
                        }
                        else if(non)
                        {
                            afficher_commentaire(P, renderer, font, "OK", 4000);
                        }
            }
        }

        //**** La carte est déjà achetée par un autre joueur ****//
        if(carte_associée_a_la_pos->get_etat() != nullptr && (carte_associée_a_la_pos->get_etat()->get_pseudo() != joueur_qui_joue->get_pseudo()))
        { 
            joueur_qui_joue->set_argent(-carte_associée_a_la_pos->get_prix_actuel_a_payer()); //Le joueur qui joue perd le loyer à payer
            carte_associée_a_la_pos->get_etat()->set_argent(carte_associée_a_la_pos->get_prix_actuel_a_payer()); //Le joueur qui possède la carte gagne l'argent
            afficher_commentaire(P, renderer, font, "Mince, cette propriété est déjà achetée par "+ carte_associée_a_la_pos->get_etat()->get_pseudo(),5000);
        }



}
/*** Aucun joueur ne possède pas la carte ***/
      else
            {
                    //**** Le joueur n'a pas assez d'argent pour acheter ****//
                    if (joueur_qui_joue->get_argent()<carte_associée_a_la_pos->get_prix_achat())
                    {
                        afficher_commentaire(P, renderer, font, "Vous ne pouvez pas acheter la case, vous n'avez pas assez d'argent !", 5000);
                    }

                    //**** Le joueur a assez d'argent et la carte est pas achetée ****//
                    else if (carte_associée_a_la_pos->get_etat() == nullptr && (joueur_qui_joue->get_argent()>carte_associée_a_la_pos->get_prix_achat())) 
                    {
                        afficher_commentaire_demande(P, renderer, font, "Voulez-vous acheter ? Appuyez sur O pour oui et N pour non.");

                        bool choix_fait = false;
                        bool oui = false, non = false;

                        while (!choix_fait) {
                            SDL_PumpEvents(); // Mettre à jour l'état du clavier
                            const Uint8* keystates = SDL_GetKeyboardState(nullptr);
                            if (keystates[SDL_SCANCODE_O])
                            {   // L'utilisateur a appuyé sur la touche O
                                choix_fait = true;
                                oui = true; 
                                effacer_commentaire(renderer);
                            } 
                            else if (keystates[SDL_SCANCODE_N]) 
                            {   // L'utilisateur a appuyé sur la touche N
                                choix_fait = true;
                                non = true;
                                effacer_commentaire(renderer);
                            }
                        }

                        //*** Il veut acheter la carte ***//
                        if (oui) 
                        {
                            
                                    //Achat de la carte
                                    carte_associée_a_la_pos->change_etat(joueur_qui_joue);
                                    joueur_qui_joue->set_argent(-carte_associée_a_la_pos->get_prix_achat());
                                    joueur_qui_joue->set_carte_joueur(case_du_joueur);
                                    afficher_commentaire(P, renderer, font, "Super !", 5000);


                                    //*** Il faut tester si le joueur possède le groupe complet pour changer les prix actuels du groupe ***//

                                    int cmpt = 0; //compteur du nombre de cartes du même groupe

                                    //Parcourir le tableau dynamique de cartes (d'éléments)
                                    for(int k=0; k<joueur_qui_joue->get_carte_joueur().taille_utilisee; k++)
                                    {
                                        CarteImmo* carte_du_joueur = static_cast<CarteImmo*>(static_cast<void*>(joueur_qui_joue->get_carte_joueur().ad[k]));
                                        if (carte_du_joueur->get_couleur() == carte_associée_a_la_pos->get_couleur())
                                        {
                                            cmpt++;   
                                        }

                                    }
                                    //si la couleur est bleu_clair, rose, orange rouge, jaune ou vert
                                    //Et qu'il y en a 3  
                                    //Alors le groupe est complet

                                    if((carte_associée_a_la_pos->get_couleur() == "bleu_clair" || 
                                    carte_associée_a_la_pos->get_couleur() == "rose" ||
                                    carte_associée_a_la_pos->get_couleur() == "orange" ||
                                    carte_associée_a_la_pos->get_couleur() == "rouge" ||
                                    carte_associée_a_la_pos->get_couleur() == "jaune" ||
                                    carte_associée_a_la_pos->get_couleur() == "vert") && cmpt == 3)
                                    {


                                            afficher_commentaire(P, renderer, font, "Vous avez le groupe complet !", 5000);

                                            // Le prix a payé doit changer pour les 3 cartes du groupe
                                            for(int k=0; k<joueur_qui_joue->get_carte_joueur().taille_utilisee; k++)
                                            {
                                                CarteImmo* carte_du_joueur = static_cast<CarteImmo*>(static_cast<void*>(joueur_qui_joue->get_carte_joueur().ad[k]));
                                                if (carte_du_joueur->get_couleur() == carte_associée_a_la_pos->get_couleur())
                                                {
                                                    carte_du_joueur->set_prix_actuel_a_payer(carte_du_joueur->get_prix_complet()); 
                                                }
                                            }

                                    }

                                    //Sinon si la couleur est bleu_foncé ou marron 
                                    //Et qu'il y en a 2
                                    //Alors grp complet

                                    else if ((carte_associée_a_la_pos->get_couleur() == "bleu_fonce" || 
                                    carte_associée_a_la_pos->get_couleur() == "marron") && cmpt == 2)
                                    {
                                            afficher_commentaire(P, renderer, font, "Vous avez le groupe complet !", 5000);

                                            // Le prix a payé doit changer pour les 2 cartes du groupe
                                            for(int k=0; k<joueur_qui_joue->get_carte_joueur().taille_utilisee; k++)
                                            {
                                                CarteImmo* carte_du_joueur = static_cast<CarteImmo*>(static_cast<void*>(joueur_qui_joue->get_carte_joueur().ad[k]));

                                                if (carte_du_joueur->get_couleur() == carte_associée_a_la_pos->get_couleur())
                                                {
                                                    carte_du_joueur->set_prix_actuel_a_payer(carte_du_joueur->get_prix_complet()); 
                                                }
                                            }
                                    }


                                    }

                                //*** Il ne veut pas l'acheter ***//
                                else if (non)
                                {
                                    afficher_commentaire(P, renderer, font, "OK !", 5000);

                                }
                            
                    }

        }

    }
    
 
/*** La case est une gare ***/

    if (joueur_qui_joue->get_position() == 5 || 
    joueur_qui_joue->get_position() == 15 || 
    joueur_qui_joue->get_position() == 25 || 
    joueur_qui_joue->get_position() == 35) 
    {

        Gare* carte_associée_a_la_pos = static_cast<Gare*>(static_cast<void*>(case_du_joueur));
        garee = true; 
        SDL_Event evt_gare;

         while (garee)
            {
                //**** Le joueur n'a pas assez d'argent ****//
                if (joueur_qui_joue->get_argent()<carte_associée_a_la_pos->get_prix_achat())
                {
                    afficher_commentaire(P, renderer, font, "Vous ne pouvez pas acheter la case, vous n'avez pas assez d'argent !", 5000);
                }

                //**** Le joueur a assez d'argent et la carte est pas achetée ****//
                else if (carte_associée_a_la_pos->get_etat() == nullptr && (joueur_qui_joue->get_argent()>carte_associée_a_la_pos->get_prix_achat())) 
                {
                    afficher_commentaire_demande(P, renderer, font, "Voulez-vous acheter ? Appuyez sur O pour oui et N pour non.");

                        bool choix_fait = false;
                        bool oui = false, non = false;
                    while (!choix_fait) {
                        SDL_PumpEvents(); // Mettre à jour l'état du clavier
                        const Uint8* keystates = SDL_GetKeyboardState(nullptr);
                        if (keystates[SDL_SCANCODE_O]) 
                        {   // L'utilisateur a appuyé sur la touche O
                            choix_fait = true;
                            oui = true;
                            effacer_commentaire(renderer);
                        } 
                        else if (keystates[SDL_SCANCODE_N]) 
                        {   // L'utilisateur a appuyé sur la touche N
                            choix_fait = true;
                            non = true;
                            effacer_commentaire(renderer);
                        }
                    }

                    //*** Il veut acheter la carte ***//
                    if (oui) 
                        {
                            //Achat de la carte
                            carte_associée_a_la_pos->change_e(joueur_qui_joue);
                            joueur_qui_joue->set_argent(-carte_associée_a_la_pos->get_prix_achat());
                            joueur_qui_joue->set_carte_gare(case_du_joueur);
                            afficher_commentaire(P, renderer, font, "Super !" , 4000);

                            //Si 2 gares
                            if(joueur_qui_joue->get_carte_gare().taille_utilisee==2)
                            {
                                carte_associée_a_la_pos->set_prixactuel(carte_associée_a_la_pos->get_loyer_2());
                            }

                            //Si 3 gares
                            if(joueur_qui_joue->get_carte_gare().taille_utilisee==3)
                            {
                                carte_associée_a_la_pos->set_prixactuel(carte_associée_a_la_pos->get_loyer_3());
                            }

                            //Si 4 gares
                            if(joueur_qui_joue->get_carte_gare().taille_utilisee==4)
                            {
                                carte_associée_a_la_pos->set_prixactuel(carte_associée_a_la_pos->get_loyer_4());
                            }

                            garee = false; 
                        
                        }
                            
                        //*** Il ne veut pas l'acheter ***//
                        else if (non)
                        {
                            afficher_commentaire(P, renderer, font, "OK !", 5000);      
                            garee = false; 

                        }
                }

                /*** La carte est déjà achetée et ce n'est pas le joueur qui joue **/
                else if((carte_associée_a_la_pos->get_etat()!= nullptr) && (carte_associée_a_la_pos->get_etat() != joueur_qui_joue))
                {
                    
                    // Au niveau de l'achat de la carte, le programme ne change pas le prix de toutes les cartes gares, il chage seulement le prix de la carte qu'il vient d'acheter. 
                    // C'est pourquoi si on tombe sur la gare où le prix n'a pas été changé, il faut le changer

                    Joueur * joueur_qui_possède = carte_associée_a_la_pos->get_etat();

                    //Si 2 gares
                    if(joueur_qui_possède->get_carte_gare().taille_utilisee==2)
                    {
                        carte_associée_a_la_pos->set_prixactuel(carte_associée_a_la_pos->get_loyer_2());
                    }

                    //Si 3 gares
                    if(joueur_qui_possède->get_carte_gare().taille_utilisee==3)
                    {
                        carte_associée_a_la_pos->set_prixactuel(carte_associée_a_la_pos->get_loyer_3());
                    }

                    //Si 4 gares
                    if(joueur_qui_possède->get_carte_gare().taille_utilisee==4)
                    {
                        carte_associée_a_la_pos->set_prixactuel(carte_associée_a_la_pos->get_loyer_4());
                    }

                    joueur_qui_joue->set_argent(-carte_associée_a_la_pos->get_prixactuel());
                    carte_associée_a_la_pos->get_etat()->set_argent(carte_associée_a_la_pos->get_prixactuel());
                    afficher_commentaire(P, renderer, font, "Mince la gare est déjà achetée", 4000);

                    garee = false; 
                }
                
                else
                {
                    afficher_commentaire(P, renderer, font, "Vous êtes chez vous !", 4000);
                    garee = false;
                } 
                garee = false;
            }

    }



/*** La case est un service publique ***/

if (joueur_qui_joue->get_position() == 12 || joueur_qui_joue->get_position() == 28) {

    Servicepublic* carte_associée_a_la_pos = static_cast<Servicepublic*>(static_cast<void*>(case_du_joueur));

    // Créer deux cases service elec et service eau pour faciliter les testes de possessions
    ElementTD service_elec = P.getcase(12);
    Servicepublic* case_service_elec = static_cast<Servicepublic*>(static_cast<void*>(service_elec));

    ElementTD service_eau = P.getcase(28);
    Servicepublic* case_service_eau = static_cast<Servicepublic*>(static_cast<void*>(service_eau));

    bool eau_elec = true;
    SDL_Event evt_contribution;

    while (eau_elec) {
            // Le joueur n'a pas assez d'argent
            if (joueur_qui_joue->get_argent() < carte_associée_a_la_pos->get_prixachat()) {
                afficher_commentaire(P, renderer, font, "Vous ne pouvez pas acheter la case, vous n'avez pas assez d'argent !", 5000);
                eau_elec = false;
            }
            // Le joueur a assez d'argent et la carte n'est pas achetée
            else if (carte_associée_a_la_pos->get_etat() == nullptr) {
                afficher_commentaire_demande(P, renderer, font, "Voulez-vous acheter ? Appuyez sur O pour oui et N pour non.");

                bool choix_fait = false;
                bool oui = false, non = false;
                while (!choix_fait) {
                    SDL_PumpEvents(); // Mettre à jour l'état du clavier
                    const Uint8* keystates = SDL_GetKeyboardState(nullptr);
                    if (keystates[SDL_SCANCODE_O]) {
                        // L'utilisateur a appuyé sur la touche O
                        choix_fait = true;
                        oui = true;
                        effacer_commentaire(renderer);
                    } else if (keystates[SDL_SCANCODE_N]) {
                        // L'utilisateur a appuyé sur la touche N
                        choix_fait = true;
                        non = true;
                        effacer_commentaire(renderer);
                    }
                }

                // Il veut acheter la carte
                if (oui) {
                    // Achat de la carte
                    carte_associée_a_la_pos->change_e(joueur_qui_joue);
                    joueur_qui_joue->set_argent(-carte_associée_a_la_pos->get_prixachat());
                    joueur_qui_joue->set_carte_services_publics(case_du_joueur);
                    afficher_commentaire(P, renderer, font, "Super !", 5000);
                    eau_elec = false;
                } else if (non) {
                    // Il ne veut pas l'acheter
                    afficher_commentaire(P, renderer, font, "OK !", 5000);
                    eau_elec = false;
                }

                // La carte est déjà achetée et elle n'est pas possédée par le joueur en cours
            } else if (carte_associée_a_la_pos->get_etat() != P.get_joueur(numero_du_joueur)) {
                
                afficher_commentaire(P, renderer, font, "Mince ! Ce service public est déjà acheté !", 4000);
                int dé1, dé2;
                // La carte est déjà achetée et elle est possédé par le même joueur en cours
                if (case_service_eau->get_etat() == case_service_elec->get_etat()) {
                    // Les deux services publics diffénts sont possédés par le même joueur
                    // Le lancers de dés sera multiplié par 10
                    afficher_commentaire(P, renderer, font, "Les services publics sont possédés par le même joueur ! Le résulat de vos dés sera multiplié par 10 !", 5000);
                    int res = lancer_les_dés();
                    res = res * 10;
                    joueur_qui_joue->set_argent(-res); // Le joueur actuel paye
                    case_service_eau->get_etat()->set_argent(res); // Le joueur qui possède gagne l'argent
                    afficher_commentaire(P, renderer, font, "Vous avez payé " + to_string(res), 4000);
                    eau_elec = false;

                } else {
                    // Le joueur ne possède pas les deux services plublics
                    afficher_commentaire(P, renderer, font, "Les services publics ne sont pas possédés par le même joueur ! Le résulat de vos dés sera multiplié par 4 !", 5000);
                    int res = lancer_les_dés();
                    res = res * 4;
                    joueur_qui_joue->set_argent(-res); // Le joueur actuel paye
                    carte_associée_a_la_pos->get_etat()->set_argent(res); // Le joueur qui possède gagne l'argent
                    afficher_commentaire(P, renderer, font, "Vous avez payé " + to_string(res), 4000);
                    eau_elec = false;
                }
            }
            else 
            {
                afficher_commentaire(P, renderer, font, "Vous êtes chez vous !", 4000);
                eau_elec = false;
            }
            eau_elec = false;
        
    }
}

        


        /*** Le joueur est au parc gratuit ***/
        else if(joueur_qui_joue->get_position()==20)
        {
            joueur_qui_joue->set_argent(P.getcompteur_argent());
            string argent_au_milieu = to_string(P.getcompteur_argent()).c_str();
            afficher_commentaire(P, renderer, font, " Vous récupérez l'argent qu'il y a au milieu. "+argent_au_milieu+ " euros.", 5000);
            P.setcompteur_argent(0);
        }


        /*** Le joueur visite la prison ***/
        else if(joueur_qui_joue->get_position()==10 && joueur_qui_joue->get_etat_prison() == 0)
        {
            afficher_commentaire(P, renderer, font, "Vous visitez la prison", 5000);
        }

        /*** Le joueur est sur la 1ère case d'impôts ***/
        else if(joueur_qui_joue->get_position()==4)
        {
            joueur_qui_joue->set_argent(-200);
            P.setcompteur_argent(200);
            afficher_commentaire(P, renderer, font, "Payer les impots sur le revenu, 200 euros", 5000);
        }

        /*** Le joueur est sur la deuxième case d'impôts ***/
        else if(joueur_qui_joue->get_position()==38)
        {
            joueur_qui_joue->set_argent(-100);
            P.setcompteur_argent(100);
            afficher_commentaire(P, renderer, font, "Payer les taxes de luxe, 100 euros", 5000);
        }


    }// Fin de si le joueur n'est pas en prison 
    return 0; 
    }

    return 0; 
} //Fin tour joueur




// Fonction qui lance la partie et qui ne s'arrête pas tant qu'il n'y a pas de gagnant
string lancer_partie(Plateau &P, SDL_Renderer* renderer, TTF_Font* font) {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    afficher_jeu_static(P, renderer, font);
    afficher_commentaire(P, renderer, font, "Bienvenue dans le Monopoly Lyon 1 !", 4000);
    int num_joueur_en_cours = 0;

    SDL_Event event;
    while (!fin(P)) {
        // Gestion des événements SDL
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return ""; // Quitter la partie si l'utilisateur ferme la fenêtre
            }
        }

        if (num_joueur_en_cours == P.get_nbjoueur()) {
            num_joueur_en_cours = 0;
        }

        Joueur* joueur_qui_joue = P.get_joueur(num_joueur_en_cours);
        if(joueur_qui_joue->get_joueur_neg()==0)
        {
            string joueur = "À toi de jouer " + joueur_qui_joue->get_pseudo();
            afficher_commentaire(P,renderer,font,joueur,4000);
            tour_joueur(P, joueur_qui_joue, renderer, font, num_joueur_en_cours);
        }
        else if(joueur_qui_joue->get_joueur_neg()==1)
        {
            string joueur = "Tu as perdu " + joueur_qui_joue->get_pseudo() + " ! Attend que la partie se finisse...";
            afficher_commentaire(P,renderer,font,joueur,3000);
        }
        num_joueur_en_cours++;
    }

    for(int i = 0; i < P.get_nbjoueur(); i++) {
        if(P.get_joueur(i)->get_argent() > 0) {
            return P.get_joueur(i)->get_pseudo();
        }
    }
    return "";
}





