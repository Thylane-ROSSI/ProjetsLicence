#include "jeu.hpp"
#include <algorithm>
#include <ctime>
#include <iostream>

using namespace std;

int const max_echanges = 20; 
int compteur = 0;  

/* Jeu */

Jeu::Jeu(): board(), j(), g(), etat_courant(j.main, &g.racine, 112, board, -1, -15, 112 ,0), t(board), s() {}

Jeu::~Jeu() {
    // Nettoyer tous les états restants dans la pile
    for (Etat* etat : t.pile_etats) {
        delete etat;
    }
    t.pile_etats.clear();
    
    // Si meilleur_coup existe encore et n'est pas déjà dans la pile
    if (t.meilleur_coup && std::find(t.pile_etats.begin(), t.pile_etats.end(), t.meilleur_coup) == t.pile_etats.end()) {
        delete t.meilleur_coup;
        t.meilleur_coup = nullptr;
    }
}

void mettre_sur_pile(std::vector<Etat> &pile, Etat etat_courrant){
    pile.push_back(etat_courrant);
}

Etat* depiler(std::vector<Etat*> &pile) {
    if (pile.empty()) {
        return nullptr;  // Retourner nullptr si la pile est vide
    }
    Etat* a_analyser = pile.back();
    pile.pop_back();
    return a_analyser;
}

bool au_bord(int index) {
    std::set<int> droite = {29, 44, 59, 74, 89, 104, 119, 134, 149, 164, 179, 194, 209};
    std::set<int> bas = {211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223};
    std::set<int> gauche = {15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195};
    std::set<int> haut = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    std::set<int> coin = {0, 14, 210, 224};

    return gauche.count(index) || bas.count(index) || droite.count(index) || haut.count(index) || coin.count(index);
}

bool au_bord_g(int index)
{
    std::set<int> gauche = {15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210};

    return gauche.count(index);
}


bool au_bord_d(int index)
{
    std::set<int> droite = {14, 29, 44, 59, 74, 89, 104, 119, 134, 149, 164, 179, 194, 209};

    return droite.count(index);
}

bool au_bord_h(int index)
{
    std::set<int> haut = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    return haut.count(index);
}

bool au_bord_b(int index)
{
    std::set<int> bas = {211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223};

    return bas.count(index);
}

// Vérification si l'index est valide
bool index_valide(int index) {
    return index >= 0 && index < 225; 
}

bool deja_jouer_une_lettre(Etat* a_analyser) {
    if (!a_analyser) { return false; } 

    for (int i = 0; i < 7; i++) {
        if (a_analyser->main_joueur[i] == '0') { return true; } // Si on trouve un '0' cest qu’au moins une lettre a été jouée
    }
    return false; 
}


