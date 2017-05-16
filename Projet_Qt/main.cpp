#include<QApplication>
#include<QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>


int main( int argc, char * argv[]) {
    QApplication app(argc, argv);
    QWidget fenetre;
    fenetre.setFixedSize(200, 200);
    //...

    QLabel id1 ("Identificateur",&fenetre);
    id1.move(10,10);
    id1.show();
    QLabel titre1 ("Titre",&fenetre);
    titre1.move(10,45);
    titre1.show();
    QLabel text1 ("Texte",&fenetre);
    text1.move(10,80);
    text1.show();

    QLineEdit id(&fenetre);
    id.setGeometry(100,10,95,20);
    id.show();

    QLineEdit titre(&fenetre);
    titre.setGeometry(100,45,95,20);
    titre.show();

    QTextEdit text (&fenetre);
    text.setGeometry(100,80,95,110);
    text.show();

    QPushButton  save ("Sauver",&fenetre);
   // QPushButton::connect(&coucou,SIGNAL(clicked()),&leave,SLOT(show()));
    save.setGeometry(10,170,80,20);
    save.show();




    fenetre.show();

    return app.exec();
}
