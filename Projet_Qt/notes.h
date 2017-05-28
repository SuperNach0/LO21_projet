#ifndef NOTES_H
#define NOTES_H
#include <QString>

enum etat {en_attente,en_cours,terminee};


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

private :
    std::string id;
    std::string titre ;
    std::string Creation ;
    std::string Modif;

public :

     note (std::string i,std::string t): id(i),titre(t)
      {
        this->Creation = formatTime();
        this ->Modif = formatTime();}

    const std::string getID() const {return id;}
    const std::string getTitre() const {return titre;}
    const std::string getCreation() const {return Creation;}
    const std::string getModif() const {return Modif;}

     void setTitre(const std::string& t) {titre = t;}



    virtual void afficher(std::ostream& f= std::cout) const = 0; // virtuelle pure ( a definir dans les filles)
    virtual void MiseAJour () =0 ;

    void setModif () ;

   virtual ~note () {std::cout<<"suppression de la note "<<std::endl;};


};
/********************************************************/

class NotesManager2 {
 private :
    note** Note;
    unsigned int nbNote;
    unsigned int nbMaxNote;
    void addNote (note * n);
    mutable  std::string filename;

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

    note& getNote (const std::string& id); // return the article with identificator id (create a new one if it not exists)

    note& ajArticle(const std::string& id,const std::string& txt);
    note& ajMulti(const std::string& id,const std::string& description,const std::string& image);
    note& ajTache(const std::string& id,const std::string& action ,const unsigned int priorite,const std::string& echeance);





    std::string getFilename() const { return filename; }
    void setFilename(const std::string& f) { filename=f; }
    //void load(); // load notes from file filename
    //void save() const; // save notes in file filename
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

         /*const*/ note & current () const {return ** currentA;}

     };

          Searchiterator getSearchIterator(std::string tf) const
          {
              return Searchiterator(Note,nbNote,tf);
          }





};




//******SOUS CLASSE ARTICLE /  note avec un texte ******//


class article : public note {
protected :
    std::string texte ; //ce sera un QString après

public :
    article ( const std::string i, std::string t,std::string txt)
        : note (i,t) , texte (txt){}

    const std::string getTexte() const  {return texte;}


    virtual void afficher(std::ostream& f= std::cout) const;
    virtual void MiseAJour (); //PROBLEME : ne prend que le premier mot qu'on ecrit... jpese que le QString reglera le problème




};

class media : public note { // héritage nécessaire ? ou ptite énumération ?

protected :

    std::string  description ;
    std::string image ;//à changer avec QT : chemin vers l'image ?

public :
    media ( const std::string i, std::string t,std::string d,std::string im)
        : note (i,t) , description (d), image(im){}
    const std::string getDescription()const {return description;}
    const std::string getImage() const {return image;}

    virtual void afficher(std::ostream& f= std::cout) const ;
    virtual void MiseAJour ();





};


class tache : public note{// faut ajouter l'optionalité des trucs : constructeur ?

protected :
    std::string action;
    unsigned int priorite;
    std::string echeance; //date ?
    enum etat status;

public :

    tache (const std::string i, std::string t,std::string a, unsigned int p , std::string e)
        : note (i,t),action (a), priorite(p), echeance (e) {}

    const std::string getAction() const {return action;}
    const std::string getecheance() const {return echeance;}
    enum etat getEtat() const  {return status;}
    unsigned int getPriorite() const {return priorite;}

    virtual void afficher(std::ostream& f= std::cout) const ;
    virtual void MiseAJour () ;


};

#endif // NOTES_H
