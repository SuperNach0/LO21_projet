#include "relations.h"
#include "manager.h"
#include <regex>


void RelationManager::addRelation(Relation& relation)
{
    type.push_back(&relation);
}

RelationManager::RelationManager(){
    RelationManager::addRelation(*(new Relation("References","Contient toutes les références entre notes")));
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

void save()
{

}








//********************************fin manager***********/

/*//Fonction pour checker si dans le titre ou texte d'une note il y a une référence vers une autre note

bool checkReference(note& current) const
{
    //On récupère l'instance des 2 managers
    NotesManager2& note_manager = NotesManager2::getManager();
    RelationManager& relation_manager = RelationManager::getManager();

    std::vector<std::string> liste_id;

    for(NotesManager2::ConstIterator it= note_manager.getIterator(); !it.isDone(); it.next())
    {
        liste_id.push_back(it.current().getID());
    }

    liste_id.clear();
}

bool RelationsManager::checkReference(Article& a) const{
    ///Instance de NotesManager
    NotesManager& nm = NotesManager::getInstance();
    ///Instance de RelationsManager
    RelationsManager& rm = RelationsManager::getInstance();
    ///Parcours de toutes les notes de notesManager.
    for (vector<Note*>::iterator it = nm.getIteratorBegin() ; it != nm.getIteratorEnd(); ++it){
        ///Pour chaque note on crée un Qstring personnalisé de la forme "\ref{id}".
        QString temp = "\ref{" + (*it)->getId() + "}";
            ///On parcourt le texte de l'article avec la fonction indexOf
            if (a.getText().indexOf(temp) != -1){
                    ///Si le Qstring créée est dans le texte, on crée le couple de l'article vers la note dont on a créé la Qstring personnalisée
                    Couple* c = new Couple(a,*(*it));
                    Relation* r = new Relation;
                    r->addRelation(*c);
                    rm.addRelation(r);
                    return true;
            }
            ///Sinon on ne fait rien
            else{qDebug() << "Pas présent dans " << (*it)->getId() << "\n";}
    }
    return false;
}
*/
