package VueControleur;

import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;
import javax.swing.*;

import modele.jeu.Cavalier;
import modele.jeu.Coup;
import modele.jeu.Dame;
import modele.jeu.Fou;
import modele.jeu.Jeu;
import modele.plateau.Case;
import modele.jeu.Piece;
import modele.jeu.Pion;
import modele.jeu.Roi;
import modele.jeu.Tour;
import modele.plateau.Plateau;


public class VueControleur extends JFrame implements Observer {
    private Plateau plateau;
    private Jeu jeu;
    private final int sizeX; 
    private final int sizeY;
    private static final int pxCase = 90; 

    private ImageIcon icoRoiNoir;
    private ImageIcon icoRoiBlanc;
    private ImageIcon icoDameBlanc;
    private ImageIcon icoDameNoir;
    private ImageIcon icoFouBlanc;
    private ImageIcon icoFouNoir;
    private ImageIcon icoCavalierBlanc;
    private ImageIcon icoCavalierNoir; 
    private ImageIcon icoTourBlanc;
    private ImageIcon icoTourNoir;
    private ImageIcon icoPionBlanc; 
    private ImageIcon icoPionNoir;

    private Case caseClic1; 
    private Case caseClic2;


    private JLabel[][] tabJLabel; 

    private JPanel infoPanel;
    private JLabel scoreBlancLabel;
    private JLabel scoreNoirLabel;
    private JLabel messageLabel;

    private JTextArea historiqueTextArea;
    
    private boolean finDePartieDejaAffichee = false;



    public VueControleur(Jeu _jeu) {
        jeu = _jeu;

        jeu.setPromotionListener(estBlanc -> {
            String[] options = {"Dame", "Tour", "Fou", "Cavalier"};
            int choix = JOptionPane.showOptionDialog(
                this,
                "Choisissez la pièce pour la promotion du pion",
                "Promotion",
                JOptionPane.DEFAULT_OPTION,
                JOptionPane.QUESTION_MESSAGE,
                null,
                options,
                options[0]
            );
        
            switch (choix) {
                case 1: return new Tour(jeu.getPlateau(), estBlanc);
                case 2: return new Fou(jeu.getPlateau(), estBlanc);
                case 3: return new Cavalier(jeu.getPlateau(), estBlanc);
                default: return new Dame(jeu.getPlateau(), estBlanc);
            }
        });        

        plateau = jeu.getPlateau();
        sizeX = plateau.SIZE_X;
        sizeY = plateau.SIZE_Y;



        chargerLesIcones();
        placerLesComposantsGraphiques();

        plateau.addObserver(this);

        mettreAJourAffichage();

    }


    private void chargerLesIcones() {
        icoRoiBlanc = chargerIcone("Images/wK.png");
        icoDameBlanc = chargerIcone("Images/wQ.png");
        icoFouBlanc = chargerIcone("Images/wB.png");
        icoCavalierBlanc = chargerIcone("Images/wN.png");
        icoTourBlanc = chargerIcone("Images/wR.png");
        icoPionBlanc = chargerIcone("Images/wP.png");

        icoRoiNoir = chargerIcone("Images/bK.png");
        icoDameNoir = chargerIcone("Images/bQ.png");
        icoFouNoir = chargerIcone("Images/bB.png");
        icoCavalierNoir = chargerIcone("Images/bN.png");
        icoTourNoir = chargerIcone("Images/bR.png");
        icoPionNoir = chargerIcone("Images/bP.png");

    }
    private ImageIcon chargerIcone(String urlIcone) {

        ImageIcon icon = new ImageIcon(urlIcone);

        Image img = icon.getImage().getScaledInstance(pxCase, pxCase, Image.SCALE_SMOOTH);
        ImageIcon resizedIcon = new ImageIcon(img);

        return resizedIcon;
    }



    private ArrayList<Case> casesMarquees = new ArrayList<>();

    private Color couleurOriginaleCasePaire = new Color(240, 217, 181); 
    private Color couleurOriginaleCaseImpaire = new Color(181, 136, 99); 
    private Color couleurCaseAccessible = new Color(255, 255, 0, 100); 