void Jeu::facteurs_a_1() {
    for (int i = 0; i < 225; i++) {
        // case pas vide
        if (etat_courant.b.spots[i].letter != 0) {

            // On remet le bonus lettre et le bonus mot à 1
            etat_courant.b.spots[i].bonus.letter_factor = 1;
            etat_courant.b.spots[i].bonus.word_factor = 1;
        }
    }

    // On met à jour le plateau principal avec la version modifiée de l'état courant
    board = etat_courant.b;
}
void Jeu::échanger_une_lettre() {
    // Sélectionner une lettre aléatoire de la main
    int index = rand() % 7;
    char lettre_a_remettre = j.main[index];
    
    // Piocher une nouvelle lettre du sac
    char nouvelle_lettre = s.piocher();
    
    if (nouvelle_lettre == ' ') {
        std::cout << "Le sac est vide, impossible d'échanger une lettre.\n";
        return;
    }
    
    // Remettre la lettre de la main dans le sac
    if (lettre_a_remettre >= 'A' && lettre_a_remettre <= 'Z') {
        s.sac_de_lettres[lettre_a_remettre - 'A'].nombre += 1;
        s.total_lettres += 1;
    }
    
    // Placer la nouvelle lettre dans la main
    j.main[index] = nouvelle_lettre;
}
bool Jeu::case_vide(Etat* a_analyser) {
    if (!a_analyser) { return false; } 

    bool poser_une_lettre = false;
    
    // Si on est arrivé à un mot valide et qu'on a bien posé une lettre --> on calcule le score
    if (a_analyser->noeud_courant_gaddag->terminal && deja_jouer_une_lettre(a_analyser)) {

        int solo = calculer_score(a_analyser) ; 
        int score = solo + a_analyser->score_perpendiculaire;

        if (score > t.max_score) {
            t.max_score = score;
            if (t.meilleur_coup && std::find(t.pile_etats.begin(), t.pile_etats.end(), t.meilleur_coup) == t.pile_etats.end()) {
                delete t.meilleur_coup;
            }
            //cout<<"score perpendiculaire : "<<a_analyser->score_perpendiculaire<< " points "<<endl; 
            //cout<<"score du mot qu'on pose à ce tour : "<<solo<< " points "<<endl; 
            t.meilleur_coup = a_analyser;
        }
    }

    // Si l'index est bien valide
    if(index_valide(a_analyser->index_actuel)){
        for (int i = 0; i < 7; i++) {
            char lettre = a_analyser->main_joueur[i];
            int index_lettre = lettre - 'A';

            if (lettre != '0' && index_valide(index_lettre) && a_analyser->noeud_courant_gaddag->fils[index_lettre] != nullptr) {
                Noeud* prochain_noeud = a_analyser->noeud_courant_gaddag->fils[index_lettre];
                int nouvel_index = a_analyser->index_actuel + a_analyser->direction_h + a_analyser->direction_v;

                if ((au_bord_d(a_analyser->index_actuel) && a_analyser->direction_h == 1) || 
                    (au_bord_g(a_analyser->index_actuel) && a_analyser->direction_h == -1) || 
                    (au_bord_h(a_analyser->index_actuel) && a_analyser->direction_v == -15) ||
                    (au_bord_b(a_analyser->index_actuel) && a_analyser->direction_v == 15) ||
                    !index_valide(nouvel_index)) {
                    nouvel_index = -1;
                }

                bool placement_valide = deja_jouer_une_lettre(a_analyser);
                
                if (!placement_valide) {
                    if (a_analyser->index_départ == 112) {
                        placement_valide = true;
                    } else if (
                        (index_valide(a_analyser->index_actuel - 1) && a_analyser->b.spots[a_analyser->index_actuel - 1].letter != 0) ||
                        (index_valide(a_analyser->index_actuel + 1) && a_analyser->b.spots[a_analyser->index_actuel + 1].letter != 0) ||
                        (index_valide(a_analyser->index_actuel - 15) && a_analyser->b.spots[a_analyser->index_actuel - 15].letter != 0) ||
                        (index_valide(a_analyser->index_actuel + 15) && a_analyser->b.spots[a_analyser->index_actuel + 15].letter != 0)) {
                        placement_valide = true;
                    }
                }

                if (placement_valide) {
                    Board board_temp = a_analyser->b;
                    board_temp.spots[a_analyser->index_actuel].letter = lettre;
                    bool mots_valides = true;
                    
                    int score_perp_cette_position = 0;

                    if (a_analyser->direction_h != 0) {
                        if ((index_valide(a_analyser->index_actuel - 15) && board_temp.spots[a_analyser->index_actuel - 15].letter != 0) ||
                            (index_valide(a_analyser->index_actuel + 15) && board_temp.spots[a_analyser->index_actuel + 15].letter != 0)) {
                            if (!mot_est_valide(a_analyser->index_actuel, board_temp, false)) {
                                mots_valides = false;
                            }
                            else { // NOUVELLES LIGNES AJOUTEES POUR LE SCORE DUN MOT PERPENDICULAIRE
                                Etat* nouvel_etat_perpendiculaire = new Etat(
                                    a_analyser->main_joueur,
                                    &g.racine,
                                    a_analyser->index_actuel, 
                                    board_temp,
                                    0,
                                    -15,
                                    a_analyser->index_actuel,
                                    0
                                );
                                
                                score_perp_cette_position += calculer_score(nouvel_etat_perpendiculaire);
                                
                                delete nouvel_etat_perpendiculaire;
                            }
                        }
                    }

                    if (a_analyser->direction_v != 0) {
                        if ((index_valide(a_analyser->index_actuel - 1) && board_temp.spots[a_analyser->index_actuel - 1].letter != 0) ||
                            (index_valide(a_analyser->index_actuel + 1) && board_temp.spots[a_analyser->index_actuel + 1].letter != 0)) {
                            if (!mot_est_valide(a_analyser->index_actuel, board_temp, true)) {
                                mots_valides = false;
                            }
                            else {  // NOUVELLES LIGNES AJOUTEES POUR LE SCORE DUN MOT PERPENDICULAIRE
                                Etat* nouvel_etat_perpendiculaire = new Etat(
                                    a_analyser->main_joueur,
                                    &g.racine,
                                    a_analyser->index_actuel, 
                                    board_temp,
                                    -1,
                                    0,
                                    a_analyser->index_actuel,
                                    0
                                );
                                
                                score_perp_cette_position += calculer_score(nouvel_etat_perpendiculaire);
                                
                                delete nouvel_etat_perpendiculaire;
                            }
                        }
                    }

                    if (mots_valides) {
                        Etat* nouvel_etat = new Etat(
                            a_analyser->main_joueur,
                            prochain_noeud,
                            nouvel_index,
                            a_analyser->b,
                            a_analyser->direction_h,
                            a_analyser->direction_v,
                            a_analyser->index_départ,
                            // Passe le score perpendiculaire de l'état parent + celui de cette position seulement
                            a_analyser->score_perpendiculaire + score_perp_cette_position
                        );
                        score_perp_cette_position = 0; 

                        nouvel_etat->b.spots[a_analyser->index_actuel].letter = lettre;
                        nouvel_etat->main_joueur[i] = '0';

                        t.pile_etats.push_back(nouvel_etat);
                        poser_une_lettre = true;
                    }
                }
            }
        }
    }

    return poser_une_lettre;
}
// Fonction pour vérifier si un mot est valide selon le GADDAG
bool Jeu::mot_est_valide(int index, const Board& board, bool horizontal) {
    // Si horizontal pas = 1 sinon vertical pas = 15
    int pas; 
    if(horizontal)
    {
        pas = 1; 
    }
    else 
    {
        pas = 15; 
    }
    
    // Trouver le début du mot
    int debut = index;
    while (index_valide(debut - pas) && board.spots[debut - pas].letter != 0 && (!(au_bord_h(debut) && pas == 15)&& !(au_bord_g(debut) && pas == 1))) {
        debut -= pas;
    }
    
    // Trouver la fin du mot
    int fin = index;
    while (index_valide(fin + pas) && board.spots[fin + pas].letter != 0 && (!(au_bord_b(fin) && pas == 15)&& !(au_bord_d(fin) && pas == 1))) {
        fin += pas;
    }
    
    
    // Récupérer le mot complet
    std::string mot;
    for (int i = debut; i <= fin; i += pas) {
        mot += board.spots[i].letter;
        if(i==debut){ mot += '+'; } 
    }

    // Vérifier le mot dans le GADDAG
    return g.recherche(mot);
}


