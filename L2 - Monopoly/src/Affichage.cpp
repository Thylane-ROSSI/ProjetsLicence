#include "Affichage.h"
#include "CarteImmo.h"
#include "Gare.h"
#include "ServicePublic.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <iomanip>

int screenWidth = 1920; // Largeur de l'écran
int screenHeight = 1080; // Hauteur de l'écran

using namespace std;

void init(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font*& font, Mix_Music*& backgroundMusic) {

    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        cerr << "SDL initialization failed: " << SDL_GetError() << endl;
        exit(1);
    }

    // Créer la fenêtre
    window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cerr << "Window creation failed: " << SDL_GetError() << endl;
        exit(1);
    }

    // Créer le rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cerr << "Renderer creation failed: " << SDL_GetError() << endl;
        exit(1);
    }

    // Définir la couleur de fond en blanc (255, 255, 255)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // Effacer l'écran avec la couleur de fond
    SDL_RenderClear(renderer);

    // Initialiser SDL_ttf
    if (TTF_Init() == -1) {
        cerr << "SDL_ttf initialization failed: " << TTF_GetError() << endl;
        exit(1);
    }

    // Charger la police de caractères
    font = TTF_OpenFont("/mnt/c/Windows/Fonts/arial.ttf", 26);
    if (font == nullptr) {
        cerr << "Font loading failed: " << TTF_GetError() << endl;
        exit(1);
    }

    // Initialiser SDL Mixer
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // Charger la musique de fond
    backgroundMusic = Mix_LoadMUS("data/MusiqueMonopoly.mp3");
    if (!backgroundMusic) {
        cerr << "Background music loading failed: " << Mix_GetError() << endl;
        exit(1);
    }

    // Jouer la musique de fond en boucle
    Mix_PlayMusic(backgroundMusic, -1);
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    // Libérer la Appuyez sur O pour oui et N pour non de caractères
    TTF_CloseFont(font);

    // Quitter SDL_ttf
    TTF_Quit();

    // Détruire le rendu
    SDL_DestroyRenderer(renderer);

    // Détruire la fenêtre
    SDL_DestroyWindow(window);

    // Quitter SDL
    SDL_Quit();
}


void afficher_resultat_de(Plateau &P,SDL_Renderer* renderer, TTF_Font* font, int resultat) {
    // Convertir le résultat du dé en chaîne de caractères
    string diceResult = "Résultat des dés : " + to_string(resultat);

    afficher_commentaire(P, renderer, font, diceResult, 4000);
    //Afficher le résulat des dés 4 secondes
}

void affiche_plateau(SDL_Renderer* renderer) {

    // Charger l'image
    SDL_Surface* imageSurface = IMG_Load("data/plateau.png");
    if (imageSurface == nullptr) {
        cerr << "Erreur lors du chargement de l'image : " << IMG_GetError() << endl;
        // Gérer l'erreur
    }
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface); // Libérer la surface car elle n'est plus nécessaire

    // Récupérer les dimensions de l'image
    int imageWidth, imageHeight;
    SDL_QueryTexture(imageTexture, nullptr, nullptr, &imageWidth, &imageHeight);

    // Dessiner l'image
    SDL_Rect imageRect = {10, 10, 1030, 1030}; // Position et taille de l'image
    SDL_RenderCopy(renderer, imageTexture, nullptr, &imageRect);
}


void effacer_commentaire(SDL_Renderer* renderer) {

    // Dessiner un rectangle blanc pour effacer le commentaire précédent

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur blanche
    SDL_Rect rect = {1040, 900, 900 , 200 };
    SDL_RenderFillRect(renderer, &rect);

}