    private void marquerCasesAccessibles(ArrayList<Case> cases) {
        casesMarquees.clear();
        casesMarquees.addAll(cases);
        
        for (Case c : cases) {
            Point pos = plateau.getPositionCase(c);
            if (pos != null) {
                int x = pos.x;
                int y = pos.y;
                
                tabJLabel[x][y].setBackground(couleurCaseAccessible);
            }
        }
    }

    private void effacerMarquageCasesAccessibles() {
        for (Case c : casesMarquees) {
            Point pos = plateau.getPositionCase(c);
            if (pos != null) {
                int x = pos.x;
                int y = pos.y;
                
                if ((y%2 == 0 && x%2 == 0) || (y%2 != 0 && x%2 != 0)) {
                    tabJLabel[x][y].setBackground(couleurOriginaleCaseImpaire);
                } else {
                    tabJLabel[x][y].setBackground(couleurOriginaleCasePaire);
                }
            }
        }
        casesMarquees.clear();
    }


    private void placerLesComposantsGraphiques() {
        setTitle("Jeu d'Échecs");
        setResizable(false);
        setSize(sizeX * pxCase + 200, sizeY * pxCase); 
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        
        getContentPane().setLayout(new BorderLayout());

        
        JPanel grilleJLabels = new JPanel(new GridLayout(sizeY, sizeX));
        tabJLabel = new JLabel[sizeX][sizeY];

        for (int y = 0; y < sizeY; y++) {
            for (int x = 0; x < sizeX; x++) {
                JLabel jlab = new JLabel();
                tabJLabel[x][y] = jlab;

                final int xx = x;
                final int yy = y;

                jlab.addMouseListener(new MouseAdapter() {
                    @Override
                    public void mouseClicked(MouseEvent e) {
                        if (caseClic1 == null) {
                            caseClic1 = plateau.getCases()[xx][yy];

                            Piece piece = caseClic1.getPiece();
                            if (piece != null) {
                                ArrayList<Case> casesAccessibles = piece.getCasesAccessibles();

                                if (casesAccessibles.isEmpty()) {
                                    caseClic1 = null;
                                } else {
                                    marquerCasesAccessibles(casesAccessibles);
                                }
                            } else {
                                caseClic1 = null;
                            }
                        } else {
                            caseClic2 = plateau.getCases()[xx][yy];
                            effacerMarquageCasesAccessibles();

                            Piece piece = caseClic1.getPiece();
                            if (piece != null) {
                                ArrayList<Case> casesAccessibles = piece.getCasesAccessibles();
                                if (casesAccessibles.contains(caseClic2)) {
                                    jeu.envoyerCoup(new Coup(caseClic1, caseClic2));
                                }
                            }


                            caseClic1 = null;
                            caseClic2 = null;
                        }
                    }
                });

                jlab.setOpaque(true);
                if ((y % 2 == 0 && x % 2 == 0) || (y % 2 != 0 && x % 2 != 0)) {
                    jlab.setBackground(couleurOriginaleCaseImpaire);
                } else {
                    jlab.setBackground(couleurOriginaleCasePaire);
                }

                grilleJLabels.add(jlab);
            }
        }

        getContentPane().add(grilleJLabels, BorderLayout.CENTER);

        infoPanel = new JPanel();
        infoPanel.setLayout(new BoxLayout(infoPanel, BoxLayout.Y_AXIS));
        infoPanel.setPreferredSize(new Dimension(200, sizeY * pxCase));

        scoreBlancLabel = new JLabel("Score Blancs : 0");
        scoreNoirLabel = new JLabel("Score Noirs : 0");
        messageLabel = new JLabel("Tour : Blancs");

        scoreBlancLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        scoreNoirLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        messageLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        infoPanel.add(Box.createVerticalStrut(20));
        infoPanel.add(scoreBlancLabel);
        infoPanel.add(Box.createVerticalStrut(10));
        infoPanel.add(scoreNoirLabel);
        infoPanel.add(Box.createVerticalStrut(30));
        infoPanel.add(messageLabel);

        getContentPane().add(infoPanel, BorderLayout.EAST);



        historiqueTextArea = new JTextArea(15, 15);
        historiqueTextArea.setEditable(false);
        historiqueTextArea.setLineWrap(true);
        historiqueTextArea.setWrapStyleWord(true);

        JScrollPane scrollPane = new JScrollPane(historiqueTextArea);
        scrollPane.setBorder(BorderFactory.createTitledBorder("Historique"));
        infoPanel.add(Box.createVerticalStrut(30));
        infoPanel.add(scrollPane);

    }



