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

    Couple(note& note1, note& note2, std::string lab, bool orientation):premiere(&note1),seconde(&note2),label(lab),orientation(orientation){}
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


    std::vector<Couple*>& getCouples(){return couples;}
    const std::string& getTitre() const {return titre;}
    const std::string& getDescription() const {return description;}

};


class RelationManager {

private:
    std::vector<Relation*> relations;

    struct Handler {
             RelationManager* instance; // pointeur sur l'unique instance
             Handler():instance(nullptr){}
            ~Handler() { delete instance; }
        };
    static Handler handler;
    RelationManager();
    ~RelationManager();



 public:

    Relation& getRelation (const std::string& titre);
    void addRelation (Relation &relation);
    std::vector<Relation*> getRelations() {return relations;}
    static RelationManager& getManager();
    static void freeManager();
    bool checkReference(note& current) const;


};

#endif // RELATIONS_H
