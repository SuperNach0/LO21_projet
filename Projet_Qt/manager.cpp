
#include <QFile>
#include <QTextCodec>
#include <QtXml>

#include <iostream>
#include <time.h>
#include "notes.h"
#include "manager.h"
#include "relations.h"

template <class T>
void Manager<T>::add(T &a_ajouter)
{
    for (unsigned int i = 0; i < objets.size(); i++)
    {
        if (objets[i]->getID()==a_ajouter.getID())
            throw NotesException("Erreur, note deja existante\n");
    }
    objets.push_back(&a_ajouter);
}


NotesManager2::NotesManager2()
{

} // constructeur de manager


NotesManager2::~NotesManager2(){
 save();
for (unsigned int i = 0; i < objets.size(); i++)
{
    delete objets[i];
}
objets.clear();
std::cout<<"le manager est detruit"<<std::endl;
}


NotesManager2::Handler NotesManager2::handler=Handler();


note& NotesManager2::getNote(const std::string& id, const std::string& date){
    // si l'article existe déjà, on en renvoie une référence, sinon on lance une exception
    for(unsigned int i=0; i<objets.size(); i++){
        if (objets[i]->getID()==id && date=="")
            return *objets[i];
        else if (objets[i]->getID()==id && date!="")
        {
            unsigned int j =0;
            while (j<objets[i]->getOldNotes().size() && objets[i]->getOldNotes()[j]->getModif() != date )
                j++;
            return *objets[i]->getOldNotes()[j];
        }
    }

    throw NotesException("La note n'existe pas\n");
}


note& NotesManager2::getOldNote(const std::string& id)
{
note& version_actuelle=getNote(id);
for(unsigned int i=0; i<version_actuelle.getOldNotes().size(); i++)
{
    if (version_actuelle.getOldNotes()[i]->getID()==id) return *version_actuelle.getOldNotes()[i];
}
throw NotesException("Version de note non trouvee\n");
}

template <class T>
void Manager<T>::Supprimer (T& toDelete)
{
    unsigned int i=0;
    while (objets[i]->getID() != toDelete.getID())
    {
        i++;
    }
    objets.erase(objets.begin()+i);
    toDelete.getOldNotes().clear();

    //Suppression des couples ou la note est impliquée
    /*
    for (unsigned int i=0;i<objets.size();i++)
    {
        if (objets[i]->getID == toDelete)
    }*/

    delete &toDelete;

}




