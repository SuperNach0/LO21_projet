#include<QApplication>
#include<QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <time.h>
#include "notes.h"
#include "fenetres.h"


/*


*dernière modif au 26/05 : progression sur l'ajout d'une note

*/




//jpense faire une sorte de classe ou type pour le temps et les dates pourrait nous aider  !
//cyril : jpense ya pas besoin, Qt gère déjà bien les dates (cf QDate sur la doc)

int menu =0;




int main(int argc,  char *argv[]){

     article a (2,"bonjour","je suis un sacré sacripan");


     ///pour afficher/retirer l'interface graphique, (dé)commenter les 4 lignes suivantes

     QApplication app(argc, argv);
     FenPrincipale fenetre;
     fenetre.show();
     return app.exec();


    a.afficher();
    a.MiseAJour();
    a.afficher();


    return  0;
}
