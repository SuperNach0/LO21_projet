#include "fenetres.h"
#include "notes.h"
#include "versions.h"

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

void fenetre_anciennes_versions::choix_ancienne_version(QString date)
{
    FenPrincipale* fenetre_parente = static_cast<FenPrincipale*>(m_parent);
    std::cout << "id = " << fenetre_parente->getCurrentNote() << "date = " << date.toStdString() << std::endl;
    fenetre_parente->affichage_single_note(QString::fromStdString(fenetre_parente->getCurrentNote()), date);
}
