#include <iostream>
#include <time.h>
#include "notes.h"
#include "fenetres.h"
#include "relations.h"
#include "manager.h"

/*


* 30/05 : ajout d'un menu contextuel pour supprimer une note
* 31/05 : modification du getNote : retourne un article("","","") si la note n'existe pas (en plus de throw une erreur) : à voir si on peut faire mieux
*
* 06/06 : affichage d'une seule note OK (enfin)
*       : j'ai modifié la classe note pour avoir direct un attribut "texte" qui était présent dans chaque sous classe
*       : du coup j'ai enlevé tes fonctions "mise à jour" qui de toute façon ne sont pas utilisées avec la GUI
*       : Edition d'une note OK, manque à gérer les versions (en progrès)
*
* 07/06 : affichage des versions de notes OK mashallah
*       : reste à faire : gérer la restauration, mais ptètre plus urgent de faire d'abord les relations ?
*
* 08/06 : début taff relation
*       : relation manager OP
*       : création relation en progrès
*       : création relation presque ok, j'ai pas beaucoup testé mais ça devrait être good, manque à faire un iterator
*
*
* 09/06 : load fonctionne pour aricle normalement.
*         il faudrait que tu mettes une actualisation de l'affichage des notes dès le chargment de la fenetre
*         et pas que a la création sionon les anciennes ne s'afficheront pas !
*          ATTENTION BUG : load sur un XML vide il kiffe pas
*
* 09/06 : bouton OK pour load (fichier..charger un xml)
*       : actualisation des notes dès le chargement de la fenetre c bon
*       : visualisation de la liste des relations c'est bon, manque affichage de chaque relation
*
* 10/06 : Affichage de chaque relation OK
*       : un truc qui serait cool à faire : utiliser un design pattern pour pouvoir recycler le manager et/ou l'itérateur de NotesManager
*       : mais du coup il faudrait changer NotesManager et utiliser un vector, ou changer RelationManager et y mettre un tableau...
*
* 11/06 : Correction de l'ajout d'une relation avec un titre déjà utilisé
*       : Pareil pour une note, maintenant plus d'article vide créé dans le getNote si la note n'existe pas
*
*       :Ajout des references avec \ref{id} mais ça ne fonctionne pas, je sais pas pourquoi
*/


int menu =0;




int main(int argc,  char *argv[]){


    NotesManager2  &m1 = NotesManager2::getManager();
    RelationManager& m2 = RelationManager::getManager();

    ///pour afficher/retirer l'interface graphique, (dé)commenter les 4 lignes suivantes
    QApplication app(argc, argv);


    FenPrincipale fenetre;

    fenetre.show();

    app.exec();


    int menu =99; int j=0;
    while (menu!=10) {

        std::cout << "  tu as actuellement "<<m1.getNotes().size() <<" notes ; que voulez vous faire  ?"<<std::endl<<
                     "1- ajouter une note"<<std::endl<<
                     "2- afficher les notes "<<std::endl<<
                     "3- rechercher une note"<<std::endl<<
                     "4- mettre a jour note(que tachepour le moment)"<<std::endl<<
                     "5- supprimer une note"<<std::endl<<
                     "7- tests cyril affichage relation note "<<std::endl<<
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
                        std::cin>>txt;

           //             m1.ajArticle(id,t,txt);
                    }
                    if (j==2){ std::string description;std::string image;
                        std::cout<<" la description ?"<<std::endl;
                        std::cin>> description;
                        std::cout<<" la image ?"<<std::endl;
                        std::cin>> image;
       //                 m1.ajMulti(id,t,description,image);
                    }
                    if (j==3){ std::string action ;  unsigned int priorite;  std::string echeance;

                        std::cout<<" action?"<<std::endl;
                        std::cin>> action;
                        std::cout<<" priorite (int)?"<<std::endl;
                        std::cin>> priorite;
                        std::cout<<" echeance?"<<std::endl;
                        std::cin>> echeance;

           //             m1.ajTache(id,t,action,priorite,echeance,en_attente);


                    }break;
        }






        case 2 :{


                }

        case 3 :{
            std::string tf;
            std::cout<<" titre/ partie du titre a trouver ?"<<std::endl;
            std::cin>> tf;

                }

        case 4 :{
            std::string tf;
            std::cout<<" ID de la note a changer?"<<std::endl;
            std::cin>> tf;
            //m1.getNote(tf).MiseAJour();// plymorphisme à definir dans les classes filles
                                          // faudrait que ca les affiche comme si on en créait non ?
                     break;
                }

        case 5 :{
                std::cout<<"id de la note à supprimer?"<<std::endl;
                std::string td;
                std::cin>> td;

               m1.SupprimerNote(m1.getNote(td));
             // m1.Supprimer(m1.getNote(td));
            break;
                }

         case 7 :
        {
            std::cout << "ESSAIS CYRIL references de notes\n";
            article* nouv = new article("id","titre","txt, \ref{id} suite \ref{id2} okalm");
            article* nouv1 = new article("id","titre","texte a lacon");
            article* nouv2 = new article("id2","titr2222e","txt");
            m1.addNote(*nouv);
            m1.addNote(*nouv2);


            m1.checkReferences(m1.getNote("id"));

        }

         case 10 : break;
        }


    };


    return  0;
}
