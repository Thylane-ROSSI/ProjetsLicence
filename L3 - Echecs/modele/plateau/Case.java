package modele.plateau;

import modele.jeu.Piece;

public class Case {

    public Piece p;
    protected Plateau plateau;

    public void quitterLaCase() {
        p = null;
    }

    public Case(Plateau _plateau) {

        plateau = _plateau;
    }

    public Piece getPiece() {
        return p;
    }

}