    private void mettreAJourAffichage() {

        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeY; y++) {

                Case c = plateau.getCases()[x][y];

                if (c != null) {

                    Piece e = c.getPiece();

                    if (e != null) {
                        if (e instanceof Roi) {
                            tabJLabel[x][y].setIcon(e.estBlanc() ? icoRoiBlanc : icoRoiNoir);
                        } else if (e instanceof Dame) {
                            tabJLabel[x][y].setIcon(e.estBlanc() ? icoDameBlanc : icoDameNoir);
                        } else if (e instanceof Tour) {
                            tabJLabel[x][y].setIcon(e.estBlanc() ? icoTourBlanc : icoTourNoir);
                        } else if (e instanceof Fou) {
                            tabJLabel[x][y].setIcon(e.estBlanc() ? icoFouBlanc : icoFouNoir);
                        } else if (e instanceof Cavalier) {
                            tabJLabel[x][y].setIcon(e.estBlanc() ? icoCavalierBlanc : icoCavalierNoir);
                        } else if (e instanceof Pion) {
                            tabJLabel[x][y].setIcon(e.estBlanc() ? icoPionBlanc : icoPionNoir);
                        }
                    } else {
                        tabJLabel[x][y].setIcon(null);
                    }


                }

            }
        }
    }

    @Override
    public void update(Observable o, Object arg) {
        mettreAJourAffichage();
    
        scoreBlancLabel.setText("Score Blancs : " + jeu.getScoreBlanc());
        scoreNoirLabel.setText("Score Noirs : " + jeu.getScoreNoir());        
        
    
        boolean estTourBlanc = jeu.getTourBlanc();

        if (jeu.estEnEchecEtMatSansNotification(estTourBlanc)) {
            if (!finDePartieDejaAffichee) {
                finDePartieDejaAffichee = true;
                String gagnant = !estTourBlanc ? "Blancs" : "Noirs";
                messageLabel.setText("<html>Échec et mat !<br>Les " + gagnant + " gagnent</html>");
                afficherFinPartie("Echec et mat ! Les " + gagnant + " gagnent !");
            }
            return;
        } else if (jeu.estPatSansNotification(estTourBlanc)) {
            if (!finDePartieDejaAffichee) {
                finDePartieDejaAffichee = true;
                messageLabel.setText("Match nul par pat !");
                afficherFinPartie("Match nul par pat !");
            }
            return;
        } else if (jeu.estTroisFoisMêmePosition()) {
            if (!finDePartieDejaAffichee) {
                finDePartieDejaAffichee = true;
                messageLabel.setText("Match nul par répétition !");
                afficherFinPartie("Match nul par répétition !");
            }
            return;
        } else if (jeu.estEnEchec(estTourBlanc)) {
            messageLabel.setText((estTourBlanc ? "Blancs" : "Noirs") + " en échec");
        } else {
            messageLabel.setText("Tour : " + (jeu.getTourBlanc() ? "Blancs" : "Noirs"));
        }

        StringBuilder sb = new StringBuilder();
        ArrayList<String> historique = jeu.getHistoriqueCoups();
        for (int i = 0; i < historique.size(); i++) {
            sb.append((i + 1) + ". " + historique.get(i) + "\n");
        }
        historiqueTextArea.setText(sb.toString());

    }
    


    private void afficherFinPartie(String messageFinal) {
        JOptionPane.showMessageDialog(
            this,
            messageFinal + "\nRetour au menu.",
            "Fin de partie",
            JOptionPane.INFORMATION_MESSAGE
        );

        jeu.stopJeu();
        dispose();
        new MenuPrincipal().setVisible(true);
    }

    
    
    
}
