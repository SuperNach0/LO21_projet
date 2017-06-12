#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>

#include<QApplication>
#include<QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <time.h>
#include "notes.h"
#include "manager.h"
#include "relations.h"
std::string etatToString(enum etat s)
{
    switch (s)
    {
        case 0:
            return "En attente";
            break;
        case 1:
            return "En cours";
            break;
        case 2:
            return "Terminee";
            break;
    }
}

/*********************fonctions de note************/

void note :: afficher(std::ostream& f ) const {
    f<<"id: "<<getID() << std::endl;
    f<<"titre:"<<getTitre() << std::endl;
    f<<"Texte:"<<getTexte() << std::endl;
    f<<"date creation:"<<getCreation() << std::endl;
    f <<"date modif:"<< getModif()<<std::endl;

}



//**********************fonction qui récupere lheure du système************************/

std::string formatTime (){

        char tmps[32];
        time_t _time;
        struct tm timeInfo;
        time(&_time);
        localtime_s(&timeInfo, &_time);

    strftime(tmps, 32, "%Y-%m-%d %H:%M:%S", &timeInfo);
    std::string temps = tmps;
return temps;
}
//**********************

void note::setModif () {
    this->Modif = formatTime();
}

//***********fonction de article

//constructeur de recopie
article::article(const article &article_a_copier) : note(article_a_copier.id,article_a_copier.titre,article_a_copier.texte)
{
    oldNotes.clear();
}

 void article ::afficher(std::ostream& f) const {

     f<<"*** Article ***" << std::endl;
     note::afficher();
     f<< "texte="<<getTexte() << std::endl;

}

//************************fonction de media****************


 void media :: afficher(std::ostream& f) const {
     f<<"***Media***" << std::endl;
     note::afficher();
     f <<" chemin ="<<chemin<<std::endl<<std::endl;
     }

 //constructeur de recopie
 media::media(const media &media_a_copier) : note(media_a_copier.id,media_a_copier.titre,media_a_copier.texte)
 {
     chemin = media_a_copier.chemin;
     oldNotes.clear();
 }

 //*****************************fonctions de taches ***************

  void tache :: afficher(std::ostream& f ) const {
      f<< "*** Tache ***"<<"\n";

      note::afficher();
      f<<" priorite :"<< priorite << " echeance : "<< echeance<<" etat = "<<status <<std::endl<<std::endl;

  }

 tache::tache(const tache &tache_a_copier) : note(tache_a_copier.id,tache_a_copier.titre,tache_a_copier.texte)
 {
     echeance=tache_a_copier.echeance;
     priorite=tache_a_copier.priorite;
     status=tache_a_copier.status;
     oldNotes.clear();
 }

 ///Vérifie si la note_a_analyser contient des références vers d'autres notes, et ajoute les relations dans le cas échéant
 void NotesManager2::checkReferences() const
 {
     RelationManager& rm = RelationManager::getManager();
     NotesManager2& nm = NotesManager2::getManager();

     //Suppression des couples correspondant à la note dans la relation References
     Relation& rel_references = rm.getRelation("References");
     rel_references.getCouples().clear();

     for (unsigned int i=0;i<nm.gettype().size();i++)
     {

         std::string texte = nm.gettype ()[i]->getTexte() + nm.gettype()[i]->getTitre(); //On récupère le texte de la note à analyser

         int position_debut_texte = texte.find("\\ref{");
         int position_fin_texte = texte.find("}",position_debut_texte);


         std::string id_texte =""; //contiendra l'id de la note courante


         while ((position_debut_texte != std::string::npos && position_fin_texte != std::string::npos))
         {
             std::cout << "TROUVE : " << std::endl;
             id_texte = texte.substr(position_debut_texte+5,position_fin_texte-position_debut_texte-5) ;
             std::cout << id_texte << std::endl;

             try{
             nm.getNote(id_texte);

            } catch (NotesException& excep)
             {
                 std::cout << "Note non trouvee dans checkRef\n";
                 std::cout << excep.getInfo();
                 QMessageBox msgBox;
                 msgBox.setText("Un ou plusieurs identifiants référencés ne sont pas valides, veuillez les corriger");
                 msgBox.exec();
                 return;
             }

             //ajout de la relation
             rel_references.addCouple(*(new Couple(*nm.gettype()[i],
                                                                 nm.getNote(id_texte),
                                                                 "Ref de " + nm.gettype()[i]->getID() + " vers " + nm.getNote(id_texte).getID(),
                                                                 1)));


             position_debut_texte = texte.find("\\ref{",position_fin_texte);
             position_fin_texte = texte.find("}",position_debut_texte);

         }

     }
    return;
 }
