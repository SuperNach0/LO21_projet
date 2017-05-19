#include<QApplication>
#include<QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <time.h>
#include "notes.h"

void note::afficher(std::ostream& f) const
{
    f<<"***** note ********"<<"\n"<<"id="<<getID()<<" titre="<<getTitre()<<" date creation="<<getJourCreation()<<" date modif="<<getJourModif()<<"\n";
}

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
