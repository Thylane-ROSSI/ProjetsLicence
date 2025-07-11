#include "jeu.hpp"

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <fstream>




int main() {

    // On init le Jeu de départ --> On a un board vide, ...
    srand(time(nullptr));

    Jeu jeu;
    Etat* meilleur; 
    int score_total = 0; 

    // Affichage de l'état initial du plateau
    std::cout << "Plateau initial:\n";
    std::cout << jeu.board << std::endl;

    // Affichage de la main du joueur
    std::cout << "Main du joueur initiale: "<<std::endl;
    jeu.j.afficher_main();

    std::cout<<"Initialisation du Gaddag..."<<std::endl;
    // Init le Gaddag 
    jeu.g.initialiser_GADDAG();

    // Traitement du premier tour (case milieu 112)
    jeu.t.a_tester = {112};
    meilleur = jeu.trouver_meilleur_coup();

    if (meilleur == nullptr) {
      std::cout << "Aucun coup possible au premier tour. Fin du jeu." << std::endl;
      return 0;
    }


     // Le plateau change apres le premier coup 
     jeu.board = meilleur->b;

     // L'état courant est mis à jour
     jeu.etat_courant = *meilleur; 

    // Affichage de la main du joueur
    std::cout << "Main du joueur après le premier tour : "<<std::endl;
    jeu.j.afficher_main();

    // Affichage de l'état initial du plateau
    std::cout << "Plateau après le premier tour :\n";
    std::cout << jeu.board << std::endl;

     for (int i=0; i<7; i++)
     {
      jeu.j.main[i] = meilleur->main_joueur[i]; 
     }

    jeu.j.remplir_la_main(jeu.s);

    // Dans votre code principal, remplacez l'affichage de la main par ceci:
    std::cout << "Main du joueur encadrée: " << std::endl;
  

    std::cout << std::endl;
    score_total+=jeu.t.max_score;
    std::cout<<"score du premier tour :"<<jeu.t.max_score<<std::endl;
    std::cout<<"score total :"<<score_total<<std::endl;
    std::cout<<"**************"<<std::endl;

    jeu.facteurs_a_1();
    
    while (meilleur != nullptr) {


      // Affichage de la main du joueur
      std::cout << "Main du joueur avant pioche: "<< std::endl;
      jeu.j.afficher_main();

      // Le premier tour est passé, maintenant il faut piocher pour remettre les lettres dans sa main 
      if(jeu.j.remplir_la_main(jeu.s) || meilleur != nullptr){

        // Affichage de la main du joueur
        std::cout << "Main du joueur après pioche: "<< std::endl;
        jeu.j.afficher_main();

        // Initialisation du tour : génère les cases à tester
        jeu.t.init_nouveau_tour(jeu.board);

        // Recherche du meilleur coup possible
        meilleur = jeu.trouver_meilleur_coup();

        if(meilleur != nullptr)
        {
          // Le plateau change apres le premier coup 
          jeu.board = meilleur->b;

          // L'état courant est mis à jour
          jeu.etat_courant = *meilleur; 

          jeu.facteurs_a_1();

          for (int i=0; i<7; i++)
          {
            jeu.j.main[i] = meilleur->main_joueur[i]; 
          }
          
          // Affichage de l'état initial du plateau
          std::cout << "Plateau après avoir mis le meilleur résultat :\n";
          std::cout << jeu.board << std::endl;

          score_total+=jeu.t.max_score;
          std::cout<<"score du tour :"<<jeu.t.max_score<<std::endl;
          std::cout<<"score total :"<<score_total<<std::endl;
          std::cout<<"**************"<<std::endl;
        }
        else{
          std::cout<<"On a pas trouvé de meilleur coup et on ne peut plus piocher\n";
          jeu.s.afficher_sac();
        }
      }
      else{
        std::cout<<"Il n'y a plus de lettres dans le sac\n";
        jeu.s.afficher_sac();
        break; 
      }

}
return 0;
}
