#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QApplication>
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

#include <iostream>

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

class fenetre_creation_note : public QWidget
{
    Q_OBJECT

public:
    fenetre_creation_note();

private:
    QVBoxLayout* m_layout_choix;

    QLineEdit* id;
    QLineEdit* titre;

};


#endif // FENPRINCIPALE_H
