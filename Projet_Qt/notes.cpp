#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>

#include<QApplication>
#include<QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <time.h>
#include "notes.h"
#include "manager.h"
#include "relations.h"
std::string etatToString(enum etat s)
{
    switch (s)
    {
        case 0:
            return "En attente";
            break;
        case 1:
            return "En cours";
            break;
        case 2:
            return "Terminee";
            break;
    }
}

/*********************fonctions de note************/

void note :: afficher(std::ostream& f ) const {
    f<<"id: "<<getID() << std::endl;
    f<<"titre:"<<getTitre() << std::endl;
    f<<"Texte:"<<getTexte() << std::endl;
    f<<"date creation:"<<getCreation() << std::endl;
    f <<"date modif:"<< getModif()<<std::endl;

}



//**********************fonction qui récupere lheure du système************************/

std::string formatTime (){

        char tmps[32];
        time_t _time;
        struct tm timeInfo;
        time(&_time);
        localtime_s(&timeInfo, &_time);

    strftime(tmps, 32, "%Y-%m-%d %H:%M:%S", &timeInfo);
    std::string temps = tmps;
return temps;
}
//**********************



/**************************MANAGER************/


void NotesManager2::addNote(note &note_a_ajouter)
{
    for (unsigned int i = 0; i < notes.size(); i++)
    {
        if (notes[i]->getID()==note_a_ajouter.getID())
            throw NotesException("Erreur, note deja existante\n");
    }

    notes.push_back(&note_a_ajouter);
}


NotesManager2::NotesManager2():notes(0),filename(""){

} // constructeur de manager


NotesManager2::~NotesManager2(){
if (filename!="") save();
for (unsigned int i = 0; i < notes.size(); i++)
{
    delete notes[i];
}
notes.clear();
std::cout<<"le manager est detruit"<<std::endl;
}


NotesManager2::Handler NotesManager2::handler=Handler();