bool Jeu::case_occupee(Etat* a_analyser) {
    if (!a_analyser) {return false; }

    // On vérifie que l’index actuel est valide
    if (!index_valide(a_analyser->index_actuel)) {
        return false;
    }

    // On récupère la lettre présente sur la case et on calcule son index 
    int lettre_index = a_analyser->b.spots[a_analyser->index_actuel].letter - 'A';

    // Si la lettre est valide et qu’il y a une branche correspondante dans le GADDAG
    if (index_valide(lettre_index) && a_analyser->noeud_courant_gaddag->fils[lettre_index] != nullptr) {
        // On avance dans le GADDAG en suivant cette lettre
        a_analyser->noeud_courant_gaddag = a_analyser->noeud_courant_gaddag->fils[lettre_index];

        // On calcule la case suivante (selon la direction horizontale ou verticale)
        int nouvel_index = a_analyser->index_actuel + a_analyser->direction_h + a_analyser->direction_v;

        // Vérification des cas où on risquerait de sortir du plateau 
        // Ce teste permet d'éviter les mots coupés car des fois le mot se coupait, il arriavait de l'autre côté
        if (!((au_bord_d(a_analyser->index_actuel) && a_analyser->direction_h == 1) || 
              (au_bord_g(a_analyser->index_actuel) && a_analyser->direction_h == -1) || 
              (au_bord_h(a_analyser->index_actuel) && a_analyser->direction_v == -15) ||
              (au_bord_b(a_analyser->index_actuel) && a_analyser->direction_v == 15) ||
              !index_valide(nouvel_index))) {

            // on crée un nouvel état avec la suite du mot
            Etat* nouvel_etat = new Etat(
                a_analyser->main_joueur,
                a_analyser->noeud_courant_gaddag,
                nouvel_index,
                a_analyser->b,
                a_analyser->direction_h,
                a_analyser->direction_v,
                a_analyser->index_départ,
                a_analyser->score_perpendiculaire
            );

            // On ajoute ce nouvel état dans la pile pour continuer la recherche
            t.pile_etats.push_back(nouvel_etat);
            return true;  // La case a été prise en compte correctement
        }
    }

    return false;  // Sinon, on ne peut pas utiliser cette case
}

