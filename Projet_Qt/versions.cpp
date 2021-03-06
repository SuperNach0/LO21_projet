#include "fenetres.h"
#include "notes.h"
#include "versions.h"
#include "manager.h"


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
        m_restaurer->connect(m_restaurer,SIGNAL(clicked(bool)),this,SLOT(restaurer()));
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


void FenPrincipale::editerNote()
{
    NotesManager2& m1 = NotesManager2::getManager();
    note& note_a_editer = m1.getNote(m_listeNotes->currentItem()->text().toStdString());

    m_fenetre_creation = new fenetre_creation_note; //On crée une nouvelle fenetre de creation de note, et l'adresse est stockée dans m_fenetre_creation
    connect(m_fenetre_creation,SIGNAL(destroyed(QObject*)),this,SLOT(affichage_notes_relations())); //on connecte la destruction de la fenetre de creation à l'affichage des notes
    m_fenetre_creation->show();
    fenetre_creation_note* fenetre = static_cast<fenetre_creation_note*>(m_fenetre_creation); //conversion de QWidget* vers fenetre_creation_note*
    fenetre->m_id->setDisabled(true); //on ne peut pas changer d'ID


    if (typeid(note_a_editer) == typeid(article))
    {
        fenetre->m_article->setChecked(true); //on coche la bonne case
    }
    else if (typeid(note_a_editer) == typeid(tache))
    {
        fenetre->m_tache->setChecked(true); //on coche la bonne case
        tache& current = static_cast<tache&>(note_a_editer); //on caste la note pour pouvoir accéder aux attributs des classes filles

        fenetre->m_priorite->setValue(current.getPriorite());
        if (current.getecheance()!="")
        {
            fenetre->m_case_calendrier->setChecked(true);
            //afficher sur le calendrier la date d'échéance
        }


    }
    else if (typeid(note_a_editer) == typeid(media))
    {
        fenetre->m_media->setChecked(true);
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

void fenetre_anciennes_versions::choix_ancienne_version(QString date)
{
    FenPrincipale* fenetre_parente = static_cast<FenPrincipale*>(m_parent); //on caste le parent pour accéder à ses méthodes
    std::cout << "id = " << fenetre_parente->getCurrentNote() << "date = " << date.toStdString() << std::endl;
    fenetre_parente->affichage_single_note(QString::fromStdString(fenetre_parente->getCurrentNote()), date);
}

void fenetre_anciennes_versions::restaurer()
{
    FenPrincipale* fenetre_parente = static_cast<FenPrincipale*>(m_parent); //on caste le parent pour accéder à ses méthodes
    std::string date = m_listeNotes->currentItem()->text().toStdString(); //on récupère la date de la version sélectionnée

    NotesManager2& nm = NotesManager2::getManager();
    note& ancienne_version = nm.getNote(fenetre_parente->getCurrentNote(),date); //on récupère une référence vers la version que l'on veut restaurer
    nm.SupprimerNote(nm.getNote(ancienne_version.getID())); //on supprime la note dont on veut restaurer une ancienne version
    nm.add(ancienne_version); //on ajoute l'ancienne version que l'on voulait restaurer

    this->close();

}

void FenPrincipale::editerRelation()
{
    std::cout << "Edition relation\n";
    m_fenetre_creation_relation = new fenetre_creation_relation(this);

    fenetre_creation_relation* fenetre = static_cast<fenetre_creation_relation*>(m_fenetre_creation_relation);
    m_fenetre_creation_relation->show();
    fenetre->lock_id_relation(getCurrentRelation());
}

void FenPrincipale::supprimerRelation()
{
    std::cout<< "Suppression Relation\n";
    /*
    RelationManager& rm = RelationManager::getManager();
    Relation& toDelete = rm.getRelation(this->getCurrentRelation());

    int i=0;
    while (i<rm.getobjets().size() && rm.getobjets()[i]->getTitre()==toDelete.getTitre())
    {
        i++;
    }
    if (i == rm.getobjets().size())
        throw NotesException("La relation a supprimer n'existe pas\n");
    rm.getobjets().erase(rm.getobjets().begin()+i);
    */ //A FINIR

}
