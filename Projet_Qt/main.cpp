#include <iostream>
#include <time.h>
#include "notes.h"
#include "fenetres.h"


/*


*
* est-ce que tu pourras rajouter l'initialisation de l'état à "en attente" quand on crée une tache ?
*
* faudra tu m'expliques pourquoi quand tu crée un objet tu fais m1.ajMulti(id,description,image).setTitre(t); pourquoi le titre est pas dans le constructeur ?
* cest pour "séparer" et pas tout faire d'un coup pmai son peut changer si tu veux
*   --> je suis chaud que tu changes ouais ça parait beaucoup plus logique
*
* 30/05 : ajout d'un menu contextuel pour supprimer une note
* 31/05 : modification du getNote : retourne un article("","","") si la note n'existe pas (en plus de throw une erreur) : à voir si on peut faire mieux
*
* A FAIRE MON PETIT ERWAN : changer la fonction mise_a_jour pour qu'elle prenne en paramètre les modifications et que ça change direct
*/


int menu =0;




int main(int argc,  char *argv[]){

    ///pour afficher/retirer l'interface graphique, (dé)commenter les 4 lignes suivantes
    QApplication app(argc, argv);
    NotesManager2 &m1 = NotesManager2::getManager();
    //QString filename = QFileDialog::getOpenFileName();

    //m1.setFilename(filename);
    FenPrincipale fenetre;
    fenetre.show();
    app.exec();


    int menu =99; int j=0;
    while (menu!=10) {

        std::cout << "  tu as actuellement "<<m1.getnbNote()<<" notes ; que voulez vous faire  ?"<<std::endl<<
                     "1- ajouter une note"<<std::endl<<
                     "2- afficher les notes "<<std::endl<<
                     "3- rechercher une note"<<std::endl<<
                     "4- mettre a jour note(que tachepour le moment)"<<std::endl<<
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

            std::cout << " tu veux ?"<<std::endl<<
                         "1- article"<<std::endl<<
                         "2- multimedia "<<std::endl<<
                         "3- tache"<<std::endl;
            std::cin>>j;

                    if (j==1){  std::string txt;
                        std::cout<<" le texte de larticle ?"<<std::endl;
                        //std::cin>>txt;
                        //std::getline(std::cin,txt);

                        //std::cin.sync(); //clear buffer
                        //std::cin.get();

                        //std::getline(std::cin, txt);
                        std::cin>>txt;

                        m1.ajArticle(id,txt).setTitre(t);
                    }
                    if (j==2){ std::string description;std::string image;
                        std::cout<<" la description ?"<<std::endl;
                        std::cin>> description;
                        std::cout<<" la image ?"<<std::endl;
                        std::cin>> image;
                        m1.ajMulti(id,description,image).setTitre(t);
                    }
                    if (j==3){ std::string action ;  unsigned int priorite;  std::string echeance;

                        std::cout<<" action?"<<std::endl;
                        std::cin>> action;
                        std::cout<<" priorite (int)?"<<std::endl;
                        std::cin>> priorite;
                        std::cout<<" echeance?"<<std::endl;
                        std::cin>> echeance;

                        m1.ajTache(id,action,priorite,echeance).setTitre(t);


                    }break;
        }






        case 2 :{
            for(NotesManager2::ConstIterator it= m1.getIterator(); !it.isDone(); it.next())
            {
                    it.current().afficher();
            }
            break;
                }

        case 3 :{
            std::string tf;
            std::cout<<" titre/ partie du titre a trouver ?"<<std::endl;
            std::cin>> tf;
            for(NotesManager2::Searchiterator it= m1.getSearchIterator(tf); !it.isDone(); it.
                    next())
                    {
                        it.current().afficher();
                        //std::cout << it.current(); marche pas :'( c'est parce que it.current te renvoie un eréférence
                    } break;
                }

        case 4 :{
            std::string tf;
            std::cout<<" ID de la note a changer?"<<std::endl;
            std::cin>> tf;
            m1.getNote(tf).MiseAJour();// plymorphisme à definir dans les classes filles
                                          // faudrait que ca les affiche comme si on en créait non ?
                     break;
                }

         case 10 : break;
        }


    };


    return  0;
}
