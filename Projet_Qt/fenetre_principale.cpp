#include "fenetres.h"
#include "notes.h"
#include "versions.h"
#include "relations.h"
#include "manager.h"



FenPrincipale::FenPrincipale()
{
    ///LAYOUT PRINCIPAL
    m_layout_principal = new QVBoxLayout;
    this->setWindowTitle("Plurinotes");

    //********* MENU FICHIER ***************

    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
        //ajout d'une action
        QAction *actionQuitter = new QAction("&Quitter", this);
            actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
            connect(actionQuitter,SIGNAL(triggered(bool)),this,SLOT(close()));
        QAction *actionNewNote = new QAction("&Nouvelle Note",this);
            actionNewNote->setShortcut(QKeySequence("Ctrl+N"));
            connect(actionNewNote,SIGNAL(triggered(bool)),this,SLOT(popup()));
        QAction *actionNewLink = new QAction("&Nouvelle Relation",this);
            actionNewLink->setShortcut(QKeySequence("Ctrl+R"));
            connect(actionNewLink,SIGNAL(triggered(bool)),this,SLOT(popupCreationRelation()));

        menuFichier->addAction(actionQuitter);
        menuFichier->addAction(actionNewNote);
        menuFichier->addAction(actionNewLink);



    //ajout d'un 2e menu
    QMenu *menuEdition = menuBar()->addMenu("&Edition");
        //ajout d'actions
            QAction* retablir = new QAction("Rétablir");
            menuEdition->addAction(retablir);

            QAction* annuler = new QAction("Annuler");
            menuEdition->addAction(annuler);

    //Barre d'outils
    m_toolbar = addToolBar("fichier");
        actionNewNote->setIcon(QIcon("icone_nouveau.png"));
        actionNewLink->setIcon(QIcon("icone_nouvelle_relation.png"));
        actionQuitter->setIcon(QIcon("icone_exit.png"));
        m_toolbar->addAction(actionNewNote);
        m_toolbar->addAction(actionNewLink);
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

    this->affichage_notes_relations(); //pour actualiser l'affichage dès le chargement de la fenetre (load)

}


void FenPrincipale::creation_docks()
{

    m_dock_affichage_notes = new QDockWidget("Notes", this);    //nouveau dock
    m_dock_affichage_notes->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    m_listeNotes = new QListWidget(m_dock_affichage_notes);     //nouvelle liste qui contiendra les notes crées au fur et à mesure
        m_listeNotes->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(m_listeNotes,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(menuContextuel(QPoint)));
        connect(m_listeNotes,SIGNAL(currentTextChanged(QString)),this,SLOT(affichage_single_note(QString)));
        connect(m_listeNotes,SIGNAL(currentTextChanged(QString)),this,SLOT(affichage_arborescence(QString)));


    m_dock_affichage_notes->setWidget(m_listeNotes);
    addDockWidget(Qt::LeftDockWidgetArea, m_dock_affichage_notes);

    ///2e dock
    m_dock_affichage_relations = new QDockWidget("Relations",this);
    m_dock_affichage_relations->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    m_listeRelatons = new QListWidget(m_dock_affichage_relations);
        m_listeRelatons->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(m_listeRelatons,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(menuContextuel2(QPoint)));
        connect(m_listeRelatons,SIGNAL(currentTextChanged(QString)),this,SLOT(affichage_single_relation(QString)));


    m_dock_affichage_relations->setWidget(m_listeRelatons);
    addDockWidget(Qt::RightDockWidgetArea, m_dock_affichage_relations);

    ///3e dock
    m_dock_affichage_taches = new QDockWidget("Tâches",this);
    m_dock_affichage_taches->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    m_liste_taches = new QListWidget(m_dock_affichage_taches);
        connect(m_liste_taches,SIGNAL(currentTextChanged(QString)),this,SLOT(affichage_single_note(QString)));
        connect(m_liste_taches,SIGNAL(currentTextChanged(QString)),this,SLOT(affichage_arborescence(QString)));


    m_dock_affichage_taches->setWidget(m_liste_taches);
    addDockWidget(Qt::LeftDockWidgetArea, m_dock_affichage_taches);




}

