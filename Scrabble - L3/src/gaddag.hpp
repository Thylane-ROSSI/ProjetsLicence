#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <string.h>

#include "noeud.hpp"

/* GADDAG */

class GADDAG {
    public:
    
    Noeud racine; 

    void ajouter_mot(std::string mot); 
    bool recherche(std::string mot);
    void transformer_plus(std::string mot); 
    void initialiser_GADDAG();

};