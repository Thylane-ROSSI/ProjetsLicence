#include "gaddag.hpp"

/* GADDAG */

// Charge tous les mots du fichier dictionnaire et les insère dans la structure
void GADDAG::initialiser_GADDAG() {
    std::ifstream fichier("data/dico.txt");
    std::string mot;
    while (fichier >> mot) {
        for (char& c : mot) c = toupper(c);
        ajouter_mot(mot);
        tous_les_mots.push_back(mot);
    }
}


// Ajoute un mot caractère par caractère dans le GADDAG
void GADDAG::ajouter_mot(std::string mot)  
    {
        Noeud* courant;
        courant = &racine;
        for(const char& c : mot)
        {
            int index = c - 'A' ;
            if(courant->fils[index] == nullptr) //L'arrête n'est pas créée
            {
                Noeud* nouveau_noeud = new Noeud; 
                courant->fils[index] = nouveau_noeud; 
            }
            courant = courant->fils[index];
        }
        courant->terminal = true; // Fin du mot changer état du terminal
    }
   
// Vérifie si un mot est présent dans le GADDAG
bool GADDAG::recherche(std::string mot)
    {
        Noeud* courant;
        courant = &racine;
        
        for(const char& c : mot)
        {
            int index = c - 'A' ;
            if(courant->fils[index] == nullptr) //L'arrête n'est pas créée
            {
                std::cout<<"le mot n'existe pas"<<std::endl; 
                return false; 
            }
             courant = courant->fils[index];  
        }
        if(courant->terminal)
        {
            std::cout<<"le mot est dans le Gaddag"<<std::endl; 
            return true;
        }
        std::cout<<"le mot n'est pas dans le Gaddag"<<std::endl;
        return false; 
    }


