#include "fenetres.h"
#include "notes.h"





FenPrincipale::FenPrincipale()
{
    ///LAYOUT PRINCIPAL
    m_layout_principal = new QVBoxLayout;


    //********* MENU FICHIER **********

    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
        //ajout d'une action
        QAction *actionQuitter = new QAction("&Quitter", this);
            actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
            connect(actionQuitter,SIGNAL(triggered(bool)),this,SLOT(close()));
        QAction *actionNouveau = new QAction("&Nouvelle Note",this);
            actionNouveau->setShortcut(QKeySequence("Ctrl+N"));
            connect(actionNouveau,SIGNAL(triggered(bool)),this,SLOT(popup()));

        menuFichier->addAction(actionQuitter);
        menuFichier->addAction(actionNouveau);


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

    //Barre d'outils
    m_toolbar = addToolBar("fichier");
        actionNouveau->setIcon(QIcon("icone_nouveau.png"));
        m_toolbar->addAction(actionNouveau);
        m_toolbar->addAction(actionQuitter);



    //Configuration emplacement des fenetres
    QMdiArea* zoneCentrale = new QMdiArea;
    zoneCentrale->setLayout(m_layout_principal);


    //CREATION ONGLETS
    creation_tabs();
        m_layout_principal->addWidget(m_onglets);

    //CREATION DES DOCKS
    creation_docks();



    setCentralWidget(zoneCentrale);


}

// *************** FENETRE CREATION NOTE ****************


fenetre_creation_note::fenetre_creation_note() : QWidget()
{
    this->setWindowModality(Qt::ApplicationModal); //pour que la fenetre parente ne soit pas utilisable quand celle ci est ouverte
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

    m_save = new QPushButton("Sauvegarder",this);
        m_save->connect(m_save,SIGNAL(clicked(bool)),this,SLOT(save()));
    m_quit = new QPushButton("Annuler",this);
        m_quit->connect(m_quit,SIGNAL(clicked(bool)),this,SLOT(close()));

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
    m_layout_choix->addWidget(m_save);
    m_layout_choix->addWidget(m_quit);


    this->setLayout(m_layout_choix); //affectation du layout
    this->move(100,100); //décalage de la nouvelle fenetre par rapport à la première

}

void FenPrincipale::creation_docks()
{

    m_dock_affichage_notes = new QDockWidget("Notes", this);    //nouveau dock
    m_dock_affichage_notes->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    m_listeNotes = new QListWidget(m_dock_affichage_notes);     //nouvelle liste qui contiendra les notes crées au fur et à mesure
        m_listeNotes->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(m_listeNotes,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(menuContextuel(QPoint)));
        connect(m_listeNotes,SIGNAL(currentTextChanged(QString)),this,SLOT(affichage_single_note(QString)));


    m_dock_affichage_notes->setWidget(m_listeNotes);
    addDockWidget(Qt::LeftDockWidgetArea, m_dock_affichage_notes);

    ///2e dock
/*
    dock = new QDockWidget(tr("Paragraphs"), this);
    QListWidget* paragraphsList = new QListWidget(dock);
    paragraphsList->addItems(QStringList()
            << "Thank you for your payment which we have received today."
            << "Your order has been dispatched and should be with you "
               "within 28 days.";

    dock->setWidget(paragraphsList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    */

}

void FenPrincipale::creation_tabs()
{
    // 1 : Créer le QTabWidget
    m_onglets = new QTabWidget(this);

    // 2 : Créer les pages
    m_page_affichage_note = new QWidget;
    m_page_affichage_relations = new QWidget;

    // 3 : Créer le contenu des pages de widgets

        // Page affichage note
        m_layout_onglet_affichage = new QVBoxLayout;
        m_label_ID_note = nullptr;
        m_page_affichage_note->setLayout(m_layout_onglet_affichage);

        // Page 2

        QProgressBar *progress = new QProgressBar;
        progress->setValue(50);
        QSlider *slider = new QSlider(Qt::Horizontal);
        QPushButton *bouton3 = new QPushButton("Valider");

        QVBoxLayout *vbox2 = new QVBoxLayout;
        vbox2->addWidget(progress);
        vbox2->addWidget(slider);
        vbox2->addWidget(bouton3);

        m_page_affichage_relations->setLayout(vbox2);


    // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
    m_onglets->addTab(m_page_affichage_note, "Affichage d'une note");
    m_onglets->addTab(m_page_affichage_relations, "Affichage des relations");
}

