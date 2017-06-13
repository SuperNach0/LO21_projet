#ifndef MANAGER_H
#define MANAGER_H
#include <QString>
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <vector>
#include "relations.h"


#endif // MANAGER_H
class RelationManager;

template<class T>
class Manager {
protected :

   std::vector<T*> type;
   QString filename;

public:

   void add (T& a_ajouter);
   void Supprimer (T& toDelete);
   const std::vector<T*> gettype() const {return type;}
   QString getFilename() const { return filename; }
   void setFilename(const QString& f) { filename=f; }

   Manager():type(0),filename(QString::fromStdString("..\\sauvegarde.xml")){}

   virtual ~Manager<T>(){std::cout<<"manager(base) detruit"<<std::endl;}
   Manager(const Manager& m);
   Manager& operator=(const Manager& m);
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
   NotesManager2();
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
