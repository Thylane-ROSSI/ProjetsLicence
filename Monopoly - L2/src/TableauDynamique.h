#ifndef _TAB_DYN
#define _TAB_DYN

#include "ElementTD.h"

/**
 * @class TableauDynamique 
 * @brief la classe TableauDynamique représente un tableau dynamique. 
 */
class TableauDynamique {
public:

    ElementTD * ad;
    unsigned int capacite; 
    unsigned int taille_utilisee;
    
    /**
     * @brief constructeur par défaut de la classe TableauDynamique.
     * 
     * @post le tableau a 1 emplacement alloué mais vide (taille utilisée nulle).
     */
    TableauDynamique();
    /**
     * @brief constructeur par copie de la classe TableauDynamique.
     * @param t le tableau dynamique à copier.
     * @pre le tableau t est initialisé.
     * @post les deux tableaux contiennent des séquences d'ElementTD identiques (copie de t).
     */
    TableauDynamique(const TableauDynamique& t);
    /**
     * @brief destructeur de la classe TableauDynamique.
     * @post la mémoire allouée dynamiquement est libérée.
     */
    ~TableauDynamique();
    /**
     * @brief cette fonction vide le tableau dynamique.
     * @post : la mémoire allouée dynamiquement est libérée. Le tableau a 1 emplacement alloué mais vide (taille utilisée nulle).
     */
    void vider();
    /**
     * @brief cette fonction ajoute un élément à la fin du tableau.
     * @param e l'élément à ajouter.
     * @post l'élément e est ajouté dans le premier emplacement inutilisé du tableau, la taille est incrémentée de 1. Doublement de la capacité si nécessaire.
     */
    void ajouterElement(const ElementTD e);
    /**
     * @brief cette fonction recupére la valeur de l'élément à l'indice spécifié.
     * @param indice L'indice de l'élément.
     * @pre 0 <= indice < taille_utilisee.
     * @return l'élément à l'indice spécifié.
     */
    ElementTD valeurIemeElement(int indice) const;
    /**
     * @brief cette fonction modifie la valeur de l'élément à l'indice spécifié.
     * @param e la nouvelle valeur de l'élément.
     * @param indice L'indice de l'élément à modifier.
     * @pre 0 <= indice < taille_utilisee.
     * @post l'élément à l'indice spécifié vaut e.
     */
    void modifierValeurIemeElement(ElementTD e, unsigned int indice);
    /**
     * @brief cette fonction affiche les éléments du tableau sur la sortie standard.
     * @post les éléments du tableau sont affichés sur la sortie standard (espacement entre les éléments).
     */
    void afficher() const;
    /**
     * @brief cette fonction supprime l'élément à l'indice spécifié.
     * @param indice L'indice de l'élément à supprimer.
     * @pre le tableau est non vide, et 0 <= indice < taille_utilisee.
     * @post la taille utilisée du tableau est décrémentée de 1.Si taille_utilisee < capacite/3, alors on divise la capacité par 2.
     */
    void supprimerElement(unsigned int indice);
    /**
     * @brief cette fonction insère un élément à l'indice spécifié.
     * @param e l'élément à insérer.
     * @param indice L'indice où insérer l'élément.
     * @pre 0 <= indice < taille_utilisee.
     * @post e est inséré à l'indice spécifié et la taille utilisée est incrémentée de 1.
     */
    void insererElement(ElementTD e, unsigned int indice);
    /**
     * @brief cette fonction trie les éléments du tableau dans l'ordre croissant.
     * @post le tableau est trié dans l'ordre croissant des valeurs des éléments.
     */
    void trier();
    /**
     * @brief cette fonction recherche un élément dans le tableau trié.
     * @param e l'élément à rechercher.
     * @pre le tableau est trié dans l'ordre croissant.
     * @return l'indice de l'emplacement qui contient un élément égal à e, -1 si le tableau ne contient pas d'élément égal à e.
     */
    int rechercherElement(ElementTD e) const;

};

#endif
