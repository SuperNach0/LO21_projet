#include<QApplication>
#include<QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <time.h>
#include "notes.h"
#include "fenprincipale.h"


/* A LIRE MONSIEUR LAY
 * en fait comme on a dit on ecrit d'abord le tout pour que ce soit
 * executable sur un terminal comme ca on saura que ca marche plus facilement
 *  avant
 * de se paumer dans des conneries graphiques.
 * du coup on oublie les Qstring pour le moment et on utilise des char*
 * on fera les changements quand on commencera vraiment le Qt
 * ca devrait pas trop prendre de temps
 *
 * la j'ai fait principalement la classe mere note et j'ai adapté un
 * manager(c'est lui qui gerera tout comme au médian)
 *
 * hésite pas a changer des trucs si tu veux ;)



*là je viens de charger en 2-2 une vieille GUI que j'avais faite ya longtemps, je la modifie bientot pour l'adapter

*/




//jpense faire une sorte de classe ou type pour le temps et les dates pourrait nous aider  !


int menu =0;




int main(int argc,  char *argv[]){

     article a (2,"bonjour","je suis un sacré sacripan");


     ///pour afficher l'interface graphique, décommenter les 4 lignes suivantes
     /*
     QApplication app(argc, argv);
     FenPrincipale fenetre;
     fenetre.show();
     return app.exec();
    */

    a.afficher();
    a.MiseAJour();
    a.afficher();


    return  0;
}
