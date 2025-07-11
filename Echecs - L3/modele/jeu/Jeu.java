package modele.jeu;


import modele.plateau.Case;
import modele.plateau.Plateau;

import java.util.ArrayList;
import java.util.HashMap;


import java.awt.Point;

public class Jeu extends Thread{
    private Plateau plateau;

    private boolean tourBlanc = true; 
    public Coup coupRecu;

   
    private boolean contreIA = false;
    private boolean iaEstBlanc = false;
    private int niveauIA = 0; 



    private int scoreBlanc = 0;
    private int scoreNoir = 0;

    public int getScoreBlanc() { return scoreBlanc; }
    public int getScoreNoir() { return scoreNoir; }

    private HashMap<String, Integer> repetitionPositions = new HashMap<>(); // Compter plusieurs fois la même position

    private boolean enCours = true; 
    
    private PromotionListener promotionListener;

    private Coup dernierCoup;

    private ArrayList<String> historiqueCoups = new ArrayList<>();

    public Jeu() {
        plateau = new Plateau();
        plateau.setJeu(this);

        plateau.placerPieces();

        start();

    } 


    public void stopJeu() {
        enCours = false;
        synchronized (this) {
            notify(); 
        }
    }

    public void jouerCoupIAInitial() {
        if (contreIA && iaEstBlanc && tourBlanc) {
            new Thread(() -> {
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {}
                
                Coup coupIA = IA.choisirCoup(plateau, iaEstBlanc, niveauIA);
                if (coupIA != null) {
                    envoyerCoup(coupIA);
                }
            }).start();
        }
    }
    

    public Plateau getPlateau() {
        return plateau;
    }

    public void placerPieces() {

        plateau.placerPieces();
    }


    public void annulerCoup(Coup coup, Piece pieceCapturee) {
        Piece piece = coup.arr.getPiece();
    
        coup.arr.quitterLaCase();
        if (pieceCapturee != null) {
            pieceCapturee.setCase(coup.arr);
        }
    
        piece.setCase(coup.dep);
        plateau.notifierObservateurs();
    }
    

    public ArrayList<String> getHistoriqueCoups() { return historiqueCoups; }

