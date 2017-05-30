#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QApplication>
#include <QtWidgets>
#include <iostream>

/* *********** FENETRE PRINCIPALE ************* */

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

public:

    FenPrincipale();

private slots:
    void popup();
    void affichage_notes();
    void affichage_single_note(QString texte);
    void menuContextuel(const QPoint&);
    void supprimerNote();

private:
    void creation_docks(); //Création du dock de gauche, et affichage des notes
    void creation_tabs(); //Création des différents onglets de la vue principale

    QToolBar* m_toolbar; //barre d'outils

    QVBoxLayout* m_layout_principal; //layout pour les objets de la vue principale (au centre)


    QDockWidget *m_dock_affichage_notes;
        QListWidget* m_listeNotes;

    QWidget* m_fenetre_creation; //attribut vers la fenetre de création de note

    //onglets
    QTabWidget *m_onglets;
        QWidget* m_page_affichage_note;
            QVBoxLayout* m_layout_onglet_affichage;
                QLabel* m_label_ID_note;
        QWidget* m_page_affichage_relations;



};

/* ********** FENETRE DE CREATION DE NOTE ************* */
class fenetre_creation_note : public QWidget
{
    Q_OBJECT

public:
    fenetre_creation_note();

public slots:
    void choisir_fichier();
    void save();

private:
    QVBoxLayout* m_layout_choix;
    QLineEdit* m_id;
    QLineEdit* m_titre;
    QDateTime m_date_creat, m_date_modif;
    QLabel *m_label_date_creat, *m_label_date_modif;
    QRadioButton *m_article, *m_tache, *m_media;
    QTextEdit* m_texte;

    ///objets qui peuvent être affichés ou non selon la case cochée
    QPushButton* m_selection_fichier;
    QString* m_fichier;
    QSpinBox* m_priorite;

    QVBoxLayout* m_layout_tache;
    QWidget* m_groupe_tache;
    QCalendarWidget* m_calendrier;
        QCheckBox* m_case_calendrier;

    //Boutons de fin
    QPushButton* m_save;
    QPushButton* m_quit;

};


#endif // FENPRINCIPALE_H
