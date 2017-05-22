#include<QApplication>
#include<QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <time.h>
#include "notes.h"






//**********************fonction qui récupere lheure du système************************/

std::string formatTime (){

         char tmps[32];
        time_t _time;
        struct tm timeInfo;
        time(&_time);
        localtime_s(&timeInfo, &_time);

    strftime(tmps, 32, "%Y-%m-%d %H-%M", &timeInfo);
    std::string temps = tmps;
return temps;
}
//**********************


void note::setModif () {
    this->Modif = formatTime();
}

//***********fonction de article

 void article ::afficher(std::ostream& f) const {

     f<<"***** article ********"<<"\n"<<"id="<<getID()<<" titre="<<getTitre()<<" date creation="<<getCreation()<<" date modif="<<getModif()<<"\n"
     <<"texte ="<<texte<<std::endl;

}


   void article ::  MiseAJour () {


     std::cout <<"mettez a jour le texte "<<std::endl;
     std::cin>> texte;
     setModif();

 }


//************************fonction de media****************


 void media :: afficher(std::ostream& f) const {
     f<<"***** media ********"<<"\n"<<"id="<<getID()<<" titre="<<getTitre()<<" date creation="<<getCreation()<<" date modif="<<getModif()<<"\n"
     <<"description ="<<description<<std::endl;
     }
 void media :: MiseAJour () {

     std::cout <<"mettez a jour la description "<<std::endl;
     std::cin>> description;
     setModif();
     }


 //*****************************fonctions de taches ***************

  void tache :: afficher(std::ostream& f ) const {
      f<<"***** tache ********"<<"\n"<<"id="<<getID()<<" titre="<<getTitre()<<" date creation="<<getCreation()<<" date modif="<<getModif()<<"\n"
      <<"action ="<<action<<"priorité :"<< priorite << "echeance : "<< echeance<<"etat = "<<status <<std::endl;

  }
  void tache:: MiseAJour () {
      // trucs a faire wallah
      setModif();

  }
