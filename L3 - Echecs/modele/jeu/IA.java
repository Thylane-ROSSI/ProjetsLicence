package modele.jeu;

import modele.plateau.*;
import java.util.ArrayList;
import java.util.Random;
import java.awt.Point;

public class IA {
    private static final Random rand = new Random();

    public static Coup choisirCoup(Plateau plateau, boolean estBlanc, int niveau) {
        ArrayList<Coup> tousLesCoups = getTousLesCoupsPossibles(plateau, estBlanc);

        if (tousLesCoups.isEmpty()) return null;

        switch (niveau) {
            case 0: // Facile 
                return tousLesCoups.get(rand.nextInt(tousLesCoups.size()));

            case 1: // Moyen 
                return choisirMeilleureCapture(plateau, tousLesCoups);

            case 2: // Difficile 
                return choisirCoupStrategique(plateau, tousLesCoups);

            default:
                return tousLesCoups.get(0);
        }
    }

    private static ArrayList<Coup> getTousLesCoupsPossibles(Plateau plateau, boolean estBlanc) {
        ArrayList<Coup> liste = new ArrayList<>();
        Jeu jeu = plateau.getJeu();

        for (Case[] ligne : plateau.getCases()) {
            for (Case c : ligne) {
                Piece p = c.getPiece();
                if (p != null && p.estBlanc() == estBlanc) {
                    for (Case cible : p.getCasesAccessibles()) {
                        Coup coup = new Coup(c, cible);
                        Piece pieceCapturee = cible.getPiece();

                        jeu.appliquerCoup(coup);
                        boolean enEchec = jeu.estEnEchec(estBlanc);
                        jeu.annulerCoup(coup, pieceCapturee);

                        if (!enEchec) {
                            liste.add(coup);
                        }
                    }
                }
            }
        }
        return liste;
    }

    private static Coup choisirMeilleureCapture(Plateau plateau, ArrayList<Coup> coups) {
        Coup meilleurCoup = null;
        int maxValeur = -1;

        for (Coup c : coups) {
            Piece cible = c.arr.getPiece();
            if (cible != null) {
                int valeur = getValeurPiece(cible);
                if (valeur > maxValeur) {
                    maxValeur = valeur;
                    meilleurCoup = c;
                }
            }
        }

        return (meilleurCoup != null) ? meilleurCoup : coups.get(rand.nextInt(coups.size()));
    }

    private static Coup choisirCoupStrategique(Plateau plateau, ArrayList<Coup> coups) {
        int meilleurScore = Integer.MIN_VALUE;
        Coup meilleurCoup = null;

        for (Coup c : coups) {
            int score = evaluerCoup(c, plateau);
            if (score > meilleurScore) {
                meilleurScore = score;
                meilleurCoup = c;
            }
        }

        return (meilleurCoup != null) ? meilleurCoup : coups.get(rand.nextInt(coups.size()));
    }

    private static int evaluerCoup(Coup coup, Plateau plateau) {
        int score = 0;

        Piece cible = coup.arr.getPiece();
        if (cible != null) {
            score += getValeurPiece(cible) * 10;
        }

        Point pos = plateau.getPositionCase(coup.arr);
        if (pos.x >= 3 && pos.x <= 4 && pos.y >= 3 && pos.y <= 4) {
            score += 3;
        }

        Piece piece = coup.dep.getPiece();
        if (piece instanceof Cavalier || piece instanceof Fou) {
            if (piece.getCase() == coup.dep) {
                score += 2;
            }
        }

        return score;
    }

    private static int getValeurPiece(Piece p) {
        if (p instanceof Pion) return 1;
        if (p instanceof Cavalier || p instanceof Fou) return 3;
        if (p instanceof Tour) return 5;
        if (p instanceof Dame) return 9;
        if (p instanceof Roi) return 100;
        return 0;
    }
}