void FenPrincipale::creation_tabs()
{
    // 1 : Créer le QTabWidget
    m_onglets = new QTabWidget(this);

    // 2 : Créer les pages
    m_page_affichage_note = new QWidget;
    m_page_affichage_relations = new QWidget;
    m_page_arborescence = new QWidget;

    // 3 : Créer le contenu des pages de widgets

        // Page affichage note
        m_layout_onglet_affichage = new QVBoxLayout;
        m_label_ID_note = new QLabel("",this);
        m_titre_note = new QLabel("",this);
        m_date_creation_note = new QLabel("",this);
        m_date_modif_note = new QLabel("",this);
        m_texte_note = new QLabel("",this);
        m_priorite_note = new QLabel("",this);
        m_echeance_note = new QLabel("",this);
        m_statut_note = new QLabel("",this);
        m_chemin_note = new QLabel("",this);

        m_layout_onglet_affichage->addWidget(m_label_ID_note);
        m_layout_onglet_affichage->addWidget(m_titre_note);
        m_layout_onglet_affichage->addWidget(m_date_creation_note);
        m_layout_onglet_affichage->addWidget(m_date_modif_note);
        m_layout_onglet_affichage->addWidget(m_texte_note);
        m_layout_onglet_affichage->addWidget(m_priorite_note);
        m_layout_onglet_affichage->addWidget(m_echeance_note);
        m_layout_onglet_affichage->addWidget(m_statut_note);
        m_layout_onglet_affichage->addWidget(m_chemin_note);
        m_page_affichage_note->setLayout(m_layout_onglet_affichage);

        // Page affichage relations
        QVBoxLayout *layout_affichage_relations = new QVBoxLayout;
        m_titre_relation = new QLabel("",this);
        m_description_relation = new QLabel("",this);
        m_liste_couples = new QListWidget(this);
        layout_affichage_relations->addWidget(m_titre_relation);
        layout_affichage_relations->addWidget(m_description_relation);
        layout_affichage_relations->addWidget(m_liste_couples);

        m_page_affichage_relations->setLayout(layout_affichage_relations);

        // Page arborescence
        m_layout_onglet_arborescence = new QVBoxLayout;
        m_page_arborescence->setLayout(m_layout_onglet_arborescence);
        liste_ascendants = new QListWidget;
        liste_descendants = new QListWidget;
        m_label_arborescence = new QLabel("");

        m_layout_onglet_arborescence->addWidget(new QLabel("<b> Notes ascendantes </b>"));
        m_layout_onglet_arborescence->addWidget(liste_ascendants);
        m_layout_onglet_arborescence->addWidget(m_label_arborescence);
        m_layout_onglet_arborescence->addWidget(new QLabel("<b> Notes descendantes </b>"));
        m_layout_onglet_arborescence->addWidget(liste_descendants);



    // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
    m_onglets->addTab(m_page_affichage_note, "Affichage d'une note");
    m_onglets->addTab(m_page_affichage_relations, "Affichage des relations");
    m_onglets->addTab(m_page_arborescence,"Affichage d'une arborescence");
}


void FenPrincipale::affichage_notes_relations()
{
    NotesManager2& m1 = NotesManager2::getManager();
    m_listeNotes->clear();
    int min_priorite=99;

    for (unsigned int i = 0; i<m1.getobjets().size();i++) //affichage notes
    {
        m_listeNotes->addItem(QString::fromStdString(m1.getobjets()[i]->getID()));
    }

    m_liste_taches->clear();
    while (min_priorite>=0) //affichage selon priorité
    {
        for (unsigned int i = 0; i<m1.getobjets().size();i++) //affichage taches
        {
            if (typeid(*(m1.getobjets()[i]))==typeid(tache))//si c'est une tache, on la met dans le dock
            {
                tache& current = static_cast<tache&>(*(m1.getobjets()[i]));

                    if (current.getPriorite()==min_priorite)
                        m_liste_taches->addItem(QString::fromStdString(m1.getobjets()[i]->getID()));
            }
        }
        min_priorite--;
    }



    RelationManager& m2 = RelationManager::getManager();
    m_listeRelatons->clear();

    for (unsigned int i=0;i<m2.getobjets().size();i++)
    {
        m_listeRelatons->addItem(QString::fromStdString(m2.getobjets()[i]->getTitre()));
    }

}

