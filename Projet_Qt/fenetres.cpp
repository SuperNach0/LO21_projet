#include "fenetres.h"




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

    //*** MENU : RIEN NEFONCTIONNE C'EST JUSTE DES TESTS POUR L'INSTANT, je finirais après

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
    m_id = new QLineEdit("Entre l'id poulet",this);
    m_titre = new QLineEdit("Titre ici",this);
    m_date_creat = m_date_modif = QDateTime();
    m_date_creat = m_date_modif = QDateTime::currentDateTime();
    m_label_date_creat = new QLabel("Date de création : " + m_date_creat.toString("dddd dd MMMM yyyy"),this);
    m_label_date_modif = new QLabel("Date de dernière modif : " + m_date_modif.toString("dddd dd MMMM yyyy"),this);
    m_texte = new QTextEdit("texte/description/action ici",this);


    m_article = new QRadioButton("Article",this);
        m_article->toggle();
    m_tache = new QRadioButton("Tache",this);
        m_groupe_tache = new QWidget(this);
        m_layout_tache = new QVBoxLayout;
        m_groupe_tache->setLayout(m_layout_tache);
        m_groupe_tache->setVisible(false);
        m_tache->connect(m_tache,SIGNAL(toggled(bool)),m_groupe_tache,SLOT(setVisible(bool)));

        QLabel* label_spinbox = new QLabel("Priorité, 0 si aucune priorité",this);
        m_priorite = new QSpinBox(this);
        m_case_calendrier = new QCheckBox("Echeance",this);
            m_calendrier = new QCalendarWidget(this);
            m_calendrier->setVisible(false);
            m_case_calendrier->connect(m_case_calendrier,SIGNAL(toggled(bool)),m_calendrier,SLOT(setVisible(bool)));

    m_media = new QRadioButton("Media",this);
        m_selection_fichier = new QPushButton("Parcourir...",this);
            m_selection_fichier->setVisible(false);
            m_selection_fichier->connect(m_selection_fichier,SIGNAL(clicked(bool)),this,SLOT(choisir_fichier()));
        m_media->connect(m_media,SIGNAL(toggled(bool)),m_selection_fichier,SLOT(setVisible(bool)));




    //Connexions signaux/slots pour afficher/cacher les champs concernés


    //Ajout des objets au layout
    m_layout_choix->addWidget(m_id);
    m_layout_choix->addWidget(m_titre);
    m_layout_choix->addWidget(m_label_date_creat);
    m_layout_choix->addWidget(m_label_date_modif);
    m_layout_choix->addWidget(m_article);
    m_layout_choix->addWidget(m_tache);
    m_layout_choix->addWidget(m_media);
    m_layout_choix->addWidget(m_texte);
    m_layout_choix->addWidget(m_selection_fichier);

    m_layout_tache->addWidget(label_spinbox);
    m_layout_tache->addWidget(m_priorite);
    m_layout_tache->addWidget(m_case_calendrier);
    m_layout_tache->addWidget(m_calendrier);

    m_layout_choix->addWidget(m_groupe_tache);




    this->setLayout(m_layout_choix); //affectation du layout
    this->move(100,100); //décalage de la nouvelle fenetre par rapport à la première

}

void fenetre_creation_note :: choisir_fichier()
{
    m_fichier = new QString("");
    *m_fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
}

void FenPrincipale :: popup()
{
    fenetre_creation_note* fenetre = new fenetre_creation_note;
    fenetre->show();
}

