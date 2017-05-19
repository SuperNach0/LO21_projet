#ifndef NOTES_H
#define NOTES_H
#include <QString>


std::string formatTime ();

class note {

private :
    unsigned int id;
    std::string titre ;
    std::string JourCreation ;
    std::string JourModif;

public :

     note (int i,std::string t): id(i),titre(t)
      {


        this->JourCreation = formatTime();
        std::cout<<formatTime()<<std::endl;
        this ->JourModif = formatTime();}
    unsigned int getID() const {return id;}
    const std::string getTitre() const {return titre;}
    const std::string getJourCreation() const {return JourCreation;}
    const std::string getJourModif() const {return JourModif;}

    void afficher(std::ostream& f= std::cout) const;







};





#endif // NOTES_H
