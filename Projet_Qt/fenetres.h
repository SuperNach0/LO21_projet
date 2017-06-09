#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "relations.h"

/* *********** FENETRE PRINCIPALE ************* */

class fenetre_anciennes_versions;
class fenetre_creation_relation;

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

protected:
    void creation_docks(); //Création du dock de gauche, et affichage des notes
    void creation_tabs(); //Création des différents onglets de la vue principale

    QToolBar* m_toolbar; //barre d'outils

    QVBoxLayout* m_layout_principal; //layout pour les objets de la vue principale (au centre)


    QDockWidget *m_dock_affichage_notes;
        QListWidget* m_listeNotes;
    QDockWidget* m_dock_affichage_relations;
        QListWidget* m_listeRelatons;

    QWidget* m_fenetre_creation; //attribut vers la fenetre de création de note
    fenetre_anciennes_versions* m_fenetre_ancienne_versions;
    //fenetre_creation_relation* m_fenetre_creation_relation;
    QWidget* m_fenetre_creation_relation;


    //onglets
    QTabWidget *m_onglets;
        QWidget* m_page_affichage_note;
            QVBoxLayout* m_layout_onglet_affichage;
                QLabel* m_label_ID_note;
                QLabel* m_titre_note;
                QLabel* m_date_creation_note;
                QLabel* m_date_modif_note;
                QLabel* m_texte_note;
                QLabel* m_echeance_note;
                QLabel* m_statut_note;
                QLabel* m_chemin_note;
                QLabel* m_priorite_note;
        QWidget* m_page_affichage_relations;

public:

    FenPrincipale();
    const std::string getCurrentNote() {return m_listeNotes->currentItem()->text().toStdString();}

public slots:
    void popup();
    void popupAnciennesVersions();
    void popupCreationRelation();
    void affichage_notes_relations();
    void affichage_single_note(QString id, QString date="");
    void menuContextuel(const QPoint&);
    void supprimerNote();
    void editerNote();
    void load_xml();


};

/* ********** FENETRE DE CREATION DE NOTE ************* */
class fenetre_creation_note : public QWidget
{
    Q_OBJECT
    friend FenPrincipale;
public:
    fenetre_creation_note();

public slots:
    void choisir_fichier();
    void save();

protected:
    QVBoxLayout* m_layout_choix;
    QLineEdit* m_id;
    QLineEdit* m_titre;
    QDateTime m_date_creat, m_date_modif;
    QLabel *m_label_date_creat, *m_label_date_modif;
    QRadioButton *m_article, *m_tache, *m_media;
    QTextEdit* m_texte;

    ///objets qui peuvent être affichés ou non selon la case cochée
    QVBoxLayout* m_layout_tache;
    QSpinBox* m_priorite;
    QComboBox* m_statut;
    QWidget* m_groupe_tache;
    QCalendarWidget* m_calendrier;
        QCheckBox* m_case_calendrier;

    QPushButton* m_selection_fichier;
    QString* m_fichier;

    //Boutons de fin
    QPushButton* m_save;
    QPushButton* m_quit;

};

class fenetre_creation_relation : public QWidget
{
    Q_OBJECT

public:
    fenetre_creation_relation(QWidget *parent);

public slots:
    void affichage_couples();
    void save_couple();
    void save_relation();

private:
    bool is_oriented;
    QWidget* m_parent;
    QListWidget* m_notes_gauche;
    QListWidget* m_notes_droite;
    QListWidget* m_liste_couples;
    QLineEdit* m_label_couple;
    QCheckBox* m_orientation;
    QLineEdit* m_label_relation;
    QTextEdit* m_description_relation;
    QGridLayout* m_layout;

    std::vector<Couple> couples;

};


#endif // FENPRINCIPALE_H
