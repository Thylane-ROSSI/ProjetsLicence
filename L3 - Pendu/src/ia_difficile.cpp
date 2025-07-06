#include "ia.hpp"
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

// Stockage persistant entre les tours
static std::vector<std::string> mots_candidats;
static bool deja_initialise = false;

// Réinitialise les mots candidats pour recommencer depuis zéro
void resetIADifficile() {
    mots_candidats.clear();
    deja_initialise = false;
}

// Charge tous les mots du dictionnaire de la bonne longueur
void initialiserCandidats(int longueur) {
    if (deja_initialise) return;

    mots_candidats.clear();
    std::ifstream fichier("data/dico.txt");
    std::string mot;

    while (fichier >> mot) {
        for (char& c : mot) c = toupper(c);
        if ((int)mot.size() == longueur)
            mots_candidats.push_back(mot);
    }

    deja_initialise = true;
    std::cout << "[IA DIFFICILE] Initialisation : " << mots_candidats.size()
              << " mots de longueur " << longueur << std::endl;
}

// Élimine les mots qui ne correspondent pas au masque et aux lettres déjà testées
void filtrerCandidats(const std::string& masque, const std::set<char>& lettresEssayees) {
    // Séparer les lettres trouvées des lettres absentes
    std::set<char> lettres_trouvees;
    std::set<char> lettres_absentes;
    
    // Récupérer les lettres qui sont dans le masque (donc trouvées)
    for (char c : masque) {
        if (c != '_' && c != ' ') {
            lettres_trouvees.insert(c);
        }
    }
    
    // Les lettres essayées mais pas dans le masque sont absentes
    for (char c : lettresEssayees) {
        if (lettres_trouvees.find(c) == lettres_trouvees.end()) {
            lettres_absentes.insert(c);
        }
    }

    std::vector<std::string> nouveaux_candidats;
    
    for (const std::string& mot : mots_candidats) {
        bool compatible = true;
        
        // Créer une version du masque sans espaces pour comparaison
        std::string masque_sans_espaces;
        for (char c : masque) {
            if (c != ' ') masque_sans_espaces += c;
        }

        // Vérifier que les longueurs correspondent
        if (mot.size() != masque_sans_espaces.size()) {
            compatible = false;
            continue;
        }

        // Vérifier la compatibilité avec le masque
        for (size_t i = 0; i < mot.size(); ++i) {
            char lettre_mot = mot[i];
            char lettre_masque = masque_sans_espaces[i];

            // Si le masque a une lettre à cette position, le mot doit l'avoir aussi
            if (lettre_masque != '_' && lettre_masque != lettre_mot) {
                compatible = false;
                break;
            }

            // Si le masque a un _, le mot ne doit pas avoir une lettre trouvée ailleurs
            if (lettre_masque == '_' && lettres_trouvees.count(lettre_mot)) {
                compatible = false;
                break;
            }
        }

        if (!compatible) continue;

        // Vérifier que le mot ne contient aucune lettre absente
        for (char c : lettres_absentes) {
            if (mot.find(c) != std::string::npos) {
                compatible = false;
                break;
            }
        }

        if (compatible) {
            nouveaux_candidats.push_back(mot);
        }
    }

    mots_candidats = nouveaux_candidats;
    std::cout << "[IA DIFFICILE] Après filtrage : " << mots_candidats.size() << " candidats restants" << std::endl;
    
    // Debug : afficher quelques candidats
    if (mots_candidats.size() <= 20 && mots_candidats.size() > 0) {
        std::cout << "[IA DIFFICILE] Candidats restants : ";
        for (size_t i = 0; i < std::min((size_t)10, mots_candidats.size()); ++i) {
            std::cout << mots_candidats[i] << " ";
        }
        std::cout << std::endl;
    }
}


// Retourne la lettre encore non testée la plus présente dans les mots restants
char lettrePlusProbable(const std::set<char>& lettresEssayees) {
    std::map<char, int> frequences;
    
    // Compter les lettres dans tous les mots candidats
    for (const std::string& mot : mots_candidats) {
        std::set<char> lettres_uniques_du_mot;
        
        // Ne compter chaque lettre qu'une fois par mot
        for (char c : mot) {
            if (!lettresEssayees.count(c)) {
                lettres_uniques_du_mot.insert(c);
            }
        }
        
        // Incrémenter le compteur pour chaque lettre unique du mot
        for (char c : lettres_uniques_du_mot) {
            frequences[c]++;
        }
    }

    // Trouver la lettre avec la plus grande fréquence
    char meilleure_lettre = '\0';
    int max_frequence = 0;
    
    for (const auto& [lettre, freq] : frequences) {
        if (freq > max_frequence) {
            max_frequence = freq;
            meilleure_lettre = lettre;
        }
    }

    std::cout << "[IA DIFFICILE] Lettre choisie : " << meilleure_lettre 
              << " (présente dans " << max_frequence << " mots)" << std::endl;
    
    return meilleure_lettre;
}

// Choisit la meilleure lettre à proposer en fonction du masque et des mots filtrés
char choisirLettreIADifficile(const std::set<char>& lettresEssayees, const std::string& masque) {
    // Compter seulement les lettres (ignorer les espaces et _)
    int longueur_reelle = 0;
    for (char c : masque) {
        if (c != ' ') longueur_reelle++;
    }
    
    // Initialiser si premier appel
    if (!deja_initialise) {
        initialiserCandidats(longueur_reelle);
    }

    // Filtrer selon les contraintes actuelles
    filtrerCandidats(masque, lettresEssayees);

    // Cas d'erreur : plus de candidats
    if (mots_candidats.empty()) {
        std::cout << "[IA DIFFICILE] ERREUR : Plus aucun mot candidat !" << std::endl;
        // Retourner une lettre fréquente comme fallback
        std::string lettres_frequentes = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
        for (char c : lettres_frequentes) {
            if (!lettresEssayees.count(c)) return c;
        }
        return 'E'; // Ultime fallback
    }

    // Cas spécial : un seul mot candidat
    if (mots_candidats.size() == 1) {
        std::cout << "[IA DIFFICILE] Un seul mot candidat : " << mots_candidats[0] << std::endl;
        for (char c : mots_candidats[0]) {
            if (!lettresEssayees.count(c)) {
                return c;
            }
        }
    }

    // Cas général : choisir la lettre la plus probable
    return lettrePlusProbable(lettresEssayees);
}

// Retourne la liste actuelle des mots candidats
const std::vector<std::string>& getCandidatsIADifficile() {
    return mots_candidats;
}