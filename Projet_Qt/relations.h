#ifndef RELATIONS_H
#define RELATIONS_H

#include "notes.h"


class Couple
{
private:
    note* premiere;
    note* seconde;
    std::string label;
public:
    Couple(note& note1, note& note2):premiere(&note1),seconde(&note2){}
    const note& getPremiere() const {return *premiere;}
    const note& getSeconde() const {return *seconde;}
    const std::string getLabel() const {return label;}

};


class Relation
{
private:

    std::vector<Couple*> couples;
    std::string titre;
    std::string description;

public:
    std::vector<Couple*>& getCouples(){return couples;}
    const std::string& getTitre() const {return titre;}
    const std::string& getDescription() const {return description;}

};

#endif // RELATIONS_H
