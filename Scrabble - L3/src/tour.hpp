#include <vector>
#include <set>

#include "etat.hpp"

class Tour {
public:

    // Liste des positions sur le plateau qu’on doit tester pour poser un mot
    std::vector<int> a_tester;

    // Pile d’états explorés pendant le tour, utilisée pour générer et tester des coups
    std::vector<Etat*> pile_etats;

    // Score maximal trouvé pendant ce tour
    int max_score;

    Etat* meilleur_coup;

    int num_tour;

    Tour(Board b);

    void init_nouveau_tour(Board b);
};
