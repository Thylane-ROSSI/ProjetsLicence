#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <string.h>

#include "lettre.hpp"

/* Sac */

class Sac{

    public: 

    lettre sac_de_lettres[26];  
    int total_lettres; 

    Sac(); 

    void afficher_sac(); 

    char piocher();
}; 
