#include<QApplication>
#include<QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <time.h>
#include "notes.h"





int main( ) {


     note p (2,"hellowww");
    p.afficher();



    p.setModif();

    p.afficher();

    return  0;
}
