package modele.jeu;

import modele.plateau.Case;

public class Coup {
    public Case dep;
    public Case arr;
    public Coup(Case _dep, Case _arr) {
        dep = _dep;
        arr = _arr;
    }
}
