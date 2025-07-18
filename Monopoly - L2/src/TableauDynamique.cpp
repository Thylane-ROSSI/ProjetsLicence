#include "TableauDynamique.h"


#include <iostream>
#include <stdlib.h>
using namespace std;

TableauDynamique::TableauDynamique () {
    ad = new ElementTD [1];
    capacite = 1;
    taille_utilisee = 0;
}

TableauDynamique::TableauDynamique (const TableauDynamique & t) {
  ad = new ElementTD [t.capacite];
  capacite = t.capacite;
  taille_utilisee = t.taille_utilisee;
  for (unsigned int i = 0; i < t.taille_utilisee; i++) ad[i] = t.ad[i];
}

TableauDynamique::~TableauDynamique () {
  delete [] ad;
  ad = NULL;
  capacite = 0;
  taille_utilisee = 0;
}

void TableauDynamique::vider () {
  delete [] ad;
  ad = new ElementTD [1];
  capacite = 1;
  taille_utilisee = 0;
}


void TableauDynamique::ajouterElement (ElementTD e) {
  ElementTD * temp;
  if (taille_utilisee == capacite) { // tableau plein, doublons la capacitÃ©
      temp = ad;
      ad = new ElementTD [2*capacite];
      if(ad == NULL) {
          cout << "Espace memoire insuffisant" << endl;
          exit(EXIT_FAILURE);
      }
      capacite *= 2;
      for (unsigned int i = 0; i < taille_utilisee; i++) ad[i] = temp[i];
      delete [] temp;
  }
  ad[taille_utilisee] = e;
  taille_utilisee++;
}

ElementTD TableauDynamique::valeurIemeElement (int indice) const {
  return ad[indice];
}

void TableauDynamique::modifierValeurIemeElement (ElementTD e, unsigned int indice) {
  ad[indice] = e;
}

void TableauDynamique::afficher () const {
  for (unsigned int i = 0; i < taille_utilisee; i++) {
        afficheElementTD(ad[i]);
        cout << " ";
  }
  cout << endl;
}

void TableauDynamique::supprimerElement (unsigned int indice) {
  if(indice < taille_utilisee-1) {
      for(unsigned int p = indice; p < taille_utilisee-1; p++)
        ad[p] = ad[p+1];
  }
  taille_utilisee--;
  if (taille_utilisee < capacite / 3) {
    ElementTD * temp = ad;
    capacite = capacite / 2;
    ad = new ElementTD [capacite];
    for(unsigned int p = 0; p < taille_utilisee; p++)
        ad[p] = temp[p];
    delete [] temp;
  }
}

void TableauDynamique::insererElement (ElementTD e, unsigned int indice) {
  if(taille_utilisee > 0) {
      /* S'il y a au moins un ElementTD dans le tableau, on recopie le dernier
         en appelant la procÃ©dure d'ajout, qui s'occupera d'augmenter la capacitÃ© si nÃ©cessaire */
      ajouterElement(ad[taille_utilisee - 1]);
  }
  /* Ensuite on dÃ©cale d'un cran les Ã©lÃ©ments Ã  droite de indice */
  for (unsigned int j = taille_utilisee - 1; j > indice; j--)
    ad[j] = ad[j-1];
  /* On peut enfin insÃ©rer e Ã  la position indice */
  ad[indice] = e;
}

void TableauDynamique::trier () {
  /* tri par sÃ©lection */
  unsigned int i, j, indmin;
  ElementTD min;
  for (i = 0; i < taille_utilisee - 1; i++) {
      indmin = i;
      for (j = i+1; j < taille_utilisee; j++) {
          if (ad[j] < ad[indmin]) indmin = j;
      }
      min = ad[indmin];
      ad[indmin] = ad[i];
      ad[i] = min;
    }
}

int TableauDynamique::rechercherElement (ElementTD e) const {
  int debutZR, finZR, milieuZR; /* indices de la zone de recherche */
  bool trouve, fini;
  int res;

  if (taille_utilisee < 1) return -1; // tableau vide
  if ((e < ad[0]) || (e > ad[taille_utilisee-1])) return -1; // l'élément recherche n'est pas compris entre le min et le max du tableau

  debutZR = 0;
  finZR = taille_utilisee - 1;
  fini = false;
  trouve = false;
  res = -1;

  while ((!fini) && (!trouve)) {
      milieuZR = (finZR - debutZR)/2 + debutZR;

      if (e == ad[debutZR])     {trouve = true; res = debutZR;}
      if (e == ad[finZR])       {trouve = true; res = finZR;}
      if (e == ad[milieuZR])    {trouve = true; res = milieuZR;}
      if (debutZR == milieuZR)  {fini = true;}

      if ((!trouve) && (!fini)) {
          if(ad[milieuZR] < e) debutZR = milieuZR;
          else finZR = milieuZR;
      }
    }
    return res;
}

