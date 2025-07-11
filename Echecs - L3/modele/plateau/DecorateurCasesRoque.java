package modele.plateau;

import modele.jeu.Piece;
import modele.jeu.Tour;
import java.awt.Point;
import java.util.ArrayList;

public class DecorateurCasesRoque extends DecorateurCasesAccessibles {
    public DecorateurCasesRoque(DecorateurCasesAccessibles base) {
        super(base);
    }

    @Override
    public ArrayList<Case> getMesCasesAccessibles() {
        
        ArrayList<Case> accessibles = new ArrayList<>();

        
        Point posRoi = plateau.getPositionCase(piece.getCase());
        Case[][] cases = plateau.getCases();
        int y = posRoi.y;

        // Petit roque
        if (peutRoquerVers(7, new int[]{5, 6})) {
            accessibles.add(cases[6][y]);
        }
        // Grand roque
        if (peutRoquerVers(0, new int[]{3, 2, 1})) {
            accessibles.add(cases[2][y]);
        }

        return accessibles;
    }


    private boolean peutRoquerVers(int xTour, int[] xLibres) {
        Case caseRoi = piece.getCase();
        Point pos = plateau.getPositionCase(caseRoi);
        
        if (pos == null) {
            return false;
        }
        
        Case[][] cases = plateau.getCases();
        int y = piece.getCase() != null ? plateau.getPositionCase(piece.getCase()).y : -1;
        if (y == -1) {
            return false;
        }
    
        Piece tour = cases[xTour][y].getPiece();

    
        if (!(tour instanceof Tour)) {
            return false;
        }
        if (tour.estBlanc() != piece.estBlanc()) {
            return false;
        }
        if (tour.aDejaBouge()) {
            return false;
        }
    
        for (int x : xLibres) {
            if (cases[x][y].getPiece() != null) {
                return false;
            }
        }
    
        for (int x : xLibres) {
            Case cible = cases[x][y];
    
            Case ancienneCase = piece.getCase();
            Piece cibleBackup = cible.getPiece();
    
            ancienneCase.quitterLaCase();
            piece.setCase(cible);
    
            boolean danger = plateau.getJeu().estEnEchec(piece.estBlanc());
    
            piece.setCase(ancienneCase);
            cible.p = cibleBackup;
    
            if (danger) {
                return false;
            }
        }
    
        return true;
    }
    
} 
