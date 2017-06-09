#include <iostream>
#include <time.h>
#include "notes.h"
#include "fenetres.h"
#include "relations.h"


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
*/


int menu =0;




int main(int argc,  char *argv[]){


    NotesManager2 &m1 = NotesManager2::getManager();
    RelationManager& m2 = RelationManager::getManager();

    ///pour afficher/retirer l'interface graphique, (dé)commenter les 4 lignes suivantes
    QApplication app(argc, argv);

    QString filename = QFileDialog::getOpenFileName();

    m1.setFilename(filename);
    m1.load();

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

                        m1.ajTache(id,action,priorite,echeance,en_attente).setTitre(t);


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
                    } break;
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
            break;
                }

         case 7 :
        {
            std::cout << "ESSAIS CYRIL Relations DE NOTES\n";
            /*
            Couple a(m1.getNote("id"),m1.getNote("id2"),"tamer");
            Couple a1(m1.getNote("id"),m1.getNote("id3"),"OKKK");
            Relation b("titre","desc");
            Relation b1("titre2","desc2");
            b.addCouple(a);
            b.addCouple(a);
            b.addCouple(a1);
            b1.addCouple(a);
            m2.addRelation(b);
            m2.addRelation(b1);
            */
            for (unsigned int i=0;i<m2.relations.size();i++)
            {
                std::cout << "titre de la relation : " << m2.relations[i]->getTitre() << std::endl;
                std::cout << "Description de la relation : " << m2.relations[i]->getDescription() << std::endl;

                std::cout << "Couple n°" << i <<":  "<< std::endl;
                for (unsigned int j=0;j<m2.relations[i]->getCouples().size();j++)
                {
                    std::cout << "Label premiere note: : " << m2.relations[i]->getCouples()[j]->getPremiere().getID() << std::endl;
                }

            }





        }

         case 10 : break;
        }


    };


    return  0;
}
