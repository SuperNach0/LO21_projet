#ifndef NOTES_H
#define NOTES_H
#include <QString>
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <vector>


enum etat {en_attente,en_cours,terminee};

std::string etatToString(enum etat s);


std::string formatTime ();

class note;

class NotesManager2;

class NotesException{
public:
    NotesException(const std::string& message):info(message){}
    std::string getInfo() const { return info; }
private:
    std::string info;
};




//****************** SUPER CLASSE NOTE***********************/
class note {

protected :
    std::string id;
    std::string titre ;
    std::string Creation ;
    std::string Modif;
    std::string texte;
    std::vector<note*> oldNotes;

public :

     note (std::string i,std::string t,std::string txt,std::string crea="",std::string modif =""): id(i),titre(t),texte(txt),oldNotes(0)
     { if  (crea=="") {
        this->Creation = formatTime();
        this->Modif = formatTime();
     }
     else  {
             this->Creation = crea;
             this->Modif = modif;
         }
     }



    const std::string getID() const {return id;}
    const std::string getTitre() const {return titre;}
    const std::string getCreation() const {return Creation;}
    const std::string getModif() const {return Modif;}
    const std::string getTexte() const {return texte;}
    std::vector<note*>& getOldNotes() {return oldNotes;}

    void setTexte(const std::string& text) {texte = text;}
    void setTitre(const std::string& t) {titre = t;}



    virtual void afficher(std::ostream& f= std::cout) const = 0; // virtuelle pure ( a definir dans les filles)



    //virtual void MiseAJour () =0 ;

    void setModif () ;

   virtual ~note () {std::cout<<"suppression de la note "<<std::endl;}; //à rajouter dans le destructeur : destruction de toutes les vieilles versions


};


class NotesManager2
{
private :
   std::vector<note*> notes;

   mutable  QString filename;

   struct Handler {
            NotesManager2* instance; // pointeur sur l'unique instance
            Handler():instance(nullptr){}
           ~Handler() { delete instance; }
       };
   static Handler handler;
   NotesManager2();
   ~NotesManager2();
   NotesManager2(const NotesManager2& m);
   NotesManager2& operator=(const NotesManager2& m);


   //void addNote (const QString& i, const QString& ti, const QString& te);//3




public:

   note& getNote (const std::string& id, const std::string& date="");
   note& getOldNote(const std::string& id);
   void addNote (note& note_a_ajouter);

   const std::vector<note*> getNotes() const {return notes;}

   void SupprimerNote (note& toDelete);
   QString getFilename() const { return filename; }
   void setFilename(const QString& f) { filename=f; }
   void load(); // load notes from file filename
   void save(); // save notes in file filename


   static NotesManager2& getManager();
   static void freeManager();



};

//Vieux manager avec tableau
/*
class NotesManager2 {
 private :
    note** Note;
    unsigned int nbNote;
    unsigned int nbMaxNote;
    void addNote (note * n);
    mutable  QString filename;

    struct Handler {
             NotesManager2* instance; // pointeur sur l'unique instance
             Handler():instance(nullptr){}
            ~Handler() { delete instance; }
        };
    static Handler handler;
    NotesManager2();
    ~NotesManager2();
    NotesManager2(const NotesManager2& m);
    NotesManager2& operator=(const NotesManager2& m);
    void addNote (const QString& i, const QString& ti, const QString& te);//3


 public:

    unsigned int getnbNote() const {return nbNote;}
    note& getNote (const std::string& id, const std::string& date=""); // return the article with identificator id (create a new one if it not exists)
    note& getOldNote(const std::string& id);
    note& ajArticle(const std::string& id,const std::string& titre,const std::string& txt,const std::string& crea="",const std::string& modif="");
    note& ajMulti(const std::string& id,const std::string& titre,const std::string& description,const std::string& image,const std::string& crea="",const std::string& modif="");
    note& ajTache(const std::string& id,const std::string& titre, const std::string& action , const unsigned int priorite, const std::string& echeance, enum etat stat,const std::string& crea="",const std::string& modif="");



    void SupprimerNote (note& toDelete);





    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }
    void load(); // load notes from file filename
    void save() const; // save notes in file filename
    static NotesManager2& getManager();
    static void freeManager();

    class ConstIterator {
        friend class NotesManager2;
        note** currentA;
        unsigned int nbRemain;
        ConstIterator(note** a, unsigned nb):currentA(a),nbRemain(nb){}
    public:
        ConstIterator():nbRemain(0),currentA(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw NotesException("error, next on an iterator which is done");
            nbRemain--;
            currentA++;
        }
        const note& current() const {
            if (isDone())
                throw NotesException("error, indirection on an iterator which is done");
            return **currentA;
        }
    };
    ConstIterator getIterator() const {
        return ConstIterator(Note,nbNote);
    }

    class Searchiterator{
          friend class NotesManager2;
          note ** currentA;
          int nbRemain;
          std::string toFind;
          Searchiterator(note **a, int nb, std::string tf): currentA(a),nbRemain(nb), toFind(tf){
             while (nbRemain > 0 && (**currentA).getTitre().find(toFind)== std::string::npos){
              currentA++;
              nbRemain--;}

          }

      public:
          bool isDone () const { return nbRemain ==0;}

          void next ()
          {
              if (isDone())
                  throw NotesException("ERROR : fin de la collection");
              currentA++;
              nbRemain --;
              while (nbRemain > 0 && (**currentA).getTitre().find(toFind)== std::string::npos)
              {
                  currentA++;
                  nbRemain--;
              }

          }

          note & current () const {return ** currentA;}

     };

          Searchiterator getSearchIterator(std::string tf) const
          {
              return Searchiterator(Note,nbNote,tf);
          }





};

*/
//******SOUS CLASSE ARTICLE /  note avec un texte ******//


class article : public note {

public :

    article (  std::string i, std::string t,std::string txt, std::string crea="",std::string modif="")
        : note (i,t,txt,crea,modif){}
    article (const article& article_a_copier);

    virtual void afficher(std::ostream& f= std::cout) const;

};

class media : public note { // héritage nécessaire ? ou ptite énumération ?

protected :

    std::string chemin ;//à changer avec QT : chemin vers l'image ?

public :
    media ( const std::string i, std::string t,std::string txt, std::string im ,std::string crea="",std::string modif="" )
        : note (i,t,txt,crea,modif),chemin(im){}
    media(const media& media_a_copier);
    const std::string getChemin() const {return chemin;}
    void setChemin(const std::string& text) {chemin = text;}

    virtual void afficher(std::ostream& f= std::cout) const ;
    //virtual void MiseAJour ();

};


class tache : public note{// faut ajouter l'optionalité des trucs : constructeur ?

protected :
    unsigned int priorite;
    std::string echeance;
    enum etat status;

public :


    tache ( const std::string i, std::string t,std::string txt, unsigned int p , std::string e,enum etat Status,std::string crea="",std::string modif="" )
        : note (i,t,txt,crea,modif),priorite(p), echeance (e),status(Status){}

    tache(const tache &tache_a_copier); //constructeur recopie (sert pour gérer les versions)

    const std::string getecheance() const {return echeance;}
    enum etat getEtat() const  {return status;}
    unsigned int getPriorite() const {return priorite;}

    void setPriorite(int prio){priorite=prio;}
    void setEcheance(const std::string& date){echeance=date;}
    void setStatus(enum etat stat){status=stat;}

    virtual void afficher(std::ostream& f= std::cout) const ;
    //virtual void MiseAJour () ;


};

#endif // NOTES_H
