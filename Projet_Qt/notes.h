#ifndef NOTES_H
#define NOTES_H
#include <QString>


char* formatTime ();

class note {

private :
    unsigned int id;
    std::string titre ;
    char* JourCreation ;
    char* JourModif;

public :

     note (int i,std::string t): id(i),titre(t)
      {
        time_t _time;
        this->JourCreation = formatTime();
        this ->JourModif = formatTime();}
     unsigned int getID() const {return id;}
    const std::string getTitre() const {return titre;}
    const char* getJourCreation() const {return JourCreation;}
    const char* getJourModif() const {return JourModif;}

    void afficher(std::ostream& f= std::cout) const;







};





#endif // NOTES_H
