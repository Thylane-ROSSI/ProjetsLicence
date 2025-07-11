#include "sac.hpp"

/* Joueur */

class Joueur
{ 
    public:
        char main[7];
        int nombre_dans_main; // On utilise plus vraiment car on met des 0 à la place des lettres utilisées

        void initialiser_main(Sac &sac); 
        Joueur();
        bool remplir_la_main(Sac &sac); 
        void afficher_main(); 
}; 