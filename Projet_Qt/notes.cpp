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




char* formatTime (){


        time_t _time;

    struct tm timeInfo;
    char format[32];

    time(&_time);
    localtime_s(&timeInfo, &_time);

    strftime(format, 32, "%Y-%m-%d %H-%M", &timeInfo);

    std::cout << format << std::endl;

return format;
}
