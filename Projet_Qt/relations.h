#ifndef RELATIONS_H
#define RELATIONS_H

#include "notes.h"


class Couple
{
private:
    note* premiere;
    note* seconde;
    std::string label;
    bool orientation;
public:

    Couple(note& note1, note& note2, std::string lab, bool ori):premiere(&note1),seconde(&note2),label(lab),orientation(ori){}
    const note& getPremiere() const {return *premiere;}
    const note& getSeconde() const {return *seconde;}
    const std::string getLabel() const {return label;}
    bool isOriented() const {return orientation;}

};


class Relation
{
private:

    std::vector<Couple*> couples;
    std::string titre;
    std::string description;

public:
    Relation(const std::string& tit, const std::string& desc) : couples(0),titre(tit),description(desc){}
    void addCouple(Couple& couple){couples.push_back(&couple);}

    //void supprimerCouple(std::string& label) {}
    std::vector<Couple*>& getCouples(){return couples;}
    const std::string& getTitre() const {return titre;}
    const std::string& getDescription() const {return description;}
    void setDescription(std::string desc){description=desc;}

};




#endif // RELATIONS_H
