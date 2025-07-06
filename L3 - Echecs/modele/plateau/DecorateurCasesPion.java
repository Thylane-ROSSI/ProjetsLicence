package modele.plateau;

import modele.jeu.*;
import java.awt.Point;
import java.util.ArrayList;

public class DecorateurCasesPion extends DecorateurCasesAccessibles {
    public DecorateurCasesPion(DecorateurCasesAccessibles _baseDecorateur) {
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
        
        int direction = piece.estBlanc() ? -1 : 1; 
        boolean premierCoup = (piece.estBlanc() && position.y == 6) || (!piece.estBlanc() && position.y == 1);
        
        
        int newY = position.y + direction;
        if (newY >= 0 && newY < Plateau.SIZE_Y) {
            Case[][] cases = plateau.getCases();
            Case caseDavant = cases[position.x][newY];
            
            
            if (caseDavant.getPiece() == null) {
                casesAccessibles.add(caseDavant);
                
                
                if (premierCoup) {
                    int doublePas = position.y + (2 * direction);
                    if (doublePas >= 0 && doublePas < Plateau.SIZE_Y) {
                        Case caseDoublePas = cases[position.x][doublePas];
                        if (caseDoublePas.getPiece() == null) {
                            casesAccessibles.add(caseDoublePas);
                        }
                    }
                }
            }

            
            for (int dx : new int[]{-1, 1}) {
                int newX = position.x + dx;
                if (newX >= 0 && newX < Plateau.SIZE_X) {
                    Case caseDiag = cases[newX][newY];
                    if (caseDiag.getPiece() != null && caseDiag.getPiece().estBlanc() != piece.estBlanc()) {
                        casesAccessibles.add(caseDiag);
                    }
                }
            }
        }

    // Prise en passant
    Coup dernierCoup = plateau.getJeu().getDernierCoup();
    if (dernierCoup != null && dernierCoup.dep != null && dernierCoup.arr != null) {
        Piece pionAdverse = dernierCoup.arr.getPiece();

        
        if (pionAdverse instanceof Pion && pionAdverse.estBlanc() != piece.estBlanc()) {

            Point derniereDep = plateau.getPositionCase(dernierCoup.dep);
            Point derniereArr = plateau.getPositionCase(dernierCoup.arr);

            boolean doublePas = Math.abs(derniereArr.y - derniereDep.y) == 2;
            boolean memeLigne = derniereArr.y == position.y;
            boolean estAdjacent = Math.abs(derniereArr.x - position.x) == 1;

            if (doublePas && memeLigne && estAdjacent) {
                int yCible = position.y + direction;
                if (yCible >= 0 && yCible < Plateau.SIZE_Y) {
                    Case caseEnPassant = plateau.getCases()[derniereArr.x][yCible];
                    if (caseEnPassant.getPiece() == null) {
                        
                        casesAccessibles.add(caseEnPassant);
                    }
                }
            }
        }
    
    }

        return casesAccessibles;
    }
}
