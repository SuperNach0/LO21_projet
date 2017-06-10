#include "relations.h"
#include "manager.h"
void RelationManager::addRelation(Relation& relation)
{
    relations.push_back(&relation);
}


RelationManager::RelationManager():relations(0){

} // constructeur de manager


RelationManager::~RelationManager(){
    for (unsigned int i=0;i<relations.size();i++)
        delete relations[i];
    relations.clear();
    std::cout<<"le RelationManager est detruit"<<std::endl;
}


RelationManager::Handler RelationManager::handler=Handler();


Relation& RelationManager::getRelation(const std::string& titre)
{
    unsigned int i=0;
    while (i<relations.size() && relations[i]->getTitre() != titre)
    {
        i++;
    }
    return *relations[i];
    throw NotesException("La relation n'existe pas\n");

}


/*
void NotesManager2::SupprimerNote (note& toDelete)
{
    int i=0;
    while (Note[i]->getID() != toDelete.getID())
    {
        i++;
    }

    for (i;i<nbNote;i++)
    {
        Note[i]=Note[i+1];
    }
    nbNote--;
    delete &toDelete;
}
*/

RelationManager& RelationManager::getManager(){
    if (!handler.instance) handler.instance=new RelationManager;
    return *handler.instance;
}

void RelationManager::freeManager(){
    delete handler.instance;
    handler.instance=nullptr;
}


//********************************fin manager***********/
