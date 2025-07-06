package modele.jeu;

import modele.plateau.*;
import java.awt.Point;

public class Roi extends Piece {
    public Roi(Plateau _plateau, boolean _estBlanc) {
        super(_plateau, _estBlanc);
        DecorateurCasesAccessibles diag = new DecorateurCasesEnDiagonale(null);
        DecorateurCasesAccessibles ligne = new DecorateurCasesEnLigne(diag);
        DecorateurCasesAccessibles roque = new DecorateurCasesRoque(ligne);
        casesAccessibles = roque;
    }

    @Override
    public void allerSurCase(Case _c) {
        super.allerSurCase(_c);
        aDejaBouge = true;
    }

    public void gererRoqueSiNecessaire(Coup coup) {
        Point dep = plateau.getPositionCase(coup.dep);
        Point arr = plateau.getPositionCase(coup.arr);
        Case[][] cases = plateau.getCases();
        int y = dep.y;

        if (dep.y == arr.y && Math.abs(dep.x - arr.x) == 2) {
            if (arr.x == 6) {
                Piece tour = cases[7][y].getPiece();
                if (tour instanceof Tour) {
                    tour.quitterCase();
                    tour.allerSurCase(cases[5][y]);
                }
            } else if (arr.x == 2) {
                Piece tour = cases[0][y].getPiece();
                if (tour instanceof Tour) {
                    tour.quitterCase();
                    tour.allerSurCase(cases[3][y]);
                }
            }
        }
    }
}  
