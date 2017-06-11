#include "fenetres.h"
#include "notes.h"
#include "versions.h"
#include "relations.h"
#include "manager.h"


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

void fenetre_creation_note :: choisir_fichier()
{
    *m_fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg *.avi *.mp4)");
}


void fenetre_creation_note :: save() //Sauvegarde/modification d'une note en tant qu'objet
{
    NotesManager& m1 = NotesManager::getManager();

    //à faire : gérer cas ou il n'y pas de fichier selectionné

    std::string erreur ="";
    try
    {
        m1.getNote(m_id->text().toStdString());
    }
    catch (NotesException& excep)
    {
        erreur = excep.getInfo();
    }

    if (erreur=="") ///Si la note existe déjà
    {
        note& note_modif = m1.getNote(m_id->text().toStdString()); //On récupère une référence vers la note à modifier

        if (typeid(note_modif) == typeid(article))
        {

            article& current = static_cast<article&>(note_modif);
            std::cout << "pass\n";
            article* article_nouv = new article(current);    //on copie la note à modifier
            note_modif.getOldNotes().push_back(article_nouv); //on ajoute la copie dans les anciennes versions
            //on fait les modifs : pas de modif pour un article


        }
        else if (typeid(note_modif) == typeid(tache))
        {
            tache& current = static_cast<tache&>(note_modif);

            tache* tache_nouv = new tache(current);    //on copie la note à modifier

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
            media* media_nouv = new media(current);    //on copie la note à modifier via constructeur de copie
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
        if (m_article->isChecked())
        {
            article* nouveau = new article(m_id->text().toStdString(),m_titre->text().toStdString(),m_texte->toPlainText().toStdString());
            m1.addNote(*nouveau);
        }
        if (m_tache->isChecked())
        {
            QString date = m_calendrier->selectedDate().toString("dddd dd MMMM yyyy");
            if (!m_case_calendrier->isChecked())    //si pas d'échéance
                date = "";
            tache* nouveau = new tache(m_id->text().toStdString(),m_titre->text().toStdString(),m_texte->toPlainText().toStdString(),m_priorite->value(),date.toStdString(),(etat)m_statut->currentIndex());
            m1.addNote(*nouveau);
        }
        if (m_media->isChecked())
        {
            media* nouveau = new media(m_id->text().toStdString(),m_titre->text().toStdString(),m_texte->toPlainText().toStdString(),m_fichier->toStdString());
            m1.addNote(*nouveau);
        }

        } catch (NotesException& a)
        {
            std::cout<< "Erreur lors de la creation de la note, ID déjà utilise? (fenetre_creation_note->save() )\n";
            std::cout << a.getInfo();
        }
    }
    this->close();
    delete this; //forcer la destruction pour que le signal soit bien reçu par la FenPrincipale
}