Etat* Jeu::trouver_meilleur_coup() {
    facteurs_a_1();  

    // Réinitialisation du meilleur coup au début du tour
    if (t.meilleur_coup) {
        delete t.meilleur_coup;  
        t.meilleur_coup = nullptr;
    }
    t.max_score = -1; 

    // On vide la pile d’états précédente pour recommencer proprement
    for (Etat* etat : t.pile_etats) {
        delete etat;
    }
    t.pile_etats.clear();

    // Pour chaque case à tester on crée deux états : un horizontal, un vertical
    for (int i = 0; i < int(t.a_tester.size()); i++) {
        int index = t.a_tester[i];
        Etat* etat_horizontal = new Etat(j.main, &g.racine, index, board, -1, 0, index , 0);  // vers la gauche
        Etat* etat_vertical = new Etat(j.main, &g.racine, index, board, 0, -15, index , 0);   // vers le haut

        t.pile_etats.push_back(etat_horizontal);
        t.pile_etats.push_back(etat_vertical);
    }

    // Tant qu’il reste des états à explorer
    while (!t.pile_etats.empty()) {
        Etat* a_analyser = depiler(t.pile_etats);  // On récupère un état à analyser

        if (!a_analyser) continue;  // si l’état est nul on arrête

        if (a_analyser->direction_h != 0) {  // Si on est en horizontal

            // Si la case est vide on essaie de poser une lettre // Le -1 c'est pour assurer les bords il est traité dans case vide
            if (a_analyser->b.spots[a_analyser->index_actuel].letter == 0 || a_analyser->index_actuel == -1) {
                bool poser_lettre = case_vide(a_analyser);

                // Si on est en train de finir a gauche on teste le passage a droite
                if (!poser_lettre && a_analyser->direction_h == -1 && a_analyser->noeud_courant_gaddag->fils[26] != nullptr) {
                    int nouvel_index = a_analyser->index_départ + 1;
                    if (index_valide(nouvel_index) && !au_bord_d(a_analyser->index_départ)) {
                        Etat* etat_plus = new Etat(
                            a_analyser->main_joueur,
                            a_analyser->noeud_courant_gaddag->fils[26],
                            nouvel_index,
                            a_analyser->b,
                            1, 0,
                            a_analyser->index_départ,
                            a_analyser->score_perpendiculaire
                        );
                        t.pile_etats.push_back(etat_plus);
                    }
                }

                // Si cet état ne sert plus à rien on le supprime
                if (t.meilleur_coup != a_analyser) {
                    delete a_analyser;
                }

            } else {
                // Si la case est déjà occupée on la traite avec case_occupee
                bool occupee = case_occupee(a_analyser);
                if (!occupee && t.meilleur_coup != a_analyser) {
                    delete a_analyser;
                }
            }

        } else if (a_analyser->direction_v != 0) {  // Si on est en vertical

            if (a_analyser->b.spots[a_analyser->index_actuel].letter == 0) {
                bool poser_lettre = case_vide(a_analyser);

                // Même principe que pour l’horizontal mais vers le bas
                if (!poser_lettre && a_analyser->direction_v == -15 && a_analyser->noeud_courant_gaddag->fils[26] != nullptr) {
                    int nouvel_index = a_analyser->index_départ + 15;
                    if (index_valide(nouvel_index)) {
                        Etat* etat_plus = new Etat(
                            a_analyser->main_joueur,
                            a_analyser->noeud_courant_gaddag->fils[26],
                            nouvel_index,
                            a_analyser->b,
                            0, 15,
                            a_analyser->index_départ,
                            a_analyser->score_perpendiculaire
                        );
                        t.pile_etats.push_back(etat_plus);
                    }
                }

                if (t.meilleur_coup != a_analyser) {
                    delete a_analyser;
                }

            } else {
                bool occupee = case_occupee(a_analyser);
                if (!occupee && t.meilleur_coup != a_analyser) {
                    delete a_analyser;
                }
            }

        } else {
            // Si la direction est bizarre on jette l'état 
            if (t.meilleur_coup != a_analyser) {
                delete a_analyser;
            }
        }
    }

    // Si on n’a rien trouvé et qu’il reste des lettres dans le sac, on tente un échange de lettre (max 20 fois) --> la constante du début
    if (t.meilleur_coup == nullptr && s.total_lettres > 0 && compteur < max_echanges) {
        //srand(time(nullptr));
        échanger_une_lettre();  // On tente une nouvelle main
        compteur++;  // On note qu’on a échangé
        return trouver_meilleur_coup();  // On recommence
    }

    return t.meilleur_coup;  // À la fin on retourne le meilleur coup trouvé (ou nullptr si rien)
}

