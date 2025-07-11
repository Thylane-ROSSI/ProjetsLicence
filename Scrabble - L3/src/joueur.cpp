#include "joueur.hpp"

/* Joueur */

// Initialise la main du joueur avec 7 lettres piochées dans le sac
void Joueur::initialiser_main(Sac &sac){
    nombre_dans_main = 7;  
    for(int i = 0; i < 7; i++) {
        main[i] = sac.piocher(); 
    }
}


Joueur::Joueur(){
    Sac s;  
    nombre_dans_main = 0;  
    initialiser_main(s);   
}

bool Joueur::remplir_la_main(Sac &sac){
    char lettre;
    for(int i = 0; i < 7; i++) {
        if(main[i] == '0') {  
            lettre = sac.piocher(); 
            if(lettre == ' ') {// Le sac est vide il a pas réussi à piocher
               
                return false;
            } else {
                main[i] = lettre;  
            }
        }
    }
    return true; 
}

// Affiche la main du joueur
void Joueur::afficher_main() {
    static const char* grey = "\033[1;90m";  
    static const char* reset = "\033[0m";   

    // le haut des cases
    for (int i = 0; i < 7; i++) {
        std::cout << grey << "+---+" << reset << " ";
    }
    std::cout << std::endl;

    //les lettres dans leur case
    for (int i = 0; i < 7; i++) {
        std::cout << grey << "|" << reset << " " << main[i] << " " << grey << "|" << reset << " ";
    }
    std::cout << std::endl;

    // le bas des cases
    for (int i = 0; i < 7; i++) {
        std::cout << grey << "+---+" << reset << " ";
    }
    std::cout << std::endl;
}
