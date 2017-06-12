#include "fenetres.h"
#include "notes.h"
#include "versions.h"
#include "relations.h"
#include "manager.h"



FenPrincipale::FenPrincipale()
{
    ///LAYOUT PRINCIPAL
    m_layout_principal = new QVBoxLayout;


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
        QAction *actionLoadXml = new QAction("&Charger un xml",this);
            actionLoadXml->setShortcut(QKeySequence("Ctrl+L"));
            connect(actionLoadXml,SIGNAL(triggered(bool)),this,SLOT(load_xml()));

        menuFichier->addAction(actionQuitter);
        menuFichier->addAction(actionNewNote);
        menuFichier->addAction(actionNewLink);
        menuFichier->addAction(actionLoadXml);


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


    m_dock_affichage_notes->setWidget(m_listeNotes);
    addDockWidget(Qt::LeftDockWidgetArea, m_dock_affichage_notes);

    ///2e dock
    m_dock_affichage_relations = new QDockWidget("Relations",this);
    m_dock_affichage_relations->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    m_listeRelatons = new QListWidget(m_dock_affichage_relations);
        connect(m_listeRelatons,SIGNAL(currentTextChanged(QString)),this,SLOT(affichage_single_relation(QString)));


    m_dock_affichage_relations->setWidget(m_listeRelatons);
    addDockWidget(Qt::RightDockWidgetArea, m_dock_affichage_relations);

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


    // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
    m_onglets->addTab(m_page_affichage_note, "Affichage d'une note");
    m_onglets->addTab(m_page_affichage_relations, "Affichage des relations");
}

///ATTENTION, à chaque ajout de note, le dock de gauche supprime la liste et la réaffiche pour l'actualiser avec les nouveaux,
/// ça va peut être causer des bugs plus tard
/// mais c'est la seule solution que j'ai trouvé pour l'instant
void FenPrincipale::affichage_notes_relations()
{
    NotesManager2& m1 = NotesManager2::getManager();
    m_listeNotes->clear();

    for (unsigned int i = 0; i<m1.gettype().size();i++)
    {
        m_listeNotes->addItem(QString::fromStdString(m1.gettype()[i]->getID()));
    }

    RelationManager& m2 = RelationManager::getManager();
    m_listeRelatons->clear();

    for (unsigned int i=0;i<m2.getRelations().size();i++)
    {
        m_listeRelatons->addItem(QString::fromStdString(m2.getRelations()[i]->getTitre()));
    }

}

void FenPrincipale::affichage_single_note(QString id, QString date)
{



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

    QString separateur = "<--->";

    for (unsigned int i=0;i<current.getCouples().size();i++)
    {
        if (current.getCouples()[i]->isOriented())
            separateur="--->";

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
    // If multiple selection is on, we need to erase all selected items
    for (int i = 0; i < m_listeNotes->selectedItems().size(); ++i)
    {
       // Get curent item on selected row
       QListWidgetItem *item = m_listeNotes->takeItem(m_listeNotes->currentRow());
       m1.SupprimerNote(m1.getNote(item->text().toStdString()));
    }
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
    QString filename = QFileDialog::getOpenFileName();
    m1.setFilename(filename);
    m1.load();
    this->affichage_notes_relations();
}


fenetre_anciennes_versions::fenetre_anciennes_versions(QWidget* parent)
{
    this->setWindowModality(Qt::ApplicationModal); //pour que la fenetre parente ne soit pas utilisable quand celle ci est ouverte
    NotesManager2& m1 = NotesManager2::getManager();
    m_parent = parent;
    FenPrincipale* fenetre_parente = static_cast<FenPrincipale*>(m_parent);
    note& current = m1.getNote(fenetre_parente->getCurrentNote());

    m_layout_choix = new QVBoxLayout; //création layout
    //Création des différents champs du formulaire
    m_restaurer = new QPushButton("Restaurer",this);
        //m_save->connect(m_save,SIGNAL(clicked(bool)),this,SLOT(save()));
    m_quit = new QPushButton("Quitter",this);
        m_quit->connect(m_quit,SIGNAL(clicked(bool)),this,SLOT(close()));
    m_listeNotes = new QListWidget(this);
        connect(m_listeNotes,SIGNAL(currentTextChanged(QString)),this,SLOT(choix_ancienne_version(QString)));


    for (unsigned int i=0;i<current.getOldNotes().size();i++)
    {
        m_listeNotes->addItem(QString::fromStdString(current.getOldNotes()[i]->getModif()));
    }

    //Ajout des objets au layout
    m_layout_choix->addWidget(new QLabel("<b>Modifié le :</b>"));
    m_layout_choix->addWidget(m_listeNotes);
    m_layout_choix->addWidget(m_restaurer);
    m_layout_choix->addWidget(m_quit);



    this->setLayout(m_layout_choix); //affectation du layout
    this->move(100,100); //décalage de la nouvelle fenetre par rapport à la première
}


