#include "sac.hpp"

/* Sac */

Sac::Sac() {

        char lettre[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        // Nombre pour chaque lettre dans le sac
        int nombre[] = {9, 2, 2, 3, 15, 2, 2, 2, 8, 1, 1, 5, 3, 6, 6, 2, 1, 6, 6, 6, 6, 2, 1, 1, 1, 1};

        // Points de chaque lettre
        int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 10, 1, 2, 1, 1, 3, 8, 1, 1, 1, 1, 4, 10, 10, 10, 10};

        total_lettres = 0; // compteur total de lettres dans le sac

        // On initialise chaque case du tableau de lettres
        for (int i = 0; i < 26; i++) {
            sac_de_lettres[i].lettre = lettre[i];
            sac_de_lettres[i].nombre = nombre[i];
            sac_de_lettres[i].points = points[i];
            total_lettres += nombre[i];
        }
}

// Affiche le contenu du sac
void Sac::afficher_sac() {
        std::cout << "Dans le sac de lettres il reste " << total_lettres << " lettres\n";
        for (int j = 0; j < 26; j++) {
            std::cout << "lettre :" << sac_de_lettres[j].lettre
                      << " nombre :" << sac_de_lettres[j].nombre
                      << " Point :" << sac_de_lettres[j].points << "\n"; 
        }
}

// Fonction pour piocher une lettre au hasard dans le sac
char Sac::piocher() {
    if (total_lettres <= 0) { // Le sac est vide
        return ' ';  
    }

    // On choisit un numéro aléatoire entre 0 et total_lettres - 1
    int k = rand() % total_lettres;
    int somme_courante = 0;

    for (int i = 0; i < 26; i++) {
        somme_courante += sac_de_lettres[i].nombre; // On additionne le nombre de la lettre courante 

        // Dès qu’on dépasse ou atteint l’index aléatoire on pioche cette lettre
        if (k < somme_courante) {
            sac_de_lettres[i].nombre -= 1;     
            total_lettres -= 1;                
            return sac_de_lettres[i].lettre;
        }
    }

    // Normalement jamais atteint si total_lettres est bon
    return ' ';
}
