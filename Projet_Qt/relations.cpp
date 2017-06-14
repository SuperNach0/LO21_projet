#include "relations.h"
#include "manager.h"
#include <regex>


void RelationManager::addRelation(Relation& relation)
{
    objets.push_back(&relation);
}

RelationManager::RelationManager(){
} // constructeur de manager


RelationManager::~RelationManager(){
    for (unsigned int i=0;i<objets.size();i++)
        delete objets[i];
    objets.clear();
    std::cout<<"le RelationManager est detruit"<<std::endl;
}


RelationManager::Handler RelationManager::handler=Handler();

Relation& RelationManager::getRelation(const std::string& titre)
{
    unsigned int i=0;
    while (i<objets.size() && objets[i]->getTitre() != titre)
    {
        i++;
    }
    if (i==objets.size())
        throw NotesException("La relation n'existe pas\n");

    return *objets[i];
}


RelationManager& RelationManager::getManager(){
    if (!handler.instance) handler.instance=new RelationManager;
    return *handler.instance;
}

void RelationManager::freeManager(){
    delete handler.instance;
    handler.instance=nullptr;
}