note& NotesManager2::getNote(const std::string& id, const std::string& date){
    // si l'article existe déjà, on en renvoie une référence, sinon on lance une exception
    for(unsigned int i=0; i<notes.size(); i++){
        if (notes[i]->getID()==id && date=="")
            return *notes[i];
        else if (notes[i]->getID()==id && date!="")
        {
            unsigned int j =0;
            while (j<notes[i]->getOldNotes().size() && notes[i]->getOldNotes()[j]->getModif() != date )
                j++;
            return *notes[i]->getOldNotes()[j];
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


void NotesManager2::SupprimerNote (note& toDelete, const std::string& date)
{
    unsigned int i=0;
    while (notes[i]->getID() != toDelete.getID() && i<notes.size()) //on recherche la note concernée
    {
        i++;
    }
    if (i==notes.size())
    {
        throw NotesException("Suppression impossible, note non trouvee\n");
        return;
    }
    if (date=="")
    {
        notes.erase(notes.begin()+i);
        toDelete.getOldNotes().clear();
        delete &toDelete;
    }
    //on cherche la version de la note concernée
    else //si la date n'est pas vide, on cherche à supprimer une ancienne version
    {
        unsigned int j=0;
        while (notes[i]->getOldNotes()[j]->getModif() != date && j<notes[i]->getOldNotes().size())
            j++;
        notes[i]->getOldNotes()[j]->getOldNotes().clear();

        notes[i]->getOldNotes().erase(notes[i]->getOldNotes().begin()+j);
    }
}


                                                // A FAIRE EN Qt PAREIL POUR SAVE
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
        // If it's named taches, we'll go to the next.
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
            NotesManager2::addNote(*nouveau);
        }

      else  if(xml.name() == "media") {// µ**********************************************MEDIAA
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
            NotesManager2::addNote(*nouveau);

           // NotesManager2::ajMulti(identificateur.toStdString(),titre.toStdString(),text.toStdString(),path.toStdString(),
             //                        creation.toStdString(),modif.toStdString());

        }


        else if (xml.name()=="tache"){// **********************************************TACHE

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
            NotesManager2::addNote(*nouveau);

            /*
            NotesManager2::ajTache(identificateur.toStdString(),titre.toStdString(),text.toStdString(),
                                   priorite,echeance.toStdString(),state,
                                   creation.toStdString(),modif.toStdString());
                                   */


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
QFile newfile(filename);
if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
    throw NotesException("erreur sauvegarde notes : ouverture fichier xml");
QXmlStreamWriter stream(&newfile);
stream.setAutoFormatting(true);
stream.writeStartDocument();
stream.writeStartElement("notes");

for (unsigned int i = 0; i<getNotes().size();i++)
{
    if (typeid(*getNotes()[i])==typeid(article)) {// ATRICLE
    stream.writeStartElement("article");
    stream.writeTextElement("id",QString::fromStdString((getNotes()[i])->getID()));
    stream.writeTextElement("titre",QString::fromStdString((getNotes()[i])->getTitre()));
     stream.writeTextElement("creation",QString::fromStdString((getNotes()[i])->getCreation()));
      stream.writeTextElement("modif",QString::fromStdString((getNotes()[i])->getModif()));
      stream.writeTextElement("texte",QString::fromStdString((getNotes()[i])->getTexte()));


    stream.writeEndElement();
    }

    else if (typeid(*getNotes()[i])==typeid(media)) {
        stream.writeStartElement("media");
        stream.writeTextElement("id",QString::fromStdString((getNotes()[i])->getID()));
        stream.writeTextElement("titre",QString::fromStdString((getNotes()[i])->getTitre()));
         stream.writeTextElement("creation",QString::fromStdString((getNotes()[i])->getCreation()));
          stream.writeTextElement("modif",QString::fromStdString((getNotes()[i])->getModif()));
          stream.writeTextElement("texte",QString::fromStdString((getNotes()[i])->getTexte()));
      const media& med = static_cast<const media&>(*getNotes()[i]);
      stream.writeTextElement("chemin",QString::fromStdString(med.getChemin()));


        stream.writeEndElement();
    }

     else if (typeid(*getNotes()[i])==typeid(tache)) {
        stream.writeStartElement("tache");
        stream.writeTextElement("id",QString::fromStdString((getNotes()[i])->getID()));
        stream.writeTextElement("titre",QString::fromStdString((getNotes()[i])->getTitre()));
         stream.writeTextElement("creation",QString::fromStdString((getNotes()[i])->getCreation()));
         stream.writeTextElement("modif",QString::fromStdString((getNotes()[i])->getModif()));
       stream.writeTextElement("texte",QString::fromStdString((getNotes()[i])->getTexte()));
       const tache& task = static_cast<const tache&>(*getNotes()[i]);
       stream.writeTextElement("echeance",QString::fromStdString(task.getecheance()));
       stream.writeTextElement("priorite",QString::number(task.getPriorite()));
        stream.writeTextElement("status",QString::fromStdString(etatToString(task.getEtat())));

        stream.writeEndElement();

    }
}
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


//********************************fin manager***********/



void note::setModif () {
    this->Modif = formatTime();
}

//***********fonction de article

//constructeur de recopie
article::article(const article &article_a_copier) : note(article_a_copier.id,article_a_copier.titre,article_a_copier.texte)
{
    oldNotes.clear();
}

 void article ::afficher(std::ostream& f) const {

     f<<"*** Article ***" << std::endl;
     note::afficher();
     f<< "texte="<<getTexte() << std::endl;

}


//************************fonction de media****************


 void media :: afficher(std::ostream& f) const {
     f<<"***Media***" << std::endl;
     note::afficher();
     f <<" chemin ="<<chemin<<std::endl<<std::endl;
     }

 //constructeur de recopie
 media::media(const media &media_a_copier) : note(media_a_copier.id,media_a_copier.titre,media_a_copier.texte)
 {
     chemin = media_a_copier.chemin;
     oldNotes.clear();
 }

 //*****************************fonctions de taches ***************

  void tache :: afficher(std::ostream& f ) const {
      f<< "*** Tache ***"<<"\n";

      note::afficher();
      f<<" priorite :"<< priorite << " echeance : "<< echeance<<" etat = "<<status <<std::endl<<std::endl;

  }

 tache::tache(const tache &tache_a_copier) : note(tache_a_copier.id,tache_a_copier.titre,tache_a_copier.texte)
 {
     echeance=tache_a_copier.echeance;
     priorite=tache_a_copier.priorite;
     status=tache_a_copier.status;
     oldNotes.clear();
 }

 ///Vérifie si la note_a_analyser contient des références vers d'autres notes, et ajoute les relations dans le cas échéant
 void NotesManager2::checkReferences() const
 {
     RelationManager& rm = RelationManager::getManager();
     NotesManager2& nm = NotesManager2::getManager();

     //Suppression des couples correspondant à la note dans la relation References
     Relation& rel_references = rm.getRelation("References");
     rel_references.getCouples().clear();

     for (unsigned int i=0;i<nm.getNotes().size();i++)
     {

         std::string texte = nm.getNotes()[i]->getTexte() + nm.getNotes()[i]->getTitre(); //On récupère le texte de la note à analyser

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
             rel_references.addCouple(*(new Couple(*nm.getNotes()[i],
                                                                 nm.getNote(id_texte),
                                                                 "Ref de " + nm.getNotes()[i]->getID() + " vers " + nm.getNote(id_texte).getID(),
                                                                 1)));


             position_debut_texte = texte.find("\\ref{",position_fin_texte);
             position_fin_texte = texte.find("}",position_debut_texte);

         }

     }
    return;
 }
