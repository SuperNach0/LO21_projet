#ifndef NOTES_H
#define NOTES_H
#include <QString>

enum etat {en_attente,en_cours,terminee};


std::string formatTime ();



//****************** SUPER CLASSE NOTE***********************/
class note {

private :
    unsigned int id;
    std::string titre ;
    std::string Creation ;
    std::string Modif;

public :

     note (int i,std::string t): id(i),titre(t)
      {
        this->Creation = formatTime();
        this ->Modif = formatTime();}

    unsigned int getID() const {return id;}
    const std::string getTitre() const {return titre;}
    const std::string getCreation() const {return Creation;}
    const std::string getModif() const {return Modif;}

    virtual void afficher(std::ostream& f= std::cout) const = 0; // virtuelle pure ( a definir dans les filles)
    virtual void MiseAJour () =0 ;

     void setModif () ;

   virtual ~note () {std::cout<<"suppression de la note "<<std::endl;};


};


//*******************NOtes manager que j'ai pompé d'un td6
// les exeptions sont pas encore fait du coup -> en commentaire
//pareil pour tout  ce qui contennait du Qstring et des file name


class NotesManager {
private:
    note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    void addNote (note* a);
   // mutable QString filename;
    struct Handler {
        NotesManager* instance; // pointeur sur l'unique instance
        Handler():instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handler;
    NotesManager();
    ~NotesManager();
    NotesManager(const NotesManager& m);
    NotesManager& operator=(const NotesManager& m);
    //void addNote(const QString& i, const QString& ti, const QString& te);
public:
    note& getNote(const unsigned int id); // return the note with identificator id (create a new one if it not exists)
//   QString getFilename() const { return filename; }
//   void setFilename(const QString& f) { filename=f; }
    void load(); // load notes from file filename
    void save() const; // save notes in file filename
    static NotesManager& getManager();
    static void freeManager(); // free the memory used by the NotesManager; it can be rebuild later






        class ConstIterator {
            friend class NotesManager;
            note** currentA;
            unsigned int nbRemain;
            ConstIterator(note** a, unsigned nb):currentA(a),nbRemain(nb){}
        public:
            ConstIterator():nbRemain(0),currentA(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
//                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentA++;
            }
            const note& current() const {
                if (isDone())
//                    throw NotesException("error, indirection on an iterator which is done");
                return **currentA;
            }
        };
        ConstIterator getIterator() const {
            return ConstIterator(notes,nbNotes);
        }




};


//******SOUS CLASSE ARTICLE /  note avec un texte ******//


class article : public note {
protected :
    std::string texte ; //ce sera un QString après

public :
    article ( const unsigned int i, std::string t,std::string txt)
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
    media ( const unsigned int i, std::string t,std::string d,std::string im)
        : note (i,t) , description (d), image(im){}
    const std::string getDescription()const {return description;}
    const std::string getImage() const {return image;}

// AFFICHER ET MISE A JOUR A METTRE §


};


class tache : public note{// faut ajouter l'optionalité des trucs : constructeur ?

protected :
    std::string action;
    unsigned int priorite;
    std::string echeance; //date ?
    enum etat status;

public :
    const std::string getAction() const {return action;}
    const std::string getecheance() const {return echeance;}
    enum etat getEtat() const  {return status;}
    unsigned int getPriorite() const {return priorite;}


// AFFICHER ET MISE A JOUR A METTRE §
};

#endif // NOTES_H
