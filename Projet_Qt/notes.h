#ifndef NOTES_H
#define NOTES_H
#include <QString>


std::string formatTime ();

class note {

private :
    unsigned int id;
    std::string titre ;
    std::string Creation ;
    std::string Modif;

public :

     note (int i,std::string t): id(i),titre(t)
      {


        this->Creation = formatTime();
        std::cout<<formatTime()<<std::endl;
        this ->Modif = formatTime();}
    unsigned int getID() const {return id;}
    const std::string getTitre() const {return titre;}
    const std::string getCreation() const {return Creation;}
    const std::string getModif() const {return Modif;}

    void afficher(std::ostream& f= std::cout) const;
    void setModif () ;

    ~note () {std::cout<<"suppression de la note "<<std::endl;};






};





#endif // NOTES_H
