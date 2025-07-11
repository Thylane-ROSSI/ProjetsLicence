#include "Cartechance.h"

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

Cartechance::Cartechance(string a , int i)
{
    id= i ;  
    action = a ;  
}

int Cartechance::get_id(){ return id; }

string Cartechance::get_action(){ return action; }