int Jeu::calculer_score(Etat* etat) {
    int score_mot = 0;
    int multiplicateur_mot = 1;
    int pas;

    // Déterminer le pas selon la direction
    if (etat->direction_h != 0) {
        pas = 1;  
    } else if (etat->direction_v != 0) {
        pas = 15; 
    } else {
        return 0; 
    }

    //  début du mot
    int debut = etat->index_départ; // AJOUTER : On part de l'index de départ sinon si on est entre 2 mots et qu'on est sur une case vide le début du mot est au début duu mot 1 et la fin à la fin du mot 2
    while (index_valide(debut - pas) && etat->b.spots[debut - pas].letter != 0 && (!(au_bord_h(debut) && pas == 15)&& !(au_bord_g(debut ) && pas == 1))) {
        debut -= pas;
    }

    // fin du mot
    int fin = etat->index_départ;
    while (index_valide(fin + pas) && etat->b.spots[fin + pas].letter != 0 && (!(au_bord_b(fin) && pas == 15)&& !(au_bord_d(fin) && pas == 1))) {
        fin += pas;
    }

    for (int i = debut; i <= fin; i += pas) {
        char lettre = etat->b.spots[i].letter;

        if (lettre == 0) continue;

        int points_lettre = s.sac_de_lettres[lettre - 'A'].points;


        // Appliquer le multiplicateur lettre (bonus lettre)
        if( etat->b.spots[i].bonus.letter_factor != 1)
        {
            points_lettre *= etat->b.spots[i].bonus.letter_factor;
            
        }

        // Ajouter le résultat au score total du mot
        score_mot += points_lettre;

        // Cumul multiplicateur mot (bonus mot)
        if( etat->b.spots[i].bonus.word_factor != 1)
        {
            multiplicateur_mot *= etat->b.spots[i].bonus.word_factor;
        }

    }
    // Récupérer le mot complet
    std::string mot;
    for (int i = debut; i <= fin; i += pas) {
        mot += etat->b.spots[i].letter;
    }

    return score_mot * multiplicateur_mot;
}
