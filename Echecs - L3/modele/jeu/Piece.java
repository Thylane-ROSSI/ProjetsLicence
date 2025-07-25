package modele.jeu;

import java.util.ArrayList;

import modele.plateau.Case;
import modele.plateau.DecorateurCasesAccessibles;
import modele.plateau.Plateau;


public abstract class Piece {

    protected Case c;
    protected Plateau plateau;
    protected DecorateurCasesAccessibles casesAccessibles;
    protected boolean estBlanc;
    protected boolean aDejaBouge = false;

    public Piece(Plateau _plateau, boolean _estBlanc) {
        plateau = _plateau;
        estBlanc = _estBlanc;
    }

    public void quitterCase() {
        c.quitterLaCase();
    }
    public void allerSurCase(Case _c) {
        if (c != null) {
            quitterCase();
        }
        c = _c;
        plateau.arriverCase(c, this);
    }

    public Case getCase() {
        return c;
    }

    public boolean estBlanc() {
        return estBlanc;
    }

    public void setCase(Case _case) {
        c = _case;
        if (_case != null) {
            _case.p = this;
        }
    }

    public ArrayList<Case> getCasesAccessibles() {
    if (casesAccessibles != null) {
        casesAccessibles.setPieceEtPlateau(this, plateau);
        return casesAccessibles.getCasesAccessibles();
    }
    return new ArrayList<>();
}

public boolean aDejaBouge() {
    return aDejaBouge;
}

public void setDejaBouge(boolean b) {
    aDejaBouge = b;
}
    

    

}