void NotesManager2::load() {
QFile fin(filename);
// If we can't open it, let's show an error message.
if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
throw NotesException("Erreur ouverture fichier notes");
}
// QXmlStreamReader takes any QIODevice.
QXmlStreamReader xml(&fin);
//qDebug()<<"debut fichier\n";
// We'll parse the XML until we reach end of it.
while(!xml.atEnd() && !xml.hasError()) {
// Read next element.
QXmlStreamReader::TokenType token = xml.readNext();
// If token is just StartDocument, we'll go to next.
if(token == QXmlStreamReader::StartDocument) continue;
// If token is StartElement, we'll see if we can read it.
if(token == QXmlStreamReader::StartElement) {
// If it's named notes, we'll go to the next.
if(xml.name() == "notes") continue;
// If it's named tache, we'll dig the information from there.
if(xml.name() == "article") {// µ**********************************************ARTICLE
qDebug()<<"new article\n";
QString identificateur;
QString titre;
QString creation;
QString modif;
QString text;
QXmlStreamAttributes attributes = xml.attributes();
xml.readNext();
//We're going to loop over the things because the order might change.
//We'll continue the loop until we hit an EndElement named article.
while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
if(xml.tokenType() == QXmlStreamReader::StartElement) {
// We've found identificteur.
if(xml.name() == "id") {
xml.readNext(); identificateur=xml.text().toString();
qDebug()<<"id="<<identificateur<<"\n";
}

// We've found titre.
if(xml.name() == "titre") {
xml.readNext(); titre=xml.text().toString();
qDebug()<<"titre="<<titre<<"\n";
}
// We've found creation
if(xml.name() == "creation") {
xml.readNext();
creation=xml.text().toString();
qDebug()<<"creation="<<creation<<"\n";
}
// We've found modif
if(xml.name() == "modif") {
xml.readNext();
modif=xml.text().toString();
qDebug()<<"modif="<<modif<<"\n";
}
// We've found text
if(xml.name() == "texte") {
xml.readNext();
text=xml.text().toString();
qDebug()<<"texte="<<text<<"\n";
}
}
// ...and next...
xml.readNext();
}
qDebug()<<"ajout note "<<identificateur<<"\n";
article* nouveau = new article(identificateur.toStdString(),titre.toStdString(),text.toStdString(),creation.toStdString(),modif.toStdString());
//NotesManager2::ajArticle(identificateur.toStdString(),titre.toStdString(),text.toStdString(),creation.toStdString(),modif.toStdString());
NotesManager2::add(*nouveau);
}

if(xml.name() == "media") {// µ**********************************************MEDIAA
qDebug()<<"new media\n";
QString identificateur;
QString titre;
QString creation;
QString modif;
QString text;
QString path;
QXmlStreamAttributes attributes = xml.attributes();
xml.readNext();
//We're going to loop over the things because the order might change.
//We'll continue the loop until we hit an EndElement named article.
while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "media")) {
if(xml.tokenType() == QXmlStreamReader::StartElement) {
// We've found identificteur.
if(xml.name() == "id") {
xml.readNext(); identificateur=xml.text().toString();
qDebug()<<"id="<<identificateur<<"\n";
}

// We've found titre.
if(xml.name() == "titre") {
xml.readNext(); titre=xml.text().toString();
qDebug()<<"titre="<<titre<<"\n";
}
// We've found creation
if(xml.name() == "creation") {
xml.readNext();
creation=xml.text().toString();
qDebug()<<"creation="<<creation<<"\n";
}
// We've found modif
if(xml.name() == "modif") {
xml.readNext();
modif=xml.text().toString();
qDebug()<<"modif="<<modif<<"\n";
}
// We've found text
if(xml.name() == "texte") {
xml.readNext();
text=xml.text().toString();
qDebug()<<"texte="<<text<<"\n";
}
// We've found path
if(xml.name() == "chemin") {
xml.readNext();
path=xml.text().toString();
qDebug()<<"chemin="<<path<<"\n";
}
}
// ...and next...
xml.readNext();
}
qDebug()<<"ajout note "<<identificateur<<"\n";
media* nouveau = new media(identificateur.toStdString(),titre.toStdString(),text.toStdString(),path.toStdString(),
creation.toStdString(),modif.toStdString());
NotesManager2::add(*nouveau);

// NotesManager2::ajMulti(identificateur.toStdString(),titre.toStdString(),text.toStdString(),path.toStdString(),
//                        creation.toStdString(),modif.toStdString());

}





if (xml.name()=="tache"){// **********************************************TACHE

qDebug()<<"new tache\n";
QString identificateur;
QString titre;
QString creation;
QString modif;
QString text;
int  priorite;
QString echeance;
QString status;
enum etat state;

QXmlStreamAttributes attributes = xml.attributes();
xml.readNext();
//We're going to loop over the things because the order might change.
//We'll continue the loop until we hit an EndElement named article.
while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
if(xml.tokenType() == QXmlStreamReader::StartElement) {
// We've found identificteur.
if(xml.name() == "id") {
xml.readNext(); identificateur=xml.text().toString();
qDebug()<<"id="<<identificateur<<"\n";
}

// We've found titre.
if(xml.name() == "titre") {
xml.readNext(); titre=xml.text().toString();
qDebug()<<"titre="<<titre<<"\n";
}
// We've found creation
if(xml.name() == "creation") {
xml.readNext();
creation=xml.text().toString();
qDebug()<<"creation="<<creation<<"\n";
}
// We've found modif
if(xml.name() == "modif") {
xml.readNext();
modif=xml.text().toString();
qDebug()<<"modif="<<modif<<"\n";
}
// We've found text
if(xml.name() == "texte") {
xml.readNext();
text=xml.text().toString();
qDebug()<<"texte="<<text<<"\n";
}
// We've found echeance
if(xml.name() == "echeance") {
xml.readNext();
echeance=xml.text().toString();
qDebug()<<"echeance="<<echeance<<"\n";
}
// We've found priorite
if(xml.name() == "priorite") {
xml.readNext();
priorite=xml.text().toInt();
qDebug()<<"priorite="<<priorite<<"\n";
}
//We've found statu
if(xml.name() == "status") {
xml.readNext();
status=xml.text().toString();
qDebug()<<"status="<<status<<"\n";


if (status=="En attente") state=en_attente;
else if (status=="En cours") state=en_cours;
else if (status=="Terminee") state=terminee;

}
}
// ...and next...
xml.readNext();
}
qDebug()<<"ajout note "<<identificateur<<"\n";

