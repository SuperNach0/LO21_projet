#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QApplication>
/*
#include <QPushButton>
#include <QWidget>
#include <QFont>
#include <QIcon>
#include <QWidget>
#include <QTextCodec>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QFileDialog>
//#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include <QDateTime>
#include <QLabel>
*/
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

private:

    QVBoxLayout* m_layout_principal;
    QPushButton* m_bouton1;
    QPushButton* m_bouton2;

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
