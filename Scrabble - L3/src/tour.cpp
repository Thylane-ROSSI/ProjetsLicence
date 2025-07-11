#include "tour.hpp"

Tour::Tour(Board b){
    max_score = 0;                      
    meilleur_coup = nullptr;           
    num_tour = 0;                      
    a_tester.push_back(112); // On met 112 cest la case du milieu     
}

void Tour::init_nouveau_tour(Board b) {

    a_tester.clear();                 
    pile_etats.clear();               
    max_score = 0;                   
    meilleur_coup = nullptr;          

    // On définit les bords du plateau pour traiter les cas particuliers
    std::set<int> droite = {29, 44, 59, 74, 89, 104, 119, 134, 149, 164, 179, 194, 209};
    std::set<int> gauche = {15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195};
    std::set<int> bas = {211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223};
    std::set<int> haut = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    // On parcourt toutes les cases du plateau
    for (int i = 0; i < 225; i++) {

        // Si la case est vide 
        if (b.spots[i].letter == 0) {

        // On va maintenant compter le nombre de voisins occupés
        int voisins_occupes = 0;

        // Cas particuliers : les coins du plateau
        if (i == 0) { // Coin haut gauche
            if (b.spots[i + 15].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i + 1].letter != 0) 
            {
                voisins_occupes++;
            }
        }
        else if (i == 14) { // Coin haut droit
            if (b.spots[i + 15].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i - 1].letter != 0) 
            {
                voisins_occupes++;
            }
        }
        else if (i == 210) { // Coin bas gauche
            if (b.spots[i - 15].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i + 1].letter != 0) 
            {
                voisins_occupes++;
            }
        }
        else if (i == 224) { // Coin bas droit
            if (b.spots[i - 15].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i - 1].letter != 0) 
            {
                voisins_occupes++;
            }
        }

        // Cas des bords du plateau
        else if (droite.find(i) != droite.end()) { // Bord droit
            if (b.spots[i - 15].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i + 15].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i - 1].letter != 0) 
            {
                voisins_occupes++;
            }
        }
        else if (gauche.find(i) != gauche.end()) { // Bord gauche
            if (b.spots[i - 15].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i + 15].letter != 0) 
             {
                voisins_occupes++;
             }
            if (b.spots[i + 1].letter != 0) 
            {
                voisins_occupes++;
            }
        }
        else if (bas.find(i) != bas.end()) { // Bord bas
            if (b.spots[i - 15].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i - 1].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i + 1].letter != 0) 
            {
                voisins_occupes++;
            }
        }
        else if (haut.find(i) != haut.end()) { // Bord haut
            if (b.spots[i + 15].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i - 1].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i + 1].letter != 0) 
            {
                voisins_occupes++;
            }
        }

        // Cas général : cases à l’intérieur du plateau
        else {
            if (b.spots[i - 15].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i + 15].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i - 1].letter != 0) 
            {
                voisins_occupes++;
            }
            if (b.spots[i + 1].letter != 0) 
            {
                voisins_occupes++;
            }
        }

        // Si la case est vide mais a au moins un voisin occupé,
        // elle est candidate pour tester un mot
        if (voisins_occupes > 0) {
            a_tester.push_back(i);
        }
    }
    }   
}