void afficher_commentaire(Plateau &P, SDL_Renderer* renderer, TTF_Font* font, const string& commentaire, int duree_affichage_ms)
 {

    int maxWidth = 2200;
    // Diviser le commentaire en mots
    vector<string> mots;
    string mot_actuel;
    istringstream iss(commentaire);
    while (iss >> mot_actuel) {
        mots.push_back(mot_actuel);
    }

    // Regrouper les mots en lignes en respectant la largeur maximale
    vector<string> lignes;
    string ligne_actuelle;
    for (const auto& mot : mots) {
        // Vérifier si le mot peut être ajouté à la ligne actuelle sans dépasser la largeur maximale
        int largeurMot;
        TTF_SizeText(font, mot.c_str(), &largeurMot, nullptr);
        int largeurLigne = TTF_FontLineSkip(font) * ligne_actuelle.size();
        if (largeurLigne + largeurMot > maxWidth) {
            lignes.push_back(ligne_actuelle);
            ligne_actuelle.clear();
        }
        if (!ligne_actuelle.empty()) {
            ligne_actuelle += ' ';
        }
        ligne_actuelle += mot;
    }
    // Ajouter la dernière ligne
    if (!ligne_actuelle.empty()) {
        lignes.push_back(ligne_actuelle);
    }

    // Afficher les lignes du commentaire
    SDL_Color color = {0, 0, 0}; // Couleur noir
    int y = 950; // Position verticale initiale
    int x = 1050; // Position horizontale initiale
    for (const auto& ligne : lignes) {
        SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, ligne.c_str(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        int textWidth = textSurface->w;
        int textHeight = textSurface->h;
        SDL_Rect textRect = {x, y, textWidth, textHeight};
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        y += textHeight; // Mise à jour de la position verticale pour la prochaine ligne
    }

    SDL_RenderPresent(renderer);

    // Attendre la durée d'affichage spécifiée
    SDL_Delay(duree_affichage_ms);

    // Effacer le rendu en redessinant la fenêtre sans le texte du commentaire
    //Nettoyer 
    effacer_commentaire(renderer);
    afficher_jeu_static(P, renderer, font);
    SDL_RenderPresent(renderer);
}



// Meme fonction que afficher commentaire mais qui ne dépend pas d'un délai et s'efface seulement quand le joueur a fait un choix
void afficher_commentaire_demande(Plateau &P, SDL_Renderer* renderer, TTF_Font* font, const string& commentaire)
 {

    int maxWidth = 2200;
    // Diviser le commentaire en mots
    vector<string> mots;
    string mot_actuel;
    istringstream iss(commentaire);
    while (iss >> mot_actuel) {
        mots.push_back(mot_actuel);
    }

    // Regrouper les mots en lignes en respectant la largeur maximale
    vector<string> lignes;
    string ligne_actuelle;
    for (const auto& mot : mots) {
        // Vérifier si le mot peut être ajouté à la ligne actuelle sans dépasser la largeur maximale
        int largeurMot;
        TTF_SizeText(font, mot.c_str(), &largeurMot, nullptr);
        int largeurLigne = TTF_FontLineSkip(font) * ligne_actuelle.size();
        if (largeurLigne + largeurMot > maxWidth) {
            lignes.push_back(ligne_actuelle);
            ligne_actuelle.clear();
        }
        if (!ligne_actuelle.empty()) {
            ligne_actuelle += ' ';
        }
        ligne_actuelle += mot;
    }
    // Ajouter la dernière ligne
    if (!ligne_actuelle.empty()) {
        lignes.push_back(ligne_actuelle);
    }

    // Afficher les lignes du commentaire
    SDL_Color color = {0,0,0}; // Couleur noir
    int y = 950; // Position verticale initiale
    int x = 1050; // Position horizontale initiale
    for (const auto& ligne : lignes) {
        SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, ligne.c_str(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        int textWidth = textSurface->w;
        int textHeight = textSurface->h;
        SDL_Rect textRect = {x, y, textWidth, textHeight};
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        y += textHeight; // Mise à jour de la position verticale pour la prochaine ligne
    }

    SDL_RenderPresent(renderer);

}




//AFFICHER CARTE CHANCE 
void afficher_carte_chance(Plateau &P, SDL_Renderer* renderer, TTF_Font* font, int id_carte) {
            //construire le chemin vers l'image de la carte
            string imageChemin = "data/chance" + to_string(id_carte) + ".png"; 

            // Charger l'image
            SDL_Surface* surface = IMG_Load(imageChemin.c_str());
            if (!surface) {
                cerr << "Erreur de télechargement d'image: " << IMG_GetError() << endl;
                return;
    }
            // Créer une texture à partir de la surface
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (!texture) {
                SDL_FreeSurface(surface);
                cerr << "Failed to create texture: " << SDL_GetError() << endl;
                return;
    }
            // Calculer la position et la taille pour centrer l'image
            int x = (1030 - surface->w) / 2;
            int y = (1030 - surface->h) / 2;
             SDL_Rect destRect = {x, y, surface->w, surface->h};
            
             // Libérer la surface dès qu'elle n'est plus nécessaire
             //SDL_FreeSurface(surface);

            // Afficher l'image
            SDL_RenderCopy(renderer, texture, NULL, &destRect); // Copier la texture au rendu
            SDL_RenderPresent(renderer); // Mettre à jour l'écran avec le rendu

             // Attendre 5 secondes
             SDL_Delay(5000);

            // revenir à l'affichage précédent ; dans la boucle du jeu 

             // Nettoyer 
            SDL_DestroyTexture(texture);
            afficher_jeu_static(P,renderer, font);
            SDL_RenderPresent(renderer);
}
// AFFICHER CARTE COMMU 

void afficher_carte_commu(Plateau &P, SDL_Renderer* renderer, TTF_Font* font, int id_carte ) {
            //construire le chemin vers l'image de la carte
            string imageChemin = "data/commu" + to_string(id_carte) + ".png"; 

            // Charger l'image
            SDL_Surface* surface = IMG_Load(imageChemin.c_str());
            if (!surface) {
                cerr << "Erreur de télechargement d'image: " << IMG_GetError() << endl;
                return;
    }
            // Créer une texture à partir de la surface
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (!texture) {
                SDL_FreeSurface(surface);
                cerr << "Failed to create texture: " << SDL_GetError() << endl;
                return;
    }
            // Calculer la position et la taille pour centrer l'image
            int x = (1030 - surface->w) / 2;
            int y = (1030 - surface->h) / 2;
             SDL_Rect destRect = {x, y, surface->w, surface->h};
            

            // Afficher l'image

            SDL_RenderCopy(renderer, texture, NULL, &destRect); // Copier la texture au rendu
            SDL_RenderPresent(renderer); // Mettre à jour l'écran avec le rendu

             // Attendre 5 secondes
             SDL_Delay(5000);

            // revenir à l'affichage précédent ; dans la boucle du jeu 

             // Nettoyer 
              SDL_DestroyTexture(texture);
              afficher_jeu_static(P,renderer, font);
              SDL_RenderPresent(renderer);
}


//  Fonction qui fait avancer le pion d'un joueur donné
// int &position_actuelle, int position_à_aller, int &position_x, int &position_y,
void avancer_pion(SDL_Renderer* renderer, int num_joueur, TTF_Font* font, Plateau &P, int resultat_des) {
    SDL_Surface* imageSurface = nullptr; // Initialisation des pointeurs à nullptr
    SDL_Texture* imageTexture = nullptr;

    string imageChemin; // Déclaration de la variable en dehors des blocs if

    if (num_joueur == 0) {
        imageChemin = "data/pingouin.png";
    } else if (num_joueur == 1) {
        imageChemin = "data/icon.png";
    } else if (num_joueur == 2) {
        imageChemin = "data/chat.png";
    } else if (num_joueur == 3) {
        imageChemin = "data/chapeau.png";
    }

    // Charger l'image
    imageSurface = IMG_Load(imageChemin.c_str());
    if (imageSurface == nullptr) {
        cerr << "Erreur lors du chargement de l'image : " << IMG_GetError() << endl;
        return; // Quitter la fonction en cas d'erreur
    }

    // Créer une texture à partir de la surface
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (imageTexture == nullptr) {
        cerr << "Failed to create texture: " << SDL_GetError() << endl;
        SDL_FreeSurface(imageSurface); // Libérer la surface en cas d'erreur
        return; // Quitter la fonction en cas d'erreur
    }

    // Récupérer les dimensions de l'image
    int imageWidth, imageHeight;
    SDL_QueryTexture(imageTexture, nullptr, nullptr, &imageWidth, &imageHeight);

    // Dessiner l'image, normalement en entrant dans la fonction, l'image est déjà dessinée
    //SDL_Rect imageRect = {P.get_joueur(num_joueur)->get_position_x(), P.get_joueur(num_joueur)->get_position_y(),100, 100}; // Position et taille de l'image
    //SDL_RenderCopy(renderer, imageTexture, nullptr, &imageRect);
    //SDL_RenderPresent(renderer); // Mettre à jour l'écran avec le rendu

// Avancer le pion progressivement
    for (int i = P.get_joueur(num_joueur)->get_position(); i < P.get_joueur(num_joueur)->get_position()+resultat_des; ++i) {
        // Mettre à jour la position actuelle
        // Afficher la case actuelle
        SDL_Rect imageRect = {P.get_joueur(num_joueur)->get_position_x(), P.get_joueur(num_joueur)->get_position_y(),100, 100}; // Position et taille de l'image
        SDL_RenderCopy(renderer, imageTexture, nullptr, &imageRect);
        SDL_RenderPresent(renderer); // Mettre à jour l'écran avec le rendu
        // Dessiner l'image
         if((i<10) && (i>=0)){
            P.get_joueur(num_joueur)->set_position_x(-85);
        } if((i<20) && (i>=10)) {
            P.get_joueur(num_joueur)->set_position_y(-85);
        }  if((i<30) && (i>=20)) {
            P.get_joueur(num_joueur)->set_position_x(85);
        }   if((i<=39) && (i>=30)) {
            P.get_joueur(num_joueur)->set_position_y(85);
        }
        SDL_Delay(100);

        afficher_jeu_static(P,renderer, font);
        SDL_RenderPresent(renderer);

    }


    // Nettoyer
    SDL_DestroyTexture(imageTexture);
    SDL_FreeSurface(imageSurface);
    afficher_jeu_static(P, renderer, font);
    SDL_RenderPresent(renderer);
}

void afficher_un_pion(Joueur * joueur_qui_joue,SDL_Renderer* renderer, int num_joueur)
{

    SDL_Surface* imageSurface = nullptr; // Initialisation des pointeurs à nullptr
    SDL_Texture* imageTexture = nullptr;

    string imageChemin; // Déclaration de la variable en dehors des blocs if

    if (num_joueur == 0) {
        imageChemin = "data/pingouin.png";
    } else if (num_joueur == 1) {
        imageChemin = "data/icon.png";
    } else if (num_joueur == 2) {
        imageChemin = "data/chat.png";
    } else if (num_joueur == 3) {
        imageChemin = "data/chapeau.png";
    }

    // Charger l'image
    imageSurface = IMG_Load(imageChemin.c_str());
    if (imageSurface == nullptr) {
        cerr << "Erreur lors du chargement de l'image : " << IMG_GetError() << endl;
        return; // Quitter la fonction en cas d'erreur
    }

    // Créer une texture à partir de la surface
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (imageTexture == nullptr) {
        cerr << "Failed to create texture: " << SDL_GetError() << endl;
        SDL_FreeSurface(imageSurface); // Libérer la surface en cas d'erreur
        return; // Quitter la fonction en cas d'erreur
    }

    // Récupérer les dimensions de l'image
    int imageWidth, imageHeight;
    SDL_QueryTexture(imageTexture, nullptr, nullptr, &imageWidth, &imageHeight);
    SDL_Rect imageRect = {joueur_qui_joue->get_position_x(), joueur_qui_joue->get_position_y(),100, 100}; // Position et taille de l'image
    SDL_RenderCopy(renderer, imageTexture, nullptr, &imageRect);
    SDL_RenderPresent(renderer); // Mettre à jour l'écran avec le rendu

}

void afficher_les_pions(Plateau &P, SDL_Renderer* renderer)
{
    Joueur * joueur_qui_joue = nullptr;
    for(int i=0; i<P.get_nbjoueur(); i++)
    {
        joueur_qui_joue = P.get_joueur(i);
        afficher_un_pion(joueur_qui_joue, renderer, i);
    }
      
}

void afficher_jeu_static (Plateau &P, SDL_Renderer* renderer, TTF_Font* font)
{
    Afficher_info_joueurs(renderer,  font, P.get_nbjoueur(), P);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    affiche_plateau(renderer);
    afficher_les_pions(P, renderer);
}


void Afficher_info_joueurs(SDL_Renderer* renderer,  TTF_Font* font, int nb_joueur, Plateau &P) {

    int position_premier = 50; 
    for(int i = 0; i<nb_joueur; i++)
    {
        if(P.get_joueur(i)->get_joueur_neg()==0){
        Joueur* joueur_a_afficher = P.get_joueur(i);
        SDL_Color color = {255, 255, 255}; // Couleur blanche


        // Afficher l'image des rectangles

        SDL_Rect backgroundRect;
        backgroundRect.x = 1050;
        backgroundRect.y = position_premier;
        backgroundRect.w = 850;
        backgroundRect.h = 175;

        // Dessiner l'image d'arrière-plan sur le rectangle spécifié
        SDL_Surface* imageSurface = IMG_Load("data/fond_joueur.png");
        if (imageSurface == nullptr) {
            printf("Erreur de chargement de l'image : %s\n", IMG_GetError());
            return;
        }

        SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        SDL_FreeSurface(imageSurface);

        SDL_RenderCopy(renderer, imageTexture, nullptr, &backgroundRect);

        SDL_DestroyTexture(imageTexture);

        string imageChemin;

        if (i == 0) {
            imageChemin = "data/pingouin.png";
        } if (i == 1) {
            imageChemin = "data/icon.png";
        } if (i == 2) {
            imageChemin = "data/chat.png";
        } if (i == 3) {
            imageChemin = "data/chapeau.png";
        }

        SDL_Rect pion;
        pion.x = 1050;
        pion.y = position_premier;
        pion.w = 80;
        pion.h = 80;

        SDL_Surface* imageSurface_pion = IMG_Load(imageChemin.c_str());
        if (imageSurface_pion == nullptr) {
            printf("Erreur de chargement de l'image : %s\n", IMG_GetError());
            return;
        }

        SDL_Texture* imageTexture_pion = SDL_CreateTextureFromSurface(renderer, imageSurface_pion);
        SDL_FreeSurface(imageSurface_pion);

        SDL_RenderCopy(renderer, imageTexture_pion, nullptr, &pion);

        SDL_DestroyTexture(imageTexture_pion);

        // Code pour le pseudo 

        string pseudo = joueur_a_afficher->get_pseudo(); 
        pseudo = "Pseudo :"+pseudo;

        int y_pseudo = position_premier+55; // Position verticale initiale
        int x_pseudo = 1400; // Position horizontale initiale

        SDL_Surface* textSurface_pseudo = TTF_RenderText_Solid(font, pseudo.c_str(), color);
        
        SDL_Texture* textTexture_pseudo = SDL_CreateTextureFromSurface(renderer, textSurface_pseudo);
        int textWidth = textSurface_pseudo->w;
        int textHeight = textSurface_pseudo->h;
        SDL_Rect textRect_pseudo = {x_pseudo, y_pseudo, textWidth, textHeight};
        SDL_RenderCopy(renderer, textTexture_pseudo, nullptr, &textRect_pseudo);


        // Code pour l'argent

        string argent = to_string(joueur_a_afficher->get_argent()); 
        argent = "Argent :"+argent+" euros";


        int y_argent = position_premier+85; // Position verticale initiale
        int x_argent = 1400; // Position horizontale initiale

        SDL_Surface* textSurface_argent = TTF_RenderText_Solid(font, argent.c_str(), color);
        
        SDL_Texture* textTexture_argent = SDL_CreateTextureFromSurface(renderer, textSurface_argent);
        int text_largeur = textSurface_argent->w;
        int text_hauteur = textSurface_argent->h;
        SDL_Rect textRect_argent = {x_argent, y_argent, text_largeur, text_hauteur};
        SDL_RenderCopy(renderer, textTexture_argent, nullptr, &textRect_argent);



        SDL_FreeSurface(textSurface_argent);
        SDL_FreeSurface(textSurface_pseudo);       
        SDL_DestroyTexture(textTexture_pseudo);
        SDL_DestroyTexture(textTexture_argent);
    

        SDL_RenderPresent(renderer);
        }
        else if (P.get_joueur(i)->get_joueur_neg()==1)
        {
            SDL_Rect backgroundRect;
            backgroundRect.x = 1050;
            backgroundRect.y = position_premier;
            backgroundRect.w = 870;
            backgroundRect.h = 175;

            // Définir la couleur de dessin sur blanc (255, 255, 255)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            // Dessiner le rectangle blanc
            SDL_RenderFillRect(renderer, &backgroundRect);
        }
        position_premier += 200; 
    }

    
}


#define CARD_WIDTH 227
#define CARD_HEIGHT 341

void affichercartes(SDL_Renderer* renderer, Joueur* joueur_qui_joue) {
    int nbCartesJoueur = joueur_qui_joue->get_carte_joueur().taille_utilisee;
    int gare = joueur_qui_joue->get_carte_gare().taille_utilisee;
    int servicpublic = joueur_qui_joue->get_carte_services_publics().taille_utilisee;
    int xPos = (1920 - (nbCartesJoueur * CARD_WIDTH)) / 2;
    int yPos = 100;

    if (nbCartesJoueur > 0) {
        for (int i = 0; i < nbCartesJoueur; ++i) {
            CarteImmo* carte = static_cast<CarteImmo*>(static_cast<void*>(joueur_qui_joue->get_carte_joueur().ad[i]));
            string cheminCarte = "data/carteimmo" + to_string(carte->get_position()) + ".png";

            SDL_Surface* surface = IMG_Load(cheminCarte.c_str());
            if (!surface) {
                cerr << "Erreur de téléchargement d'image: " << IMG_GetError() << endl;
                return;
            }
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (!texture) {
                SDL_FreeSurface(surface);
                cerr << "Failed to create texture: " << SDL_GetError() << endl;
                return;
            }

            SDL_Rect destRect = {xPos, yPos, CARD_WIDTH, CARD_HEIGHT};
            SDL_RenderCopy(renderer, texture, NULL, &destRect);

            xPos += CARD_WIDTH;
            if(xPos > 1600)
            {
                xPos = (1920 - (nbCartesJoueur * CARD_WIDTH)) / 2;
                yPos = 400;
            }

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
    }


        if (gare > 0) {
        for (int i = 0; i < gare; ++i) {
            Gare* cartegare = static_cast<Gare*>(static_cast<void*>(joueur_qui_joue->get_carte_gare().ad[i]));
            string cheminCarte = "data/carteimmo" + to_string(cartegare->get_position()) + ".png";

            SDL_Surface* surface = IMG_Load(cheminCarte.c_str());
            if (!surface) {
                cerr << "Erreur de téléchargement d'image: " << IMG_GetError() << endl;
                return;
            }
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (!texture) {
                SDL_FreeSurface(surface);
                cerr << "Failed to create texture: " << SDL_GetError() << endl;
                return;
            }

            SDL_Rect destRect = {xPos, yPos, CARD_WIDTH, CARD_HEIGHT};
            SDL_RenderCopy(renderer, texture, NULL, &destRect);

            xPos += CARD_WIDTH;
            if(xPos > 1600)
            {
                xPos = (1920 - (gare * CARD_WIDTH)) / 2;
                yPos = 400;
            }

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
    }


      if (servicpublic > 0) {
        for (int i = 0; i < servicpublic; ++i) {
            Servicepublic* carteSP = static_cast<Servicepublic*>(static_cast<void*>(joueur_qui_joue->get_carte_services_publics().ad[i]));
            string cheminCarte = "data/carteimmo" + to_string(carteSP->get_position()) + ".png";

            SDL_Surface* surface = IMG_Load(cheminCarte.c_str());
            if (!surface) {
                cerr << "Erreur de téléchargement d'image: " << IMG_GetError() << endl;
                return;
            }
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (!texture) {
                SDL_FreeSurface(surface);
                cerr << "Failed to create texture: " << SDL_GetError() << endl;
                return;
            }

            SDL_Rect destRect = {xPos, yPos, CARD_WIDTH, CARD_HEIGHT};
            SDL_RenderCopy(renderer, texture, NULL, &destRect);

            xPos += CARD_WIDTH;
            if(xPos > 1600)
            {
                xPos = (1920 - (servicpublic * CARD_WIDTH)) / 2;
                yPos = 400;
            }

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
    }
   
}


// Fonction pour afficher la vidéo en plein écran
 void afficher_video() {
    SDL_Window *fenetre = nullptr;
    SDL_Renderer *rendu = nullptr;

    // Initialiser SDL et créer une fenêtre
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL n'a pas pu s'initialiser ! Erreur SDL : " << SDL_GetError() << endl;
        return;
    }

    fenetre = SDL_CreateWindow("Lancer les dés ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    if (fenetre == nullptr) {
        cerr << "La fenêtre n'a pas pu être créée ! Erreur SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        return;
    }

    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (rendu == nullptr) {
        cerr << "Le rendu n'a pas pu être créé ! Erreur SDL : " << SDL_GetError() << endl;
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return;
    }

    // Charger et afficher séquentiellement les images
    for (int i = 1; i <= 59; ++i) {
        // Charger l'image courante
        string cheminImage = "data/dice/000" +to_string(i) + ".bmp";
        SDL_Surface *surface = SDL_LoadBMP(cheminImage.c_str());
        if (surface == nullptr) {
            cerr << "Impossible de charger l'image " << cheminImage << " ! Erreur SDL : " << SDL_GetError() << endl;
            continue;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, surface);
        SDL_FreeSurface(surface);
        if (texture == nullptr) {
            cerr << "Impossible de créer la texture pour l'image " << cheminImage << " ! Erreur SDL : " << SDL_GetError() <<endl;
            continue;
        }

        // Effacer l'écran
        SDL_RenderClear(rendu);

        // Afficher l'image courante
        SDL_RenderCopy(rendu, texture, NULL, NULL);

        // Mettre à jour l'écran
        SDL_RenderPresent(rendu);

        // Libérer la mémoire de la texture
        SDL_DestroyTexture(texture);
    }

    // Libérer les ressources et quitter SDL
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
}
