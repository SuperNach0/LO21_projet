#include "FenPrincipale.h"




FenPrincipale::FenPrincipale()
{


    ///LAYOUT PRINCIPAL
    m_layout_principal = new QVBoxLayout;

        ///Objets

            ///boutons de fin
            m_bouton1 = new QPushButton("Nouvelle note",this);
                m_bouton1->connect(m_bouton1,SIGNAL(clicked(bool)),this,SLOT(popup()));


            m_bouton2 = new QPushButton("Quitter",this);
                m_bouton2->connect(m_bouton2,SIGNAL(clicked(bool)),this,SLOT(close()));

    ///ajouts

    m_layout_principal->addWidget(m_bouton1,Qt::AlignRight);
    m_layout_principal->addWidget(m_bouton2,Qt::AlignRight);

    //*** MENU : RIEN NEFONCTIONNE C'EST JUSTE DES TESTS POUR L'INSTANT

    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
        //ajout d'une action
        QAction *actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
        actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
        connect(actionQuitter,SIGNAL(triggered(bool)),this,SLOT(close()));

    //ajout d'un 2e menu
    QMenu *menuEdition = menuBar()->addMenu("&Edition");
        //ajout d'un sous-menu
        QMenu* s_menuOptions = menuEdition->addMenu("Options");
            //ajout de 2 actions dans le sous-menu
            QAction* retablir = new QAction("Rétablir");
            s_menuOptions->addAction(retablir);

            QAction* annuler = new QAction("Annuler");
            s_menuOptions->addAction(annuler);


        //ajout d'une action
        QAction* action_test = new QAction("&test");
        menuEdition->addAction(action_test);

    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");


    QWidget* zoneCentrale = new QWidget;
    zoneCentrale->setLayout(m_layout_principal);
    setCentralWidget(zoneCentrale);


}

// FENETRE QUI S'AFFICHE QUAND ON CLIQUE sur "Nouvelle Note"
fenetre_creation_note::fenetre_creation_note() : QWidget()
{
    m_layout_choix = new QVBoxLayout; //création layout


    //Création des différents champs du formulaire
    id = new QLineEdit("Entre l'id poulet");
    titre = new QLineEdit("Titre ici");


    //Ajout des objets au layout
    m_layout_choix->addWidget(id);
    m_layout_choix->addWidget(titre);


    this->setLayout(m_layout_choix); //affectation du layout

    this->move(100,100); //décalage de la nouvelle fenetre par rapport à la première

}

void FenPrincipale :: popup()
{
    fenetre_creation_note* fenetre = new fenetre_creation_note;
    fenetre->show();
}

