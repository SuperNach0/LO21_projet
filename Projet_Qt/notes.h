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


/// Cette classe récupère un string correspondant à une erreur et a pour fonction de l'afficher sur la sortie standard.

class NotesException{
public:
    /// Cette fonction affiche sur la sortie standard l'erreur rencontrée .
    /** lors d'un test(ex :id déjà existant), utiliser un throw puis cette fonction avec le essage d'erreur en paramètre
        @param message : le message à afficher
         @return info : le message à afficher
     */
    NotesException(const std::string& message):info(message){}
    std::string getInfo() const { return info; }
private:
    std::string info;
};




/// Classe mère abstraite des types de notes
/** Cette classe regroupe  les attributs et les méthodes communes aux différents types de notes, ainsi qu'un vector contenant les anciennes versions.
 *  Classe à utiliser lors de l'implémentatuion d'un nouveau type de note.
 * Son but principal est d'éviter la redondance de code.
 *
 */
class note {

protected :
    std::string id;
    std::string titre ;
    std::string Creation ;
    std::string Modif;
    std::string texte;
    std::vector<note*> oldNotes;

public :
    /// Constructeur de notes.
     /** Ce constructeur crée une nouvelle note avec les paramètres fournis.
      * Si crea (date de création) n'est pas renseigné, il s'agit d'une nouvelle note et le constructeur appelle la fonction formatTime() qui récupèrela date et l'heure du système.
      * cette date est donc affectée à la date de création de la note et aussi à la date de dernière modification.
      * Si ces dattes sont fournis, ils sont affectédd aux attributs correspondants.
         @param i id unique de la note
         @param t titre de la note
         @param txt texte décrivant la note
         @param creadate de création de la note
         @param modif date de dernière modification de la note

      */
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


    /// accesseur en lecture de l'id de la note.
    const std::string getID() const {return id;}
        /// accesseur en lecture du titre de la note.
    const std::string getTitre() const {return titre;}
        /// accesseur en lecture de la date de création de la note.
    const std::string getCreation() const {return Creation;}
        /// accesseur en lecture de la date de modification de la note.
    const std::string getModif() const {return Modif;}
        /// accesseur en lecture du texte de la note.
    const std::string getTexte() const {return texte;}
        /// accesseur du vector contennant les anciennes versions de la note.
    std::vector<note*>& getOldNotes() {return oldNotes;}
      /// met à jour le  texte de la note.
    /**
     * @param text le nouveau texte de la note.
     */
    void setTexte(const std::string& text) {texte = text;}
      /// met à jour le titre de la note.
    /**
     * @param titre le nouveau titre de la note.
     */
    void setTitre(const std::string& t) {titre = t;}
     /// fonction virtuelle  qui affiche les attributs de la note sur la sortie standard.
    virtual void afficher(std::ostream& f= std::cout) const ;
        /// fonction mettant à jour la date de modificaton avec l'heure du système
    void setModif () ;
        ///Destructeur de note supprimmant les anciennes versions présentes dans le vector.
   virtual ~note () {
        std::cout<<"suppression de la note "<<std::endl;
        for (unsigned int i=0;i<oldNotes.size();i++)
            delete oldNotes[i];
        oldNotes.clear();
    };


};


/// Classe fille de note.
/** cette classe n'ajoute pas de nouvel attribut car texte est commun à toutes les notes
 */

class article : public note {

public :
       /// constructeur similaire à celui de note.
    /**
     * @param i : id unique de l'article
     * @param t : titre de l'article
     * @param txt : texte décrivant l'article
     * @param crea : date de création de l'article
     * @param modif : date de derniere modification de l'article
     */
    article (  std::string i, std::string t,std::string txt, std::string crea="",std::string modif="")
        : note (i,t,txt,crea,modif){}
     /// constructeur de recopie de article.
    article (const article& article_a_copier);
    /// appelle la fonction afficher() de note (pas d'attribut supplémentaire).
    virtual void afficher(std::ostream& f= std::cout) const;

};

/// Classe fille de note.
/** cette classe est une note possédant un attibut supplémentaire contennant le chemin vers un fichier (texte,image,vidéo...)
 */

class media : public note {

protected :

    std::string chemin ;

public :
    /// constructeur utilisant le constructeur de note en ajoutant l'attribut correspondant au chemin
    /**
     * @param i : id unique du média
     * @param t : titre du média
     * @param txt : texte décrivant le média
     * @param im  : chemin du fichier média
     * @param crea : date de création du média
     * @param modif :date  de derniere modification du média
     */
    media ( const std::string i, std::string t,std::string txt, std::string im ,std::string crea="",std::string modif="" )
        : note (i,t,txt,crea,modif),chemin(im){}
    /// constructeur de recopie
    media(const media& media_a_copier);
    /// accesseur en lecture du chemin du média
    const std::string getChemin() const {return chemin;}
    /// met à jour le chemin du média.
  /**
   * @param text : le nouveau chemin.
   */
    void setChemin(const std::string& text) {chemin = text;}

     /// appelle la fonction afficher() de note et affiche le chemin en plus sur la sortie standard.
    virtual void afficher(std::ostream& f= std::cout) const ;


};
/// Classe fille de note.
/** cette classe est une note possédant une priorité soud forme d'un entier, une date d'échéance et un statut qui peut etre en_attente, en_cours ,terminee.
 */

class tache : public note{

protected :
    unsigned int priorite;
    std::string echeance;
    enum etat status;

public :

    /// constructeur utilisant le constructeur de note en ajoutant les nouveaux attributs.
    /**
     * @param i : id unique de la tâche
     * @param t : titre de la tâche
     * @param txt : texte décrivant la tâche
     * @param p : priorité de la tâche
     * @param e : échéance de la tâche
     * @param Status : l'état actuel de la tâche
     * @param crea : date de création de la tâche
     * @param modif :date  de derniere modification de la tâche
     */
    tache ( const std::string i, std::string t,std::string txt, unsigned int p , std::string e,enum etat Status,std::string crea="",std::string modif="" )
        : note (i,t,txt,crea,modif),priorite(p), echeance (e),status(Status){}
    ///constructeur de recopie
    tache(const tache &tache_a_copier);
     /// accesseur en lecture de l'échéance
    const std::string getecheance() const {return echeance;}
    /// accesseur en lecture du statut
    enum etat getEtat() const  {return status;}
    /// accesseur en lecture de la priorité
    unsigned int getPriorite() const {return priorite;}
    /// met à jour la priorité
  /**
   * @param prio :la nouvelle priorité
   */
    void setPriorite(int prio){priorite=prio;}
    /// met à jour l'échéance
  /**
   * @param date :la nouvelle échéance
   */
    void setEcheance(const std::string& date){echeance=date;}
    /// met à jour le statut
  /**
   * @param stat :le nouveau statut
   */
    void setStatus(enum etat stat){status=stat;}
     /// appelle la fonction afficher() de note et affiche les attribust de tâche sur la sortie standard.
    virtual void afficher(std::ostream& f= std::cout) const ;


};

#endif // NOTES_H