void FenPrincipale::affichage_single_note(QString id, QString date)
{
    std::cout << "affichage_single_note\n";
    NotesManager2& m1 = NotesManager2::getManager();
    try
    {
        m1.getNote(id.toStdString(),date.toStdString());
    }
    catch (NotesException& excep)   //si la note n'existe pas, abort
    {
        std::cout << excep.getInfo();
        return;
    }


    note& note_affichee = m1.getNote(id.toStdString(),date.toStdString());

    //On cache les champs qui sont potentiellement non nécéssaires, en fonction du type de note
    m_echeance_note->setHidden(true);
    m_priorite_note->setHidden(true);
    m_statut_note->setHidden(true);
    m_chemin_note->setHidden(true);

    m_label_ID_note->setText("<b> ID : </b>"+id);
    QString titre = QString::fromStdString(note_affichee.getTitre());
    m_titre_note->setText("<b>Titre : </b>"+titre);
    QString texte = QString::fromStdString(note_affichee.getTexte());
    m_texte_note->setText("<b>Description : </b>"+texte);
    QString date_creation = QString::fromStdString(note_affichee.getCreation());
    m_date_creation_note->setText("<b>Création le : </b>"+ date_creation);
    QString date_modification = QString::fromStdString(note_affichee.getModif());
    m_date_modif_note->setText("<b>Dernière modification le : </b>"+date_modification);

    if (typeid(note_affichee) == typeid(tache))
    {
        tache& current = static_cast<tache&>(note_affichee);
        m_statut_note->setHidden(false);
        m_statut_note->setText("<b>Etat: </b>"+QString::fromStdString(etatToString(current.getEtat())));
        if (current.getPriorite()!=0)
        {
            m_priorite_note->setHidden(false);
            m_priorite_note->setText("<b>Priorité : </b>"+ QString::number(current.getPriorite()));
        }
        if (current.getecheance()!="")
        {
            m_echeance_note->setHidden(false);
            m_echeance_note->setText("<b>Expiration : </b>" + QString::fromStdString(current.getecheance()));
        }

    }
    else if (typeid(note_affichee) == typeid(media))
    {
        media& current = static_cast<media&>(note_affichee);
        m_chemin_note->setHidden(false);
        m_chemin_note->setText("<b>Chemin du fichier : </b>"+QString::fromStdString(current.getChemin()));
    }

}


//CHOIX A METTRE DANS LE RAPPORT : Une relation est caractérisée par son titre, pas 2 relations avec le même titre
void FenPrincipale::affichage_single_relation(QString titre)
{

    if (titre=="")
        return;
    RelationManager& m = RelationManager::getManager();
    Relation& current = m.getRelation(titre.toStdString());

    m_liste_couples->clear();

    m_titre_relation->setText("<b> Titre : </b>"+QString::fromStdString(current.getTitre()));
    m_description_relation->setText("<b> Description : </b>"+QString::fromStdString(current.getDescription()));

    for (unsigned int i=0;i<current.getCouples().size();i++)
    {
        QString separateur="<--->";
        if (current.getCouples()[i]->isOriented())
        {
            separateur="--->";
            std::cout << "note orientee\n";
        }


        m_liste_couples->addItem(QString::fromStdString(current.getCouples()[i]->getLabel())
                                 + " / "
                                 + QString::fromStdString(current.getCouples()[i]->getPremiere().getID())
                                 + separateur
                                 + QString::fromStdString(current.getCouples()[i]->getSeconde().getID())
                                 );
    }

}

