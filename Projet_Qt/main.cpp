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
*
* 27/05 : manager effectif (seulement sur la superclasse pour le moment)/ajout d'un menu SWAG

*/




//jpense faire une sorte de classe ou type pour le temps et les dates pourrait nous aider  !
//cyril : jpense ya pas besoin, Qt gère déjà bien les dates (cf QDate sur la doc)

int menu =0;




int main(int argc,  char *argv[]){

    NotesManager2& m1 = NotesManager2::getManager();

int menu =99;
while (menu!=10) {

    std::cout << "  tu as actuellement "<<m1.getnbNote()<<" notes ; que voulez vous faire  ?"<<std::endl<<
                 "1- ajouter une note"<<std::endl<<
                 "2- afficher les notes "<<std::endl<<
                 "3- rechercher une note"<<std::endl<<
                 "10- quitter"<<std::endl;
    std::cin>>menu;




    switch (menu){

    case 1 : {std::cout<<" creer"<<std::endl;
        std::string t;
        std::string id;
        std::cout<<" ID ?"<<std::endl;
        std::cin>> id;

        std::cout<<" quel est le titre de la note a creer ?"<<std::endl;
        std::cin>> t;
     m1.getNote(id).setTitre(t);
     std::cout<<" NOTE CREEE "<<std::endl;break;
    }




    case 2 :{
        for(NotesManager2::ConstIterator it= m1.getIterator(); !it.isDone(); it.next()){ it.current().afficher(); }break;
            }

    case 3 :{
        std::string tf;
        std::cout<<" titre/ partie du titre a trouver ?"<<std::endl;
        std::cin>> tf;
        for(NotesManager2::Searchiterator it= m1.getSearchIterator(tf); !it.isDone(); it.
                next())
                {
                    it.current().afficher();
                } break;
            }


     case 10 : break;
    }


};



     ///pour afficher/retirer l'interface graphique, (dé)commenter les 4 lignes suivantes

    QApplication app(argc, argv);
     FenPrincipale fenetre;
     fenetre.show();
     return app.exec();






    return  0;
}
