#include "relations.h"
#include "manager.h"
#include <regex>


void RelationManager::addRelation(Relation& relation)
{
    type.push_back(&relation);
}

RelationManager::RelationManager(){
} // constructeur de manager


RelationManager::~RelationManager(){
    for (unsigned int i=0;i<type.size();i++)
        delete type[i];
    type.clear();
    std::cout<<"le RelationManager est detruit"<<std::endl;
}


RelationManager::Handler RelationManager::handler=Handler();

Relation& RelationManager::getRelation(const std::string& titre)
{
    unsigned int i=0;
    while (i<type.size() && type[i]->getTitre() != titre)
    {
        i++;
    }
    if (i==type.size())
        throw NotesException("La relation n'existe pas\n");

    return *type[i];
}


RelationManager& RelationManager::getManager(){
    if (!handler.instance) handler.instance=new RelationManager;
    return *handler.instance;
}

void RelationManager::freeManager(){
    delete handler.instance;
    handler.instance=nullptr;
}