    public void envoyerCoup(Coup coup) {
        if (!enCours) return;
    
        Piece piece = coup.dep.getPiece();
        if (piece == null || piece.estBlanc() != tourBlanc) return;
    
        ArrayList<Case> casesAccessibles = piece.getCasesAccessibles();
        if (!casesAccessibles.contains(coup.arr)) return;
    
        Piece pieceCapturee = coup.arr.getPiece();
        boolean estPriseEnPassant = false;
    
        // Gérer la prise en passant
        if (piece instanceof Pion) {
            Point depPos = plateau.getPositionCase(coup.dep);
            Point arrPos = plateau.getPositionCase(coup.arr);
    
            if (Math.abs(depPos.x - arrPos.x) == 1 && pieceCapturee == null && dernierCoup != null) {
                Piece pionAdverse = dernierCoup.arr.getPiece(); 
                Point dernierDep = plateau.getPositionCase(dernierCoup.dep);
                Point dernierArr = plateau.getPositionCase(dernierCoup.arr);
        
                boolean doublePas = Math.abs(dernierArr.y - dernierDep.y) == 2;
                boolean memeCol = dernierArr.x == arrPos.x;
                boolean memeLigne = dernierArr.y == depPos.y;
        
                if (pionAdverse instanceof Pion && doublePas && memeCol && memeLigne &&
                    pionAdverse.estBlanc() != piece.estBlanc()) {
        
                    Case casePionCapture = plateau.getCases()[arrPos.x][depPos.y];
                    pieceCapturee = casePionCapture.getPiece();
                    casePionCapture.quitterLaCase();
                    estPriseEnPassant = true;
                }
            }
        
        }
    
        appliquerCoup(coup);
    
        if (piece instanceof Roi) {
            ((Roi) piece).gererRoqueSiNecessaire(coup);
        }
    
        if (estEnEchec(tourBlanc)) {
            annulerCoup(coup, pieceCapturee);
    
            if (estPriseEnPassant) {
                Point arrPos = plateau.getPositionCase(coup.arr);
                Point depPos = plateau.getPositionCase(coup.dep);
                pieceCapturee.setCase(plateau.getCases()[arrPos.x][depPos.y]);
            }
    
            if (contreIA && tourBlanc == iaEstBlanc) {
                tourBlanc = !tourBlanc; 
            }

            if (contreIA && tourBlanc == iaEstBlanc) {
                new Thread(() -> {
                    try { Thread.sleep(200); } catch (InterruptedException ignored) {}
                    Coup coupIA = IA.choisirCoup(plateau, iaEstBlanc, niveauIA);
                    if (coupIA != null) envoyerCoup(coupIA);
                }).start();
            }
            return;
        }
    
        historiqueCoups.add(descriptionCoup(coup, piece));
    
        // Promotion
        if (piece instanceof Pion) {
            Point pos = plateau.getPositionCase(piece.getCase());
            if ((piece.estBlanc() && pos.y == 0) || (!piece.estBlanc() && pos.y == Plateau.SIZE_Y - 1)) {
                if (promotionListener != null) {
                    Piece promotion = promotionListener.choisirPromotion(piece.estBlanc());
                    Case promotionCase = piece.getCase();
                    promotionCase.p = promotion;
                    promotion.setCase(promotionCase);
                    piece = promotion;
                }
            }
        }
    
        // Points
        if (pieceCapturee != null) {
            int points = 0;
            if (pieceCapturee instanceof Pion) points = 1;
            else if (pieceCapturee instanceof Fou || pieceCapturee instanceof Cavalier) points = 3;
            else if (pieceCapturee instanceof Tour) points = 5;
            else if (pieceCapturee instanceof Dame) points = 9;
    
            if (tourBlanc) scoreBlanc += points;
            else scoreNoir += points;
        }
    
        tourBlanc = !tourBlanc;
        plateau.notifierObservateurs();
    
        String position = encoderPosition();
        repetitionPositions.put(position, repetitionPositions.getOrDefault(position, 0) + 1);
    
        coupRecu = coup;
        dernierCoup = coup;    

        synchronized (this) {
            notify();
        }
        
        plateau.notifierObservateurs(); 


    
        if (contreIA && enCours && tourBlanc == iaEstBlanc) {
            new Thread(() -> {
                try { Thread.sleep(500); } catch (InterruptedException ignored) {}
                Coup coupIA = IA.choisirCoup(plateau, iaEstBlanc, niveauIA);
                if (coupIA != null) envoyerCoup(coupIA);
            }).start();
        }
    }
    
    
    private String descriptionCoup(Coup coup, Piece piece) {
        Point dep = plateau.getPositionCase(coup.dep);
        Point arr = plateau.getPositionCase(coup.arr);
        String nom = piece.getClass().getSimpleName();
        return nom + " : " + (char)('a' + dep.x) + (8 - dep.y) + " -> " + (char)('a' + arr.x) + (8 - arr.y);
    }
    
    public interface PromotionListener {
        Piece choisirPromotion(boolean estBlanc);
    }

