#include <vector>
#include <algorithm>

#include "tour.hpp"


/* Jeu */

class Jeu{

    public:
    Board board; 
    Joueur j; 
    GADDAG g; 
    Etat etat_courant; 
    Tour t;
    Sac s; 

    Jeu(); 
    ~Jeu();

    Etat* trouver_meilleur_coup();

    bool case_vide(Etat* a_analyser); 
    bool case_occupee(Etat* a_analyser); 

    void échanger_une_lettre();
    bool mot_est_valide(int index, const Board& board, bool horizontal);
    int calculer_score(Etat* etat);

    void facteurs_a_1();
};

void mettre_sur_pile(std::vector<Etat> &pile, Etat etat_courrant);
Etat depiler(std::vector<Etat> &pile); 
