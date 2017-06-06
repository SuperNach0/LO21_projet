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

        m_statut = new QComboBox(this);
            m_statut->addItem("En attente");
            m_statut->addItem("En cours");
            m_statut->addItem("Terminée");

        QLabel* label_spinbox = new QLabel("Priorité, 0 si aucune priorité",this);
        m_priorite = new QSpinBox(this);
        m_case_calendrier = new QCheckBox("Echeance",this);
            m_calendrier = new QCalendarWidget(this);
            m_calendrier->setVisible(false);
            m_case_calendrier->connect(m_case_calendrier,SIGNAL(toggled(bool)),m_calendrier,SLOT(setVisible(bool)));

    m_media = new QRadioButton("Media",this);
        m_selection_fichier = new QPushButton("Parcourir...",this);
        m_fichier = new QString("");
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
    m_layout_tache->addWidget(m_statut);
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

void FenPrincipale::affichage_single_note(QString id)
{
    NotesManager2& m1 = NotesManager2::getManager();
    note& note_affichee = m1.getNote(id.toStdString()); //on récupère une référence sur la note à afficher

    if (m_label_ID_note == nullptr) //si c'est la première fois qu'on affiche une note, on crée les labels (et on les ajoute au layout)
    {
        m_label_ID_note = new QLabel("texte");
        m_titre_note = new QLabel(QString::fromStdString(note_affichee.getTitre()));
        m_date_creation_note = new QLabel(QString::fromStdString(note_affichee.getCreation()));
        m_date_modif_note = new QLabel(QString::fromStdString(note_affichee.getModif()));
        m_texte_note = new QLabel("");
        m_priorite_note = new QLabel("");
        m_echeance_note = new QLabel("");
        m_statut_note = new QLabel("");
        m_chemin_note = new QLabel("");


        m_layout_onglet_affichage->addWidget(m_label_ID_note);
        m_layout_onglet_affichage->addWidget(m_titre_note);
        m_layout_onglet_affichage->addWidget(m_date_creation_note);
        m_layout_onglet_affichage->addWidget(m_date_modif_note);
        m_layout_onglet_affichage->addWidget(m_texte_note);
        m_layout_onglet_affichage->addWidget(m_priorite_note);
        m_layout_onglet_affichage->addWidget(m_echeance_note);
        m_layout_onglet_affichage->addWidget(m_statut_note);
        m_layout_onglet_affichage->addWidget(m_chemin_note);
    }
    else //entre 2 affichages (donc après un premier affichage), on cache les champs qui ne sont pas concernés à cause du type de la note
    {
        m_echeance_note->setHidden(true);
        m_priorite_note->setHidden(true);
        m_statut_note->setHidden(true);
        m_chemin_note->setHidden(true);
    }


    if (id.toStdString() != "")
    {
        m_label_ID_note->setText("<b> ID : </b>"+id);
        QString titre = QString::fromStdString(note_affichee.getTitre());
        m_titre_note->setText("<b>Titre : </b>"+titre);
        QString texte = QString::fromStdString(note_affichee.getTexte());
        m_texte_note->setText("<b>Description : </b>"+texte);
        QString date_creation = QString::fromStdString(note_affichee.getCreation());
        m_date_creation_note->setText("<b>Création le : </b>"+ date_creation);
        QString date_modification = QString::fromStdString(note_affichee.getModif());
        m_date_modif_note->setText("<b>Dernière modification le : </b>"+date_modification);

        if (typeid(note_affichee) == typeid(article))
        {
            article& current = static_cast<article&>(note_affichee); //on convertit la note dans le type correspondant pour récupérer les attributs des sous classes


        }
        else if (typeid(note_affichee) == typeid(tache))
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

void FenPrincipale::editerNote()
{
    NotesManager2& m1 = NotesManager2::getManager();
    note& note_a_editer = m1.getNote(m_listeNotes->currentItem()->text().toStdString());

    m_fenetre_creation = new fenetre_creation_note; //On crée une nouvelle fenetre de creation de note, et l'adresse est stockée dans m_fenetre_creation
    connect(m_fenetre_creation,SIGNAL(destroyed(QObject*)),this,SLOT(affichage_notes())); //on connecte la destruction de la fenetre de creation à l'affichage des notes
    m_fenetre_creation->show();
    fenetre_creation_note* fenetre = static_cast<fenetre_creation_note*>(m_fenetre_creation); //conversion de QWidget* vers fenetre_creation_note*
    fenetre->m_id->setDisabled(true); //on ne peut pas changer d'ID


    if (typeid(note_a_editer) == typeid(article))
    {
        fenetre->m_article->setChecked(true); //on coche la bonne case
        //article& current = static_cast<article&>(note_a_editer); //on caste la note pour pouvoir accéder aux attributs des classes filles
    }
    else if (typeid(note_a_editer) == typeid(tache))
    {
        fenetre->m_tache->setChecked(true);
        tache& current = static_cast<tache&>(note_a_editer); //on caste la note pour pouvoir accéder aux attributs des classes filles

        fenetre->m_priorite->setValue(current.getPriorite());
        if (current.getecheance()!="")
        {
            fenetre->m_case_calendrier->setChecked(true);
            ///afficher sur le calendrier la date d'échéance
        }


    }
    else if (typeid(note_a_editer) == typeid(media))
    {
        fenetre->m_media->setChecked(true);
        media& current = static_cast<media&>(note_a_editer);

    }
    else
        throw NotesException("Erreur, type inconnu!");

    fenetre->m_id->setText(QString::fromStdString(note_a_editer.getID()));
    fenetre->m_titre->setText(QString::fromStdString(note_a_editer.getTitre()));
    fenetre->m_texte->setText(QString::fromStdString(note_a_editer.getTexte()));
    fenetre->m_date_modif.setDate(QDate::currentDate());


    fenetre->m_article->setDisabled(true);
    fenetre->m_tache->setDisabled(true);
    fenetre->m_media->setDisabled(true);

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

void fenetre_creation_note :: choisir_fichier()
{
    *m_fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg *.avi *.mp4)");
}

void fenetre_creation_note :: save() //Sauvegarde/modification d'une note en tant qu'objet
{
    NotesManager2& m1 = NotesManager2::getManager();

    //à faire : gérer cas ou il n'y pas de fichier selectionné

    ///Si la note existe déjà
    if (m1.getNote(m_id->text().toStdString()).getID()!="") //si la note n'existe pas, m1.getNote(...) renvoie un article avec un id vide
    {
        note& note_modif = m1.getNote(m_id->text().toStdString()); //On récupère une référence vers la note à modifier

        if (typeid(note_modif) == typeid(article))
        {
            article& current = static_cast<article&>(note_modif);
            article* article_nouv = new article(current);    //on copie la note à modifier
            note_modif.getOldNotes().push_back(article_nouv); //on ajoute la copie dans les anciennes versions

            //on fait les modifs : pas de modif pour un article


        }
        else if (typeid(note_modif) == typeid(tache))
        {
            tache& current = static_cast<tache&>(note_modif);
            tache* tache_nouv(&current);    //on copie la note à modifier
            note_modif.getOldNotes().push_back(tache_nouv); //on ajoute la copie dans les anciennes version
            //on fait les modifs : echeance, priorité

            QString date = m_calendrier->selectedDate().toString("dddd dd MMMM yyyy");
            if (!m_case_calendrier->isChecked())    //si pas d'échéance
                date = "";
            current.setPriorite(m_priorite->value());
            current.setEcheance(date.toStdString());
            current.setStatus((etat)m_statut->currentIndex());

        }
        else if (typeid(note_modif) == typeid(media))
        {
            media& current = static_cast<media&>(note_modif);
            media* media_nouv(&current);    //on copie la note à modifier
            note_modif.getOldNotes().push_back(media_nouv); //on ajoute la copie dans les anciennes versions

            current.setChemin(m_fichier->toStdString());
        }

        //Modifications qui ne dépendent pas du type de note
        note_modif.setTitre(m_titre->text().toStdString());
        note_modif.setTexte(m_texte->toPlainText().toStdString());
        note_modif.setModif();
    }
    else    ///SI la note n'existe pas
    {
        try{
            ///faudrait faire un Design pattern sur l'ajout d'une note pour éviter d'avoir 3 fonctions
        if (m_article->isChecked())
        {
            m1.ajArticle(m_id->text().toStdString(),m_texte->toPlainText().toStdString()).setTitre(m_titre->text().toStdString());
        }
        if (m_tache->isChecked())
        {
            QString date = m_calendrier->selectedDate().toString("dddd dd MMMM yyyy");
            if (!m_case_calendrier->isChecked())    //si pas d'échéance
                date = "";
            m1.ajTache(m_id->text().toStdString(),m_texte->toPlainText().toStdString(),m_priorite->value(),date.toStdString(),(etat)m_statut->currentIndex()).setTitre(m_titre->text().toStdString());
        }
        if (m_media->isChecked())
        {
            m1.ajMulti(m_id->text().toStdString(),m_texte->toPlainText().toStdString(),m_fichier->toStdString()).setTitre(m_titre->text().toStdString());
        }

        } catch (NotesException& a)
        {
            std::cout<< "Erreur lors de la creation de la note, ID déjà utilise? (fenetre_creation_note->save() )\n";
        }
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

void FenPrincipale::popupAnciennesVersions()
{
    m_fenetre_ancienne_versions = new fenetre_anciennes_versions;
    connect(m_fenetre_ancienne_versions,SIGNAL(destroyed(QObject*)),this,SLOT(affichage_notes()));
    m_fenetre_ancienne_versions->show();
}

fenetre_anciennes_versions::fenetre_anciennes_versions()
{
    this->setWindowModality(Qt::ApplicationModal); //pour que la fenetre parente ne soit pas utilisable quand celle ci est ouverte

    NotesManager2& m1 = NotesManager2::getManager();
    //note& current = m1.getNote(m_listeNotes->currentItem()->text().toStdString());
/*
    for (unsigned int i=0;i<current.getOldNotes().size();i++)
    {
        current.getOldNotes()[i]->afficher();
    }
*/
    m_layout_choix = new QVBoxLayout; //création layout
    //Création des différents champs du formulaire
    m_restaurer = new QPushButton("Restaurer",this);
        //m_save->connect(m_save,SIGNAL(clicked(bool)),this,SLOT(save()));
    m_quit = new QPushButton("Quitter",this);
        m_quit->connect(m_quit,SIGNAL(clicked(bool)),this,SLOT(close()));



    //Ajout des objets au layout

    m_layout_choix->addWidget(m_restaurer);
    m_layout_choix->addWidget(m_quit);


    this->setLayout(m_layout_choix); //affectation du layout
    this->move(100,100); //décalage de la nouvelle fenetre par rapport à la première
}
