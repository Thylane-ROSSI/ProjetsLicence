#ifndef DIALOG_PSEUDOS_JOUEURS_H
#define DIALOG_PSEUDOS_JOUEURS_H

#include "Joueur.h"
#include "Plateau.h"

#include <iostream>
#include <vector>
#include <gtkmm.h>


/**
 * @brief Classe de dialogue pour entrer les pseudos des joueurs
 */

class DialogPseudosJoueurs : public Gtk::Dialog {
public:
    /**
     * @brief le constructeur prenant le nombre de joueurs en paramètre
     * @param nbJoueurs Le nombre de joueurs à entrer
     */
    DialogPseudosJoueurs(int nbJoueurs);
      /**
     * @brief cette fonction permet d'obtenir les pseudos des joueurs
     * @return Un vecteur de chaînes de caractères contenant les pseudos entrés
     */
    std::vector<std::string> obtenirPseudosJoueurs() const;

private:
    std::vector<Gtk::Entry*> champsSaisie;
};
/**
 * @brief cette fonction permet de demander les pseudos des joueurs via un dialogue
 * @param nbJoueurs Le nombre de joueurs à entrer
 * @return Un vecteur de chaînes de caractères contenant les pseudos entrés
 */
std::vector<std::string> demanderPseudosJoueurs(int nbJoueurs);
/**
 * @brief cette fonction permet d'entrer les pseudos des joueurs
 * @param nb_joueurs Le nombre de joueurs à entrer
 * @param P Référence vers le plateau de jeu
 */
void entrer_les_pseudos(int nb_joueurs, Plateau &P);

#endif // DIALOG_PSEUDOS_JOUEURS_H
