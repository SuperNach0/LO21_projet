#include<QApplication>
#include<QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <time.h>
#include "notes.h"


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
 * hésite pas a changer des trucs si tu veux ;) */


int menu =0;




int main( ) {

     article a (2,"bonjour","je suis un sacré sacripan");




    a.afficher();
    a.MiseAJour();
    a.afficher();




    return  0;
}