void FenPrincipale::supprimerNote()
{
    NotesManager2& m1 = NotesManager2::getManager();

    for (int i = 0; i < m_listeNotes->selectedItems().size(); ++i)
    {
       // Get curent item on selected row
       QListWidgetItem *item = m_listeNotes->takeItem(m_listeNotes->currentRow());
       m1.SupprimerNote(m1.getNote(item->text().toStdString()));
    }
    affichage_arborescence("");
}


void FenPrincipale::menuContextuel(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = m_listeNotes->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("Editer",this,SLOT(editerNote()));
    myMenu.addAction("Anciennes versions",this,SLOT(popupAnciennesVersions()));
    myMenu.addAction("Supprimer", this, SLOT(supprimerNote()));

    // Show context menu at handling position
    myMenu.exec(globalPos);
}

void FenPrincipale::menuContextuel2(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = m_listeRelatons->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("Editer",this,SLOT(editerRelation()));
    myMenu.addAction("Supprimer",this,SLOT(supprimerRelation()));

    // Show context menu at handling position
    myMenu.exec(globalPos);
}



void FenPrincipale :: popup()   //affichage de la fenetre de création de note
{
    m_fenetre_creation = new fenetre_creation_note; //On crée une nouvelle fenetre de creation de note, et l'adresse est stockée dans m_fenetre_creation
    connect(m_fenetre_creation,SIGNAL(destroyed(QObject*)),this,SLOT(affichage_notes_relations())); //on connecte la destruction de la fenetre de creation à l'affichage des notes
    m_fenetre_creation->show();
}

void FenPrincipale::popupAnciennesVersions()
{
    m_fenetre_ancienne_versions = new fenetre_anciennes_versions(this);
    connect(m_fenetre_ancienne_versions,SIGNAL(destroyed(QObject*)),this,SLOT(affichage_notes_relations()));
    m_fenetre_ancienne_versions->show();
}

void FenPrincipale :: popupCreationRelation()
{
    m_fenetre_creation_relation = new fenetre_creation_relation(this);
    m_fenetre_creation_relation->show();
    connect(m_fenetre_creation_relation,SIGNAL(destroyed(QObject*)),this,SLOT(affichage_notes_relations())); //on connecte la destruction de la fenetre de creation à l'affichage des notes
}

void FenPrincipale :: load_xml()
{
    NotesManager2 &m1 = NotesManager2::getManager();
    RelationManager &m2 = RelationManager::getManager();
    QString filename = QFileDialog::getOpenFileName();
    m1.setFilename(filename);
    m2.setFilename(filename);
    m1.load();
    this->affichage_notes_relations();

}


void FenPrincipale::affichage_arborescence(QString id)
{
    NotesManager2& nm = NotesManager2::getManager();
    RelationManager& rm = RelationManager::getManager();

    if (id=="") //si aucune note n'est sélectionnée dans la fenetre principale
        return;
    note& note_a_afficher = nm.getNote(id.toStdString());
    m_label_arborescence->setText(QString::fromStdString(note_a_afficher.getID()));
            liste_ascendants->clear();
            liste_descendants->clear();


    for (unsigned int i=0;i<rm.getobjets().size();i++) //parcourt des relations
    {
        for (unsigned int j=0;j<rm.getobjets()[i]->getCouples().size();j++) //parcourt des couples de la relation
        {
            if (rm.getobjets()[i]->getCouples()[j]->getPremiere().getID()==note_a_afficher.getID())
            {
                liste_descendants->addItem(QString::fromStdString(rm.getobjets()[i]->getCouples()[j]->getSeconde().getID()));
            }
            if (rm.getobjets()[i]->getCouples()[j]->getSeconde().getID()==note_a_afficher.getID())
            {
                liste_ascendants->addItem(QString::fromStdString(rm.getobjets()[i]->getCouples()[j]->getPremiere().getID()));
            }
        }
    }


}
