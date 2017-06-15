#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "relations.h"

/* *********** FENETRE PRINCIPALE ************* */

class fenetre_anciennes_versions;

/// Classe Fenetre principale
/** Cette fenêtre va servir à visualiser tous les différents objets : liste des notes, liste des taches selon leur priorité,
 * liste des relations. Elle contient aussi un Widget central contenant trois onglets. Ce widget central permet l'affichage de l'arborescence,
 * ou de la note/relation sélectionnée dans le dock adéquat.
 *
 */
class fenetre_creation_relation;

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

protected:
    /// fonction qui initialise les docks, et réalise les connexions nécéssaires aux affichages, ainsi qu'au menu contextuel.
    void creation_docks();
    /// fonction qui initialise les onglets et leurs layouts
    void creation_tabs();

    QToolBar* m_toolbar; //barre d'outils

    QVBoxLayout* m_layout_principal; //layout pour les objets de la vue principale (au centre)


    QDockWidget *m_dock_affichage_notes;
        QListWidget* m_listeNotes;
    QDockWidget* m_dock_affichage_relations;
        QListWidget* m_listeRelatons;
    QDockWidget* m_dock_affichage_taches;
        QListWidget* m_liste_taches;

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
            QLabel* m_titre_relation;
            QLabel* m_description_relation;
            QListWidget* m_liste_couples;
        QWidget* m_page_arborescence;
            QVBoxLayout* m_layout_onglet_arborescence;
            QListWidget* liste_ascendants;
            QListWidget* liste_descendants;
            QLabel* m_label_arborescence;

public:

    ///Initialise tous les widgets de la fenetre principale. Fait appel à creation_docks et creation_tabs.
    FenPrincipale();
    ///Retourne l'id de la note actuellement sélectionnée dans le dock.
    const std::string getCurrentNote() const {return m_listeNotes->currentItem()->text().toStdString();}
    ///Retourne le titre de la relation actuellement sélectionnée dans le dock.
    const std::string getCurrentRelation() const {return m_listeRelatons->currentItem()->text().toStdString();}

public slots:
    ///Affiche la fenetre modale de création de note
    void popup();
    ///Affiche une fenetre modale qui contient la liste des versions de la note sélectionnée, permet d'en restaurer une.
    void popupAnciennesVersions();
    ///Affiche la fenetre modale de création de relation
    void popupCreationRelation();
    ///Remplit les différents docks avec les objets du manager
    void affichage_notes_relations();
    ///Affiche au centre de la fenetre, la note sélectionnée dans le dock
    /**
    * @param id : identifiant de la note, transmis via des signaux
    * @param date : date correspondante à la version recherchée. Si la date est non renseignée, c'est la note active qui est recherchée.
    */
    void affichage_single_note(QString id, QString date="");
    ///Affiche la relation sélectionnée dans son dock
    /**
     * @param titre : titre de la relation recherchée, envoyé via un signal depuis un dock
     */
    void affichage_single_relation(QString titre);

    ///Menu contextuel personnalisé permettant des opérations d'édition, de suppression ou de restauration d'ancienne version sur une note
    void menuContextuel(const QPoint&);
    ///Menu contextuel personnalisé permettant des opérations d'édition ou de suppression sur une relation
    void menuContextuel2(const QPoint&);
    ///Supprime la note sélectionnée dans son dock
    void supprimerNote();
    ///Supprime la relation sélectionnée dans son dock
    void supprimerRelation();
    ///Appelle la fenetre de création de note, mais en mode "edition" : l'id et le type ne sont plus modifiables
    void editerNote();
    ///Appelle la fenetre de création de relation, en mode édition: le titre n'est plus modifiable.
    void editerRelation();
    ///Crée tous les objets contenus dans le xml "sauvegarde.xml"
    void load_xml();
    ///Affiche les ascendants et descendants d'une note
    /**
     * @param id : identifiant de la note, transmis via un signal
     */
    void affichage_arborescence(QString id);


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


/* ********** FENETRE DE CREATION DE RELATION ********* */
class fenetre_creation_relation : public QWidget
{
    Q_OBJECT

private:

    QWidget* m_parent;
    QListWidget* m_notes_gauche;
    QListWidget* m_notes_droite;
    QListWidget* m_liste_couples;
    QLineEdit* m_label_couple;
    QCheckBox* m_orientation;
    QLineEdit* m_label_relation;
    QTextEdit* m_description_relation;
    QGridLayout* m_layout;

    std::vector<Couple*> m_couples;

public:
    fenetre_creation_relation(QWidget *parent);
    std::vector<Couple*> getCouples() {return m_couples;}
    void lock_id_relation(std::string titre) {
        m_label_relation->setText(QString::fromStdString(titre));
        m_label_relation->setDisabled(true);}

public slots:
    void affichage_couples();
    void save_couple();
    void save_relation();



};


#endif // FENPRINCIPALE_H
