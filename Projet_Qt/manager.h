﻿#ifndef MANAGER_H
#define MANAGER_H
#include <QString>
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <vector>


#endif // MANAGER_H


/*
  template<class T>  class Manager {
private :

     T** type;
    unsigned int nb;
    unsigned int nbMax;
    template<class Type> void add (Type* a);
    mutable  QString filename;

    struct Handler {
             Manager* instance; // pointeur sur l'unique instance
             Handler():instance(nullptr){}
            ~Handler() { delete instance; }
        };
    static Handler handler;
    Manager();
    ~Manager();
    Manager(const Manager& m);
    Manager& operator=(const Manager& m);


public:
    unsigned int getnb() const {return nb;}

    template<class Type> void Supprimer (Type& toDelete);

    static Manager& getManager();
    static void freeManager();

    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }


     class ConstIterator {

        friend class Manager;
        T** currentA;
        unsigned int nbRemain;
        ConstIterator(T** a, unsigned nb):currentA(a),nbRemain(nb){}
    public:
        ConstIterator():nbRemain(0),currentA(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw ("error, next on an iterator which is done");
            nbRemain--;
            currentA++;
        }
        const T& current() const {
            if (isDone())
                throw ("error, indirection on an iterator which is done");
            return **currentA;
        }
    };
     ConstIterator getIterator() const {
        return ConstIterator(type,nb);
    }


     class Searchiterator{
           friend class Manager;
           T ** currentA;
           int nbRemain;
           std::string toFind;
           Searchiterator(T **a, int nb, std::string tf): currentA(a),nbRemain(nb), toFind(tf){
              while (nbRemain > 0 && (**currentA).getTitre().find(toFind)== std::string::npos){
               currentA++;
               nbRemain--;}

           }

       public:
           bool isDone () const { return nbRemain ==0;}

           void next ()
           {
               if (isDone())
                   throw ("ERROR : fin de la collection");
               currentA++;
               nbRemain --;
               while (nbRemain > 0 && (**currentA).getTitre().find(toFind)== std::string::npos) //attention get titre ?
               {
                   currentA++;
                   nbRemain--;
               }

           }

           T & current () const {return ** currentA;}

      };

           Searchiterator getSearchIterator(std::string tf) const
           {
               return Searchiterator(type,nb,tf);
           }



};


class NotesManager2 : public  Manager {
 private :

    void addNote (const QString& i, const QString& ti, const QString& te);//3


 public:



    note& getNote (const std::string& id, const std::string& date=""); // return the article with identificator id (create a new one if it not exists)
    note& getOldNote(const std::string& id);

    note& ajArticle(const std::string& id,const std::string& titre,const std::string& txt,const std::string& crea="",const std::string& modif="");
    note& ajMulti(const std::string& id,const std::string& titre,const std::string& description,const std::string& image,const std::string& crea="",const std::string& modif="");
    note& ajTache(const std::string& id,const std::string& titre, const std::string& action , const unsigned int priorite, const std::string& echeance, enum etat stat,const std::string& crea="",const std::string& modif="");


    void load(); // load notes from file filename
    void save() const; // save notes in file filename











};

*/
