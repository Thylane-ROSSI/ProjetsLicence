#include "Cartecommu.h"

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

Cartecommu::Cartecommu(string a , int i)
{
    id= i ;  
    action = a ;  
}

int Cartecommu::get_id(){ return id; }

string Cartecommu::get_action(){ return action; }

