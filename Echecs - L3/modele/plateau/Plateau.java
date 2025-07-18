package modele.plateau;


import modele.jeu.Cavalier;
import modele.jeu.Dame;
import modele.jeu.Fou;
import modele.jeu.Jeu;
import modele.jeu.Piece;
import modele.jeu.Pion;
import modele.jeu.Roi;
import modele.jeu.Tour;

import java.awt.Point;
import java.util.HashMap;
import java.util.Observable;


public class Plateau extends Observable {

    public static final int SIZE_X = 8;
    public static final int SIZE_Y = 8;

    private Jeu jeu;
    public void setJeu(Jeu j) { this.jeu = j; }
    public Jeu getJeu() { return jeu; }


    private HashMap<Case, Point> map = new  HashMap<Case, Point>(); 
    private Case[][] grilleCases = new Case[SIZE_X][SIZE_Y]; 

    public Plateau() {
        initPlateauVide();
    }

    public Case[][] getCases() {
        return grilleCases;
    }

    private void initPlateauVide() {

        for (int x = 0; x < SIZE_X; x++) {
            for (int y = 0; y < SIZE_Y; y++) {
                grilleCases[x][y] = new Case(this);
                map.put(grilleCases[x][y], new Point(x, y));
            }

        }

    }

    public void placerPieces() {
        // Pièces blanches (rangée 7)
        new Tour(this, true).allerSurCase(grilleCases[0][7]);
        new Cavalier(this, true).allerSurCase(grilleCases[1][7]);
        new Fou(this, true).allerSurCase(grilleCases[2][7]);
        new Dame(this, true).allerSurCase(grilleCases[3][7]);
        new Roi(this, true).allerSurCase(grilleCases[4][7]);
        new Fou(this, true).allerSurCase(grilleCases[5][7]);
        new Cavalier(this, true).allerSurCase(grilleCases[6][7]);
        new Tour(this, true).allerSurCase(grilleCases[7][7]);

        // Pions blancs (rangée 6)
        for (int x = 0; x < 8; x++) {
            new Pion(this, true).allerSurCase(grilleCases[x][6]);
        }

        // Pièces noires (rangée 0)
        new Tour(this, false).allerSurCase(grilleCases[0][0]);
        new Cavalier(this, false).allerSurCase(grilleCases[1][0]);
        new Fou(this, false).allerSurCase(grilleCases[2][0]);
        new Dame(this, false).allerSurCase(grilleCases[3][0]);
        new Roi(this, false).allerSurCase(grilleCases[4][0]);
        new Fou(this, false).allerSurCase(grilleCases[5][0]);
        new Cavalier(this, false).allerSurCase(grilleCases[6][0]);
        new Tour(this, false).allerSurCase(grilleCases[7][0]);

        // Pions noirs (rangée 1)
        for (int x = 0; x < 8; x++) {
            new Pion(this, false).allerSurCase(grilleCases[x][1]);
        }


        setChanged();
        notifyObservers();
    }


    public void arriverCase(Case c, Piece p) {

        c.p = p;

    }

    public void deplacerPiece(Case c1, Case c2) {
        if (c1.p != null) {
            c1.p.allerSurCase(c2);

        }


    }

    public void notifierObservateurs() {
        setChanged();
        notifyObservers();
    }


    public Point getPositionCase(Case c) {
    return map.get(c);
    }


}