tache* nouveau = new tache(identificateur.toStdString(),titre.toStdString(),text.toStdString(),
priorite,echeance.toStdString(),state,
creation.toStdString(),modif.toStdString());
NotesManager2::add(*nouveau);
}
if(xml.name() == "relations"){std::cout<<"on a atteind les relations"<<std::endl; continue;}


if(xml.name() == "relation") {// µ**********************************************RELATION
qDebug()<<"new relation\n";
QString titre;
QString description;
std::vector<Couple*> couplees;

QXmlStreamAttributes attributes = xml.attributes();
xml.readNext();
//We're going to loop over the things because the order might change.
//We'll continue the loop until we hit an EndElement named article.
while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "relation")) {
    if(xml.tokenType() == QXmlStreamReader::StartElement) {
    // We've found identificteur.
    if(xml.name() == "titre") {
    xml.readNext(); titre=xml.text().toString();
    qDebug()<<"titre="<<titre<<"\n";
    }

    // We've found titre.
    if(xml.name() == "description") {
    xml.readNext(); description=xml.text().toString();
    qDebug()<<"description="<<description<<"\n";

    }





     if(xml.name() == "couple"){ qDebug()<<"dans un couple\n";
                                 QString premiere;
                                 QString seconde;
                                 QString label;
                                 QString orientation;
                                 bool ori;

                                 QXmlStreamAttributes attributes = xml.attributes();
                                 xml.readNext();
                                 while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "couple")) {
                                     if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                         // We've found identificteur.
                                         if(xml.name() == "premiere") {
                                             xml.readNext(); premiere=xml.text().toString();
                                             qDebug()<<"premiere="<<premiere<<"\n";
                                         }
                                         if(xml.name() == "seconde") {
                                             xml.readNext(); seconde=xml.text().toString();
                                             qDebug()<<"seconde="<<seconde<<"\n";
                                         }
                                         if(xml.name() == "label") {
                                             xml.readNext(); label=xml.text().toString();
                                             qDebug()<<"label="<<label<<"\n";
                                         }
                                         if(xml.name() == "orientation") {
                                             xml.readNext(); orientation=xml.text().toString();

                                             qDebug()<<"orientation="<<orientation<<"\n";
                                             if (orientation.toStdString()=="true") {ori =  1;std::cout<<ori<<std::endl;}
                                             else {ori =  0;std::cout<<ori<<std::endl;}
                                         }
                                 }
                               // ...and next...
                                xml.readNext();

                                 }
                                 NotesManager2  &m1 = NotesManager2::getManager();
                                 Couple* nouv = new Couple (m1.getNote(premiere.toStdString()),m1.getNote(seconde.toStdString()),label.toStdString(),ori);
                                 couplees.push_back(nouv);

    }

            }
// ...and next...
xml.readNext();
}
RelationManager& m2 = RelationManager::getManager();
Relation* nouvo = new Relation (titre.toStdString(),description.toStdString());
for (unsigned int k = 0; k<couplees.size();k++) {nouvo->addCouple(*couplees[k]);}
m2.addRelation(*nouvo);





}

}
}

// Error handling.
if(xml.hasError()) {
throw NotesException("Erreur lecteur fichier notes, parser xml");
}
// Removes any device() or data from the reader * and resets its internal state to the initial state.
xml.clear();
qDebug()<<"fin load\n";
}


void NotesManager2::save(){
RelationManager &m2 = RelationManager::getManager();

QFile newfile(filename);
if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
    throw NotesException("erreur sauvegarde notes : ouverture fichier xml");
QXmlStreamWriter stream(&newfile);
stream.setAutoFormatting(true);
stream.writeStartDocument();
stream.writeStartElement("sauvegarde");
stream.writeStartElement("notes");

for (unsigned int i = 0; i<getobjets().size();i++)
{
    if (typeid(*getobjets()[i])==typeid(article)) {// ATRICLE
    stream.writeStartElement("article");
    stream.writeTextElement("id",QString::fromStdString((getobjets()[i])->getID()));
    stream.writeTextElement("titre",QString::fromStdString((getobjets()[i])->getTitre()));
     stream.writeTextElement("creation",QString::fromStdString((getobjets()[i])->getCreation()));
      stream.writeTextElement("modif",QString::fromStdString((getobjets()[i])->getModif()));
      stream.writeTextElement("texte",QString::fromStdString((getobjets()[i])->getTexte()));


    stream.writeEndElement();
    }

    else if (typeid(*getobjets()[i])==typeid(media)) {
        stream.writeStartElement("media");
        stream.writeTextElement("id",QString::fromStdString((getobjets()[i])->getID()));
        stream.writeTextElement("titre",QString::fromStdString((getobjets()[i])->getTitre()));
         stream.writeTextElement("creation",QString::fromStdString((getobjets()[i])->getCreation()));
          stream.writeTextElement("modif",QString::fromStdString((getobjets()[i])->getModif()));
          stream.writeTextElement("texte",QString::fromStdString((getobjets()[i])->getTexte()));
      const media& med = static_cast<const media&>(*getobjets()[i]);
      stream.writeTextElement("chemin",QString::fromStdString(med.getChemin()));


        stream.writeEndElement();
    }

     else if (typeid(*getobjets()[i])==typeid(tache)) {
        stream.writeStartElement("tache");
        stream.writeTextElement("id",QString::fromStdString((getobjets()[i])->getID()));
        stream.writeTextElement("titre",QString::fromStdString((getobjets()[i])->getTitre()));
         stream.writeTextElement("creation",QString::fromStdString((getobjets()[i])->getCreation()));
         stream.writeTextElement("modif",QString::fromStdString((getobjets()[i])->getModif()));
       stream.writeTextElement("texte",QString::fromStdString((getobjets()[i])->getTexte()));
       const tache& task = static_cast<const tache&>(*getobjets()[i]);
       stream.writeTextElement("echeance",QString::fromStdString(task.getecheance()));
       stream.writeTextElement("priorite",QString::number(task.getPriorite()));
        stream.writeTextElement("status",QString::fromStdString(etatToString(task.getEtat())));

        stream.writeEndElement();

    }
}
stream.writeEndElement();
stream.writeStartElement("relations");
for (unsigned int i = 0; i<m2.getobjets().size();i++)
{

    stream.writeStartElement("relation");
    stream.writeTextElement("titre",QString::fromStdString((m2.getobjets()[i])->getTitre()));
     stream.writeTextElement("description",QString::fromStdString((m2.getobjets()[i])->getDescription()));


        for (unsigned int j = 0; j<m2.getobjets()[i]->getCouples().size();j++) {
           stream.writeStartElement("couple");
             stream.writeTextElement("premiere",QString::fromStdString((m2.getobjets()[i]->getCouples()[j]->getPremiere().getID())));
              stream.writeTextElement("seconde",QString::fromStdString((m2.getobjets()[i]->getCouples()[j]->getSeconde().getID())));
               stream.writeTextElement("label",QString::fromStdString(m2.getobjets()[i]->getCouples()[j]->getLabel()));
               if(m2.getobjets()[i]->getCouples()[j]->isOriented())
                stream.writeTextElement("orientation","true");
               else  stream.writeTextElement("orientation","false");
          stream.writeEndElement();
        }




    stream.writeEndElement();
  }

stream.writeEndElement();
stream.writeEndElement();
stream.writeEndDocument();
newfile.close();
}


NotesManager2& NotesManager2::getManager(){
if (!handler.instance) handler.instance=new NotesManager2;
return *handler.instance;
}

void NotesManager2::freeManager(){
delete handler.instance;
handler.instance=nullptr;
}

void NotesManager2::SupprimerNote (note& toDelete, const std::string& date)
{
    unsigned int i=0;
    while (objets[i]->getID() != toDelete.getID() && i<objets.size()) //on recherche la note concernée
    {
        i++;
    }
    if (i==objets.size())
    {
        throw NotesException("Suppression impossible, note non trouvee\n");
        return;
    }
    if (date=="")
    {
        objets.erase(objets.begin()+i);
        toDelete.getOldNotes().clear();

        //Suppression des couples ou la note est présente
        RelationManager& rm = RelationManager::getManager();
        for (unsigned int i=0;i<rm.getobjets().size();i++)    //on parcourt les relations
        {
            for (unsigned int j=0;j<rm.getobjets()[i]->getCouples().size();j++)   //on parcourt les couples
            {
                //Si l'une des notes du couple a le même id que la note a supprimer, on supprime ce couple

                if (rm.getobjets()[i]->getCouples()[j]->getPremiere().getID()==toDelete.getID() ||
                        rm.getobjets()[i]->getCouples()[j]->getSeconde().getID()==toDelete.getID())
                {
                    rm.getobjets()[i]->getCouples().erase(rm.getobjets()[i]->getCouples().begin()+j);
                    j--;    //si on effectue une suppression, j ne change pas car la taille du vector diminue
                }

            }
        }

        delete &toDelete;
    }
    //on cherche la version de la note concernée
    else //si la date n'est pas vide, on cherche à supprimer une ancienne version
    {
        unsigned int j=0;
        while (objets[i]->getOldNotes()[j]->getModif() != date && j<objets[i]->getOldNotes().size())
            j++;
        objets[i]->getOldNotes()[j]->getOldNotes().clear();

        objets[i]->getOldNotes().erase(objets[i]->getOldNotes().begin()+j);
    }
}


///Vérifie si la note_a_analyser contient des références vers d'autres notes, et ajoute les relations dans le cas échéant
void NotesManager2::checkReferences() const
{
    RelationManager& rm = RelationManager::getManager();
    NotesManager2& nm = NotesManager2::getManager();
    Relation* test_rel_reference;
    try
    {
           test_rel_reference = &(rm.getRelation("References"));
           std::cout << "References deja existante\n";
    }
    catch(NotesException& exception)
    {
        std::cout << "References n'existait pas, creation \n";
        test_rel_reference = (new Relation("References","Contient toutes les références entre notes"));
        rm.addRelation(*test_rel_reference);
    }
    Relation& rel_references = *test_rel_reference;
    //Suppression des couples correspondant à la note dans la relation References
        rel_references.getCouples().clear();

    for (unsigned int i=0;i<nm.getobjets().size();i++)
    {

        std::string texte = nm.getobjets ()[i]->getTexte() + nm.getobjets()[i]->getTitre(); //On récupère le texte de la note à analyser

        int position_debut_texte = texte.find("\\ref{");
        int position_fin_texte = texte.find("}",position_debut_texte);


        std::string id_texte =""; //contiendra l'id de la note courante


        while ((position_debut_texte != std::string::npos && position_fin_texte != std::string::npos))
        {
            std::cout << "TROUVE : " << std::endl;
            id_texte = texte.substr(position_debut_texte+5,position_fin_texte-position_debut_texte-5) ;
            std::cout << id_texte << std::endl;

            try{
            nm.getNote(id_texte);

           } catch (NotesException& excep)
            {
                std::cout << "Note non trouvee dans checkRef\n";
                std::cout << excep.getInfo();
                QMessageBox msgBox;
                msgBox.setText("Un ou plusieurs identifiants référencés ne sont pas valides, veuillez les corriger");
                msgBox.exec();
                return;
            }

            //ajout de la relation
            rel_references.addCouple(*(new Couple(*nm.getobjets()[i],
                                                                nm.getNote(id_texte),
                                                                "Ref de " + nm.getobjets()[i]->getID() + " vers " + nm.getNote(id_texte).getID(),
                                                                1)));


            position_debut_texte = texte.find("\\ref{",position_fin_texte);
            position_fin_texte = texte.find("}",position_debut_texte);

        }

    }
   return;
}
//********************************fin manager***********/
