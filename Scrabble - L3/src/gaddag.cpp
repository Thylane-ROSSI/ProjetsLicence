#include "gaddag.hpp"

/* GADDAG */

void GADDAG::initialiser_GADDAG()
{
    std::fstream fichier("../data/dico.txt");  
    std::string mot;
    
    while(fichier >> mot)
    {
        transformer_plus(mot);  // Chaque mot est transformé avec + puis ajouté dans le GADDAG
    }
}


void GADDAG::ajouter_mot(std::string mot)  
{
    Noeud* courant;
    courant = &racine;  

    for(const char& c : mot)
    {
        int index = c - 'A';  
        if(c == '+') { index = 26; }

        if(courant->fils[index] == nullptr)  // Si l’arête n’existe pas encore
        {
            Noeud* nouveau_noeud = new Noeud;  
            courant->fils[index] = nouveau_noeud;  
        }

        courant = courant->fils[index];  
    }

    courant->terminal = true;  
}

// Fonction de recherche utilisée pour tester un mot dans le Gaddag 
bool GADDAG::recherche(std::string mot)
{
    
    Noeud* courant;
    courant = &racine;

    for(const char& c : mot)
    {
        int index = c - 'A';
        if(c == '+') index = 26;

        if(courant->fils[index] == nullptr)  
        {
            //std::cout << "le mot n'existe pas" << std::endl;
            return false;
        }

        courant = courant->fils[index];  
    }

    if(courant->terminal)  
    {
        //std::cout << "le mot est trouvé" << std::endl;
        return true;
    }

    //std::cout << "le mot n'existe pas" << std::endl;
    return false;
}


void GADDAG::transformer_plus(std::string mot)
{ 
    for(int i = 0; i < mot.size(); i++)
    {
        std::string transfo_mot = "";

        //on ajoute les lettres en ordre inversé jusqu'à l’indice i
        for (int j = i; j >= 0; j--)
        {
            transfo_mot += mot[j];
        }

        transfo_mot += "+";  // On met le +

        // On ajoute le reste du mot normalement
        for (int k = i + 1; k < mot.size(); k++)
        {
            transfo_mot += mot[k];
        }

        ajouter_mot(transfo_mot);  
    }
}
