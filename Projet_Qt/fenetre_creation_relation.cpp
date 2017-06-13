#include "fenetres.h"
#include "notes.h"
#include "versions.h"
#include "relations.h"
#include "manager.h"

fenetre_creation_relation::fenetre_creation_relation(QWidget *parent):m_couples(0)
{
    this->setWindowModality(Qt::ApplicationModal); //pour que la fenetre parente ne soit pas utilisable quand celle ci est ouverte
    m_parent = parent;
    m_couples.clear(); //on reset les couples à chaque ajout de relation
    FenPrincipale* fenetre_parente = static_cast<FenPrincipale*>(m_parent); //on caste si l'on veut accéder aux attributs du parent


    m_layout = new QGridLayout(this); //création layout


    /************* Création des différents champs du formulaire *************/

    m_notes_gauche = new QListWidget(this);
    m_notes_droite = new QListWidget(this);
    m_liste_couples = new QListWidget(this);

    QPushButton* m_quit = new QPushButton("Quitter",this);
        m_quit->connect(m_quit,SIGNAL(clicked(bool)),this,SLOT(close()));
    QPushButton* m_ajouter_relation = new QPushButton("Ajouter Relation",this);
        connect(m_ajouter_relation,SIGNAL(clicked(bool)),this,SLOT(save_relation()));
    m_label_couple = new QLineEdit("Label du couple ?",this);
    QPushButton* m_ajouter_couple = new QPushButton("Ajouter Couple",this);
        connect(m_ajouter_couple,SIGNAL(clicked(bool)),this,SLOT(affichage_couples()));
        connect(m_ajouter_couple,SIGNAL(clicked(bool)),this,SLOT(save_couple()));
    m_label_relation = new QLineEdit("Label de la relation ?",this);
        //m_label_relation->setVisible(false);
    m_description_relation = new QTextEdit("Description de la relation ?",this);
    m_orientation = new QCheckBox("Relation orientée",this);
        m_orientation->setChecked(true);





    /**** Remplissage des QList avec les notes du manager ****/
    NotesManager2& m1 = NotesManager2::getManager();

    for (unsigned int i = 0; i<m1.gettype().size();i++)
    {

        m_notes_gauche->addItem(QString::fromStdString(m1.gettype()[i]->getID()));
        m_notes_droite->addItem(QString::fromStdString(m1.gettype()[i]->getID()));
    }

    /****** Ajouts au layout ******/
    m_layout->addWidget(m_notes_gauche,0,0);
    m_layout->addWidget(m_notes_droite,0,1);
    m_layout->addWidget(m_label_couple,1,0);
    m_layout->addWidget(m_orientation,1,1);
    m_layout->addWidget(m_ajouter_couple,2,0,1,2);
    m_layout->addWidget(m_liste_couples,3,0,1,2);
    m_layout->addWidget(m_label_relation,4,0,1,2);
    m_layout->addWidget(m_description_relation,5,0,1,2);
    m_layout->addWidget(m_ajouter_relation,6,0,1,2);
    m_layout->addWidget(m_quit,7,0,1,2);

    this->setLayout(m_layout);
}

void fenetre_creation_relation::affichage_couples()
{

    QString separateur = " <--> ";
    QString label = "Label : " + m_label_couple->text() +" | ";
    if (m_orientation->isChecked())
        separateur = " --> ";
    //On affiche le nouveau couple dans la liste de couples au milieu
    m_liste_couples->addItem(label + m_notes_gauche->currentItem()->text() + separateur + m_notes_droite->currentItem()->text());

}

void fenetre_creation_relation::save_relation()
{

    RelationManager& m = RelationManager::getManager();

    std::string erreur ="";
    try
    {
        m.getRelation(m_label_relation->text().toStdString());
    } catch (NotesException& excep)
    {
        erreur = excep.getInfo();
    }
    if (erreur == "")
    {
        QMessageBox msgBox;
        msgBox.setText("La relation existe déjà, veuillez recommencer avec un titre différent");
        msgBox.exec();
        return;
    }

    //Création d'une relation avec titre et description

    Relation* nouvelle_relation = new Relation(m_label_relation->text().toStdString(),m_description_relation->toPlainText().toStdString());


    //les couples sont stockés dans le vector "couples" de la fenetre, on les ajoute tous à la relation "nouvelle_relation"
    for (unsigned int i =0;i<getCouples().size();i++)
    {
        nouvelle_relation->addCouple(*getCouples()[i]);
    }

    //on ajoute au manager la relation créée
    m.addRelation(*nouvelle_relation);

    delete this; //on force la destruction pour l'affichage des relations
}

void fenetre_creation_relation::save_couple()
{
    NotesManager2& m = NotesManager2::getManager();
    std::string label = m_label_couple->text().toStdString();
    bool orientation = true;
    if (!m_orientation->isChecked())
        orientation = false;

    //Création d'un nouveau couple en récupérant les 2 notes via les ID selectionés dans chaque liste de notes
    Couple* nouveau = new Couple(m.getNote(m_notes_gauche->currentItem()->text().toStdString()),m.getNote(m_notes_droite->currentItem()->text().toStdString()),label,orientation);
    m_couples.push_back(nouveau);

}