    public void setPromotionListener(PromotionListener listener) {
        this.promotionListener = listener;
    }

    
    public void appliquerCoup(Coup coup) {
    
        plateau.deplacerPiece(coup.dep, coup.arr);
    }
    

    
    public boolean estEnEchec(boolean estBlanc) {
        Roi roi = trouverRoi(estBlanc);
        if (roi == null) return false;
        Case caseRoi = roi.getCase();
    
        for (Case[] ligne : plateau.getCases()) {
            for (Case c : ligne) {
                Piece piece = c.getPiece();
                if (piece != null && piece.estBlanc() != estBlanc) {
                    ArrayList<Case> coupsPossibles = piece.getCasesAccessibles();
                    if (coupsPossibles.contains(caseRoi)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    private Roi trouverRoi(boolean estBlanc) {
        for (Case[] ligne : plateau.getCases()) {
            for (Case c : ligne) {
                if (c.getPiece() instanceof Roi && c.getPiece().estBlanc() == estBlanc) {
                    return (Roi)c.getPiece();
                }
            }
        }
        return null;
    }

    
    
    public boolean estEnEchecEtMat(boolean estBlanc) {
        if (!estEnEchec(estBlanc)) return false;
    
        for (Case[] ligne : plateau.getCases()) {
            for (Case c : ligne) {
                Piece piece = c.getPiece();
                if (piece != null && piece.estBlanc() == estBlanc) {
                    for (Case cible : piece.getCasesAccessibles()) {
                        Coup coupTest = new Coup(c, cible);
                        Piece pieceCapturee = cible.getPiece(); 
    
                        appliquerCoup(coupTest);
                        boolean enEchecApresCoup = estEnEchec(estBlanc);
                        annulerCoup(coupTest, pieceCapturee);
    
                        if (!enEchecApresCoup) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
    
    

    public boolean getTourBlanc() {
        return tourBlanc;
    }
    
    
    

    private boolean simulerCoupEtVerifieEchec(Piece piece, Case dep, Case arr, boolean estBlanc) {
        Case ancienneCase = dep;
        Piece pieceCapturee = arr.getPiece();
    
        dep.quitterLaCase();
        arr.quitterLaCase();
        piece.setCase(arr);
    
        boolean enEchec = estEnEchec(estBlanc);
    
        arr.quitterLaCase();
        if (pieceCapturee != null) pieceCapturee.setCase(arr);
        piece.setCase(ancienneCase);
    
        return enEchec;
    }
    
    private boolean dernierCoupBlanc;

    public boolean getDernierCoupBlanc() {
    return dernierCoupBlanc;
    }




public boolean estPat(boolean estBlanc) {
    if (estEnEchec(estBlanc)) return false;

    for (Case[] ligne : plateau.getCases()) {
        for (Case c : ligne) {
            Piece piece = c.getPiece();
            if (piece != null && piece.estBlanc() == estBlanc) {
                for (Case cible : piece.getCasesAccessibles()) {
                    Coup coupTest = new Coup(c, cible);
                    Piece pieceCapturee = cible.getPiece();

                    appliquerCoup(coupTest);
                    boolean enEchecApres = estEnEchec(estBlanc);
                    annulerCoup(coupTest, pieceCapturee);

                    if (!enEchecApres) {
                        return false; 
                    }
                }
            }
        }
    }
    return true;
}


public void configurerIA(boolean actif, boolean estBlanc, int niveau) {
    this.contreIA = actif;
    this.iaEstBlanc = estBlanc;
    this.niveauIA = niveau;
}

public boolean estTroisFoisMêmePosition() {
    String position = encoderPosition();
    return repetitionPositions.getOrDefault(position, 0) >= 3;
}

private String encoderPosition() { // converti l'etat actuel du plateau en une chaine de caractères
    StringBuilder sb = new StringBuilder();
    for (Case[] ligne : plateau.getCases()) {
        for (Case c : ligne) {
            Piece p = c.getPiece();
            if (p == null) {
                sb.append(".");
            } else {
                sb.append(p.estBlanc() ? "B" : "N");
                sb.append(p.getClass().getSimpleName().charAt(0));
            }
        }
    }
    sb.append(tourBlanc ? "W" : "B");
    return sb.toString();
}

public Coup getDernierCoup() {
    return dernierCoup;
}


// Les sans notifiactions permettent de ne pas appeler les observateurs et de ne pas mettre à jour le pleatau graphiquement

public boolean estEnEchecEtMatSansNotification(boolean estBlanc) {
    if (!estEnEchec(estBlanc)) return false;

    for (Case[] ligne : plateau.getCases()) {
        for (Case c : ligne) {
            Piece piece = c.getPiece();
            if (piece != null && piece.estBlanc() == estBlanc) {
                for (Case cible : piece.getCasesAccessibles()) {
                    if (!simulerCoupEtVerifieEchec(piece, c, cible, estBlanc)) {
                        return false; 
                    }
                }
            }
        }
    }
    return true;
}

private void annulerCoupSansNotification(Coup coup, Piece pieceCapturee) {
    Piece piece = coup.arr.getPiece();
    coup.arr.quitterLaCase();
    if (pieceCapturee != null) {
        pieceCapturee.setCase(coup.arr);
    }
    piece.setCase(coup.dep);
}

public boolean estPatSansNotification(boolean estBlanc) {
    if (estEnEchec(estBlanc)) return false;

    for (Case[] ligne : plateau.getCases()) {
        for (Case c : ligne) {
            Piece piece = c.getPiece();
            if (piece != null && piece.estBlanc() == estBlanc) {
                for (Case cible : piece.getCasesAccessibles()) {
                    Coup coupTest = new Coup(c, cible);
                    Piece pieceCapturee = cible.getPiece();

                    boolean notifieAvant = false;
                    if (plateau.hasChanged()) {
                        notifieAvant = true;
                    }

                    appliquerCoup(coupTest);
                    boolean enEchecApres = estEnEchec(estBlanc);
                    annulerCoupSansNotification(coupTest, pieceCapturee);

                    if (!enEchecApres) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}


}