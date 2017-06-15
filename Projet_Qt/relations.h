#ifndef RELATIONS_H
#define RELATIONS_H

#include "notes.h"

/// Classe définissant les couples.
/**  Possède en attributs deux pointeurs sur les notes composant le couple, un label et
 *  un booleen qui détermine si la relation est orientée ou non.
 *
 */
class Couple
{
private:
    note* premiere;
    note* seconde;
    std::string label;
    bool orientation;
public:

    /// Constructeur de couple.
     /**
      *   @param note1 : référence sur la première note
      *   @param note2 : référence sur la seconde note
      *   @param label : du couple
      *   @param orientation : (0 :non, 1: Oui)
      */
    Couple(note& note1, note& note2, std::string lab, bool ori):premiere(&note1),seconde(&note2),label(lab),orientation(ori){}
     /// accesseur en lecture retournant une référence sur la première note du couple.
    const note& getPremiere() const {return *premiere;}
    /// accesseur en lecture retournant une référence sur la seconde note du couple.
    const note& getSeconde() const {return *seconde;}
    /// accesseur en lecture du label du couple.
    const std::string getLabel() const {return label;}
    ///accesseur en lecture de l'orientation du couple.
    bool isOriented() const {return orientation;}

};

/// Classe définissant les relations.
/**  Elle possède un attribut vector<Couple*> qui contient les couples appartenant à la relation,
 *  un titre pour la relation,
 *  une description.
 *
 */
class Relation
{
private:

    std::vector<Couple*> couples;
    std::string titre;
    std::string description;

public:
    /// Constructeur de relation. initialise une relation avec un titre, une description, et initialise le vector vide.
     /**
      *   @param tit : référence sur la première note
      *   @param desc : référence sur la seconde note
      */
    Relation(const std::string& tit, const std::string& desc) : couples(0),titre(tit),description(desc){}
    ///Ajoute un couple à la relation
    /**
     *   @param couple : référence sur le couple à ajouter.
     *
     */
    void addCouple(Couple& couple){couples.push_back(&couple);}
    /// accesseur du vector contennant les couples de la relation.
    std::vector<Couple*>& getCouples(){return couples;}
    /// accesseur en lecture du titre de la relation.
    const std::string& getTitre() const {return titre;}
    /// accesseur en lecture de la decription de la relation.
    const std::string& getDescription() const {return description;}
    /// met à jour la description de la relation.
  /**
   * @param desc : la nouvelle description de la relation.
   */
    void setDescription(std::string desc){description=desc;}

};




#endif // RELATIONS_H
