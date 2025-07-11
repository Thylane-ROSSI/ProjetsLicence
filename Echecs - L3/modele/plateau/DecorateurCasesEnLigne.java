package modele.plateau;

import java.awt.Point;
import java.util.ArrayList;

public class DecorateurCasesEnLigne extends DecorateurCasesAccessibles {
    public DecorateurCasesEnLigne(DecorateurCasesAccessibles _baseDecorateur) {
        super(_baseDecorateur);
    }

    @Override
    public ArrayList<Case> getMesCasesAccessibles() {
        ArrayList<Case> casesAccessibles = new ArrayList<>();
        
        if (piece == null || plateau == null || piece.getCase() == null) {
            return casesAccessibles;
        }
        
        Case caseActuelle = piece.getCase();
        Point position = plateau.getPositionCase(caseActuelle);
        
        if (position == null) {
            return casesAccessibles;
        }
        
        // Haut
        explorerDirection(position, 0, -1, casesAccessibles);
        
        // Bas
        explorerDirection(position, 0, 1, casesAccessibles);
        
        // Gauche
        explorerDirection(position, -1, 0, casesAccessibles);
        
        // Droite
        explorerDirection(position, 1, 0, casesAccessibles);
        
        return casesAccessibles;
    }
    
    private void explorerDirection(Point position, int dx, int dy, ArrayList<Case> casesAccessibles) {
        int limitePas = (piece instanceof modele.jeu.Roi) ? 1 : 7;
        
        for (int pas = 1; pas <= limitePas; pas++) {
            int newX = position.x + (dx * pas);
            int newY = position.y + (dy * pas);
            
            if (newX >= 0 && newX < Plateau.SIZE_X && newY >= 0 && newY < Plateau.SIZE_Y) {
                Case[][] cases = plateau.getCases();
                Case caseCandidate = cases[newX][newY];
                
                if (caseCandidate.getPiece() == null) {
                    casesAccessibles.add(caseCandidate);
                } else if (caseCandidate.getPiece().estBlanc() != piece.estBlanc()) {
                    casesAccessibles.add(caseCandidate);
                    break;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }
}