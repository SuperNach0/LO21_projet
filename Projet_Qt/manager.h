#ifndef MANAGER_H
#define MANAGER_H
#include <QString>
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <vector>
#include "relations.h"


#endif // MANAGER_H


/// Classe mère Template abstraite Managers.
/** Cette classe regroupe  les attributs et les méthodes communes aux différents Managers.
 * Elle est composée d'un vector de template<classe T> qui stockera et manipulera les objets T,
 *  et d'un chemin de fichier (par défaut) qui mène au fichier .xml dans lequel les objets seront sauvegardés.
 *
 */
class RelationManager;

template<class T>
class Manager {
protected :

   std::vector<T*> objets;
   mutable  QString filename;

public:

   /// fonction qui vérifie si l'id de l'objet de type T fourni en paramètre existe déja en parcourant le vector (exeption si c'est le cas),et qui l'ajoute à l'arrièredu  vector si ce n'est pas le cas.
  /**
  * @param T& : référence sur l'objet à ajouter.
  */
    void add (T& a_ajouter);
    /// fonction qui supprime du vector l'objet de type T fourni en paramètre
   /**
   * @param T& : référence sur l'objet à supprimer.
   */
    void Supprimer (T& toDelete);
    ///accesseur en lecture du vector contennat les objets T.
     const std::vector<T*> getobjets() const {return objets;}
     ///accesseur en lecture du chemin du fichier xml.
   QString getFilename() const { return filename; }

   void setFilename(const QString& f) { filename=f; }

   Manager():objets(0),filename(QString::fromStdString("..\\sauvegarde.xml")){}

   virtual ~Manager<T>(){std::cout<<"manager(base) detruit"<<std::endl;}

   virtual void load () =0 ;
   virtual void save () =0 ;

};




class NotesManager2 :  public Manager<note> {

private :

public:

    struct Handler {
             NotesManager2* instance; // pointeur sur l'unique instance
             Handler():instance(nullptr){}
            ~Handler() { delete instance; }
        };
    static Handler handler;
   NotesManager2(){};
   ~NotesManager2();


   //NotesManager2(const NotesManager2& m);
   //NotesManager2& operator=(const NotesManager2& m);

   //void addNote (const QString& i, const QString& ti, const QString& te);//3


public:

   note& getNote (const std::string& id, const std::string& date="");
   note& getOldNote(const std::string& id);
   void SupprimerNote (note& toDelete, const std::string& date="");

   void load(); // load notes from file filename
   void save(); // save notes in file filename


   static NotesManager2& getManager();
   static void freeManager();

   void checkReferences() const;

};


class RelationManager : public Manager<Relation> {

private:


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
    void addRelation(Relation& relation);

    static RelationManager& getManager();
    static void freeManager();

    void load() {}; // load notes from file filename
    void save(){} // save notes in file filename



};
