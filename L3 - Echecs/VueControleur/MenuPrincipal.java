package VueControleur;

import java.awt.*;
import javax.swing.*;
import modele.jeu.Jeu;

public class MenuPrincipal extends JFrame {
    private boolean contreIA = false;
    private boolean iaEstBlanc = false;
    private int niveauIA = 0;
    private boolean jeuLance = false;

    public MenuPrincipal() {
        setTitle("Jeu d'Échecs - Menu Principal");
        setSize(600, 700);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setResizable(false);

        Color beige = new Color(240, 217, 181);
        Color marron = new Color(125, 95, 60);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
        mainPanel.setBackground(beige);
        mainPanel.setBorder(BorderFactory.createEmptyBorder(30, 40, 30, 40));
        setContentPane(mainPanel);

        JLabel titreLabel = new JLabel("♟ JEU D'ÉCHECS ♟");
        titreLabel.setFont(new Font("Serif", Font.BOLD, 36));
        titreLabel.setForeground(marron);
        titreLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        JLabel sousTitreLabel = new JLabel("Choisissez votre mode de jeu");
        sousTitreLabel.setFont(new Font("SansSerif", Font.PLAIN, 18));
        sousTitreLabel.setForeground(marron.darker());
        sousTitreLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        // choix mode de jeu 
        JPanel modePanel = createTitledPanel("Mode de jeu", beige, marron);
        JRadioButton vsJoueurButton = new JRadioButton("Jouer contre un ami");
        JRadioButton vsIAButton = new JRadioButton("Jouer contre l'IA");
        styleRadio(vsJoueurButton, beige, marron);
        styleRadio(vsIAButton, beige, marron);

        ButtonGroup modeGroup = new ButtonGroup();
        modeGroup.add(vsJoueurButton);
        modeGroup.add(vsIAButton);
        vsJoueurButton.setSelected(true);
        modePanel.add(vsJoueurButton);
        modePanel.add(vsIAButton);

        // options IA 
        JPanel iaOptionsPanel = createTitledPanel("Options de l'IA", beige, marron);
        iaOptionsPanel.setVisible(false);

        // niveau IA
        JPanel niveauPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        niveauPanel.setBackground(beige);
        JLabel niveauLabel = new JLabel("Niveau :");
        niveauLabel.setForeground(marron);
        JRadioButton facile = new JRadioButton("Facile");
        JRadioButton moyen = new JRadioButton("Moyen");
        JRadioButton difficile = new JRadioButton("Difficile");
        styleRadio(facile, beige, marron);
        styleRadio(moyen, beige, marron);
        styleRadio(difficile, beige, marron);

        ButtonGroup niveauGroup = new ButtonGroup();
        niveauGroup.add(facile); niveauGroup.add(moyen); niveauGroup.add(difficile);
        moyen.setSelected(true);

        niveauPanel.add(niveauLabel);
        niveauPanel.add(facile);
        niveauPanel.add(moyen);
        niveauPanel.add(difficile);

        JPanel couleurPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        couleurPanel.setBackground(beige);
        JLabel couleurLabel = new JLabel("Vous jouez :");
        couleurLabel.setForeground(marron);
        JRadioButton blanc = new JRadioButton("Blancs");
        JRadioButton noir = new JRadioButton("Noirs");
        styleRadio(blanc, beige, marron);
        styleRadio(noir, beige, marron);
        noir.setSelected(true);

        ButtonGroup couleurGroup = new ButtonGroup();
        couleurGroup.add(blanc); couleurGroup.add(noir);

        couleurPanel.add(couleurLabel);
        couleurPanel.add(blanc);
        couleurPanel.add(noir);

        iaOptionsPanel.add(niveauPanel);
        iaOptionsPanel.add(couleurPanel);

        JButton startButton = new JButton("Démarrer la partie");
        startButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        startButton.setFont(new Font("SansSerif", Font.BOLD, 16));
        startButton.setBackground(marron);
        startButton.setForeground(beige);
        startButton.setFocusPainted(false);

        vsIAButton.addActionListener(e -> iaOptionsPanel.setVisible(true));
        vsJoueurButton.addActionListener(e -> iaOptionsPanel.setVisible(false));

        startButton.addActionListener(e -> {
            contreIA = vsIAButton.isSelected();
            if (contreIA) {
                niveauIA = facile.isSelected() ? 0 : moyen.isSelected() ? 1 : 2;
                iaEstBlanc = noir.isSelected(); 
            }
            jeuLance = true;
            setVisible(false);
            lancerJeu();
        });

        
        mainPanel.add(titreLabel);
        mainPanel.add(Box.createRigidArea(new Dimension(0, 20)));
        mainPanel.add(sousTitreLabel);
        mainPanel.add(Box.createRigidArea(new Dimension(0, 30)));
        mainPanel.add(modePanel);
        mainPanel.add(Box.createRigidArea(new Dimension(0, 20)));
        mainPanel.add(iaOptionsPanel);
        mainPanel.add(Box.createRigidArea(new Dimension(0, 30)));
        mainPanel.add(startButton);

        setVisible(true);
    }

    private JPanel createTitledPanel(String title, Color bg, Color text) {
        JPanel panel = new JPanel();
        panel.setBackground(bg);
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(text), title));
        return panel;
    }

    private void styleRadio(JRadioButton rb, Color bg, Color fg) {
        rb.setBackground(bg);
        rb.setForeground(fg);
        rb.setFont(new Font("SansSerif", Font.PLAIN, 14));
    }

    private void lancerJeu() {
        Jeu jeu = new Jeu();
        jeu.configurerIA(contreIA, iaEstBlanc, niveauIA);
        VueControleur vc = new VueControleur(jeu);
        vc.setVisible(true);
        if (contreIA && iaEstBlanc) {
            try { Thread.sleep(600); } catch (InterruptedException e) {}
            jeu.jouerCoupIAInitial();
        }
    }

    public boolean estJeuLance() {
        return jeuLance;
    }
}
