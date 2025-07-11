#include <gtkmm.h>
#include <iostream>
#include <vector>

#include "Joueur.h"
#include "Plateau.h"

class DialogPseudosJoueurs : public Gtk::Dialog {
public:
    DialogPseudosJoueurs(int nbJoueurs) {
        set_title("Entrer les pseudos des joueurs");
        set_default_size(300, 150);

        Gtk::Box* boite = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
        get_content_area()->pack_start(*boite, Gtk::PACK_SHRINK, 0);

        for (int i = 0; i < nbJoueurs; ++i) {
            Gtk::Entry* champSaisie = Gtk::manage(new Gtk::Entry());
            champSaisie->set_placeholder_text("Pseudo du joueur " + std::to_string(i + 1));
            champsSaisie.push_back(champSaisie);
            boite->pack_start(*champSaisie, Gtk::PACK_SHRINK, 0);
        }

        add_button("Valider", Gtk::RESPONSE_OK);
        show_all_children();
    }

    std::vector<std::string> obtenirPseudosJoueurs() const {
        std::vector<std::string> pseudos;
        for (const auto& champSaisie : champsSaisie) {
            pseudos.push_back(champSaisie->get_text());
        }
        return pseudos;
    }

private:
    std::vector<Gtk::Entry*> champsSaisie;
};

std::vector<std::string> demanderPseudosJoueurs(int nbJoueurs) {
    DialogPseudosJoueurs dialogue(nbJoueurs);
    dialogue.run();
    return dialogue.obtenirPseudosJoueurs();
}


void entrer_les_pseudos(int nb_joueurs, Plateau &P)
{
    vector<Joueur*> joueurs;

    std::vector<std::string> pseudos = demanderPseudosJoueurs(nb_joueurs);

    for (const auto& pseudo : pseudos) {
        Joueur *jou = new Joueur;
        jou->set_pseudo(pseudo);
        joueurs.push_back(jou);
    }
    
    for (Joueur *joueur : joueurs) {
        P.ajouter_joueur(joueur);
    }

}