///ATTENTION, à chaque ajout de note, le dock de gauche supprime la liste et la réaffiche pour l'actualiser avec les nouveaux,
/// ça va peut être causer des bugs plus tard
/// mais c'est la seule solution que j'ai trouvé pour l'instant
void FenPrincipale::affichage_notes()
{
    NotesManager2& m1 = NotesManager2::getManager();
    m_listeNotes->clear();
    for(NotesManager2::ConstIterator it= m1.getIterator(); !it.isDone(); it.next())
    {
        m_listeNotes->addItem(QString::fromStdString(it.current().getID()));
            //it.current().afficher();
    }
}

void FenPrincipale::affichage_single_note(QString texte)
{
    //NotesManager2& m1 = NotesManager2::getManager();
    if (m_label_ID_note == nullptr)
    {
        m_label_ID_note = new QLabel("texte");



        //QLabel* titre_note = new QLabel(QString::fromStdString(it.current().getTitre()));
        m_layout_onglet_affichage->addWidget(m_label_ID_note);
        //m_layout_onglet_affichage->addWidget(titre_note);
    }
/*
    NotesManager2::ConstIterator it= m1.getIterator();

    while (!it.isDone() && QString::fromStdString(it.current().getID())!=texte)
    {
        it.next();
    }
    it.current().afficher();
*/
    ///à voir quand y'aura un bon searchiterator
    m_label_ID_note->setText(texte);


}

void FenPrincipale::supprimerNote()
{
    NotesManager2& m1 = NotesManager2::getManager();
    // If multiple selection is on, we need to erase all selected items
    for (int i = 0; i < m_listeNotes->selectedItems().size(); ++i)
    {
       // Get curent item on selected row
       QListWidgetItem *item = m_listeNotes->takeItem(m_listeNotes->currentRow());
       delete &(m1.getNote(item->text().toStdString()));
       delete item;
    }
}

void FenPrincipale::menuContextuel(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = m_listeNotes->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("Supprimer", this, SLOT(supprimerNote()));

    // Show context menu at handling position
    myMenu.exec(globalPos);
}


void fenetre_creation_note :: choisir_fichier()
{
    m_fichier = new QString("");
    *m_fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg *.avi *.mp4)");
}

void fenetre_creation_note :: save() //Sauvegarde d'une note en tant qu'objet
{
    NotesManager2& m1 = NotesManager2::getManager();

    //à faire : gérer cas ou il n'y a pas d'échéance/pas de fichier selectionné

    try{

        ///faudrait faire un Design pattern sur l'ajout d'une note pour éviter d'avoir 3 fonctions
    if (m_article->isChecked())
    {
        m1.ajArticle(m_id->text().toStdString(),m_texte->toPlainText().toStdString()).setTitre(m_titre->text().toStdString());
    }
    if (m_tache->isChecked())
    {
        m1.ajTache(m_id->text().toStdString(),m_texte->toPlainText().toStdString(),m_priorite->value(),m_calendrier->selectedDate().toString("dddd dd MMMM yyyy").toStdString()).setTitre(m_titre->text().toStdString());
    }
    if (m_media->isChecked())
    {
        m1.ajMulti(m_id->text().toStdString(),m_texte->toPlainText().toStdString(),m_fichier->toStdString()).setTitre(m_titre->text().toStdString());
    }

    } catch (NotesException& a)
    {
        std::cout<< "Erreur lors de la creation de la note (fenetre_creation_note->save() )\n";
    }

    this->close();
    delete this; //forcer la destruction pour que le signal soit bien reçu par la FenPrincipale
}

void FenPrincipale :: popup()   //affichage de la fenetre de création de note
{
    m_fenetre_creation = new fenetre_creation_note; //On crée une nouvelle fenetre de creation de note, et l'adresse est stockée dans m_fenetre_creation
    connect(m_fenetre_creation,SIGNAL(destroyed(QObject*)),this,SLOT(affichage_notes())); //on connecte la destruction de la fenetre de creation à l'affichage des notes
    m_fenetre_creation->show();
}


