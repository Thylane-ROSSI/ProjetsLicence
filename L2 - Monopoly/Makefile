# Les executables
all: bin/Jeu 

# Création des exécutables
bin/Jeu: obj/Plateau.o obj/Joueur.o obj/Cartecommu.o obj/Cartechance.o obj/CarteImmo.o obj/TableauDynamique.o obj/ElementTD.o obj/ServicePublic.o obj/Gare.o obj/Chance_fonctions.o obj/Caisse_fonctions.o obj/Affichage.o obj/Fonctionnalités_Monop.o obj/Tour_joueur.o obj/Accueil.o obj/Menu_nb_joueurs.o obj/Monopoly.o
	mkdir -p bin
	g++ -o bin/Jeu $^ -I/usr/include/jsoncpp -I/usr/include/SDL2 -ljsoncpp -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_mixer `pkg-config --cflags --libs gtkmm-3.0`

# Création des fichiers objets
obj/Monopoly.o : src/Monopoly.cpp src/Demander_pseudo.cpp src/Accueil.h src/Tour_joueur.h src/Affichage.h src/Menu_nb_joueurs.h
	mkdir -p obj
	g++ -o obj/Monopoly.o src/Monopoly.cpp -c -I/usr/include/SDL2 -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_video -lSDL2_mixer `pkg-config --cflags --libs gtkmm-3.0`

obj/Menu_nb_joueurs.o : src/Menu_nb_joueurs.cpp src/Menu_nb_joueurs.h 
	mkdir -p obj
	g++ -o obj/Menu_nb_joueurs.o src/Menu_nb_joueurs.cpp -c -I/usr/include/SDL2 -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_video -lSDL2_mixer

obj/Affichage.o : src/Affichage.cpp src/Affichage.h src/Plateau.h src/Joueur.h src/CarteImmo.h src/Gare.h src/ServicePublic.h
	mkdir -p obj
	g++ -o obj/Affichage.o src/Affichage.cpp -c -I/usr/include/SDL2 -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_video -lSDL2_mixer

obj/Accueil.o : src/Accueil.cpp src/Accueil.h src/Menu_nb_joueurs.h
	mkdir -p obj
	g++ -o obj/Accueil.o src/Accueil.cpp -c -I/usr/include/SDL2 -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_video -lSDL2_mixer

obj/Tour_joueur.o : src/Tour_joueur.cpp src/Tour_joueur.h src/Fonctionnalités_Monop.h
	mkdir -p obj
	g++ -o obj/Tour_joueur.o src/Tour_joueur.cpp -c -I/usr/include/SDL2 -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_video -lSDL2_mixer

obj/Fonctionnalités_Monop.o : src/Fonctionnalités_Monop.cpp src/Fonctionnalités_Monop.h src/Joueur.h src/Plateau.h src/Cartechance.h src/Cartecommu.h src/CarteImmo.h src/Gare.h src/ServicePublic.h src/Caisse_fonctions.h src/Chance_fonctions.h src/Affichage.h
	mkdir -p obj
	g++ -o obj/Fonctionnalités_Monop.o src/Fonctionnalités_Monop.cpp -c -I/usr/include/SDL2 -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_video -lSDL2_mixer -I/usr/include/jsoncpp -ljsoncpp
	
obj/Plateau.o : src/Plateau.cpp src/Plateau.h src/Joueur.h src/TableauDynamique.h
	mkdir -p obj
	g++ -o obj/Plateau.o src/Plateau.cpp -c 

obj/Joueur.o: src/Joueur.cpp src/Joueur.h src/TableauDynamique.h
	mkdir -p obj
	g++ -o obj/Joueur.o src/Joueur.cpp -c

obj/Cartecommu.o : src/Cartecommu.cpp src/Cartecommu.h
	mkdir -p obj
	g++ -o obj/Cartecommu.o src/Cartecommu.cpp -c

obj/Cartechance.o : src/Cartechance.cpp src/Cartechance.h
	mkdir -p obj
	g++ -o obj/Cartechance.o src/Cartechance.cpp -c

obj/Caisse_fonctions.o : src/Caisse_fonctions.cpp src/Caisse_fonctions.h src/Joueur.h src/Plateau.h
	mkdir -p obj
	g++ -o obj/Caisse_fonctions.o src/Caisse_fonctions.cpp -c

obj/Chance_fonctions.o : src/Chance_fonctions.cpp src/Chance_fonctions.h src/Joueur.h
	mkdir -p obj
	g++ -o obj/Chance_fonctions.o src/Chance_fonctions.cpp -c

obj/CarteImmo.o : src/CarteImmo.cpp src/CarteImmo.h src/Joueur.h
	mkdir -p obj
	g++ -o obj/CarteImmo.o src/CarteImmo.cpp -c

obj/ServicePublic.o : src/ServicePublic.cpp src/ServicePublic.h src/Joueur.h
	mkdir -p obj
	g++ -o obj/ServicePublic.o src/ServicePublic.cpp -c

obj/Gare.o : src/Gare.cpp src/Gare.h src/Joueur.h
	mkdir -p obj
	g++ -o obj/Gare.o src/Gare.cpp -c

obj/TableauDynamique.o: src/TableauDynamique.cpp src/TableauDynamique.h src/ElementTD.h 
	mkdir -p obj
	g++ -o obj/TableauDynamique.o src/TableauDynamique.cpp -c

obj/ElementTD.o : src/ElementTD.h src/ElementTD.cpp 
	mkdir -p obj
	g++ -o obj/ElementTD.o src/ElementTD.cpp -c
# La documentation
doc: doc/doxyfile
	doxygen doc/doxyfile
# Nettoyage des fichiers objets et des exécutables
clean:
	rm -rf bin/* obj/*
