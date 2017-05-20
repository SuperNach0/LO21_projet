#ifndef NOTES_H
#define NOTES_H
#include <QString>


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

    void afficher(std::ostream& f= std::cout) const;//définie des cpp
    void setModif () ;

    ~note () {std::cout<<"suppression de la note "<<std::endl;};


};


//*******************NOtes manager que j'ai pompé d'un td
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
private :


};




#endif // NOTES_H
