
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
template<class T>
 void Manager<T>:: add (T* a){
    for(unsigned int i=0; i<nb; i++){
        if (type[i]->getID()==a->getID()) throw NotesException("error, creation of an already existent note");
    }
    if (nb==nbMax){
        T** newTab= new note*[nbMax+5];
        for(unsigned int i=0; i<nb; i++) newTab[i]=type[i];
        T** oldNotes=type;
        type=newTab;
        nbMax+=5;
        if (oldNotes) delete[] oldNotes;
    }
    type[nb++]=a;
}



//template<class T>
//Manager<T>::Manager():T (nullptr),nb(0),nbMax(0),filename(""){}

// constructeur de manager


NotesManager::~NotesManager(){
    if (filename!="") save();               // SAVE PAS ENCORE DEFINIE car SAVE en Qt
    for(unsigned int i=0; i<nb; i++) delete type[i];
    delete[] type;
    std::cout<<"le manager est detruit"<<std::endl;
}


NotesManager::Handler NotesManager::handler=Handler();


note& NotesManager::getNote(const std::string& id, const std::string& date){
    // si l'article existe déjà, on en renvoie une référence
    for(unsigned int i=0; i<nb; i++){
        if (type[i]->getID()==id && date=="")
            return *type[i];
        else if (type[i]->getID()==id && date!="")
        {
            unsigned int j =0;
            while (j<type[i]->getOldNotes().size() && type[i]->getOldNotes()[j]->getModif() != date )
                j++;
            return *type[i]->getOldNotes()[j];
        }
    }


    article* vide = new article("","","",""); ///A CORRIGER SI POSSIBLE
    return *vide;

}

note& NotesManager::getOldNote(const std::string& id)
{
    note& version_actuelle=getNote(id);
    for(unsigned int i=0; i<version_actuelle.getOldNotes().size(); i++)
    {
        if (version_actuelle.getOldNotes()[i]->getID()==id) return *version_actuelle.getOldNotes()[i];
    }
    throw NotesException("Version de note non trouvee\n");
}


note& NotesManager::ajArticle(const std::string& id,const std::string& titre,const std::string& txt,const std::string& crea,const std::string& modif){
    article* n=new article(id,titre,txt,crea,modif);
    add (n);
    return *n;
}




note& NotesManager::ajMulti(const std::string& id,const std::string& text,const std::string& description,const std::string& image,const std::string& crea,const std::string& modif){

    media* n=new media(id,text,description,image,crea,modif);
    add (n);
    return *n;
}

note& NotesManager::ajTache(const std::string& id,const std::string& texte, const std::string& action , const unsigned int priorite, const std::string& echeance, enum etat stat,const std::string& crea,const std::string& modif) {
    tache* n=new tache(id,texte,action,priorite,echeance,stat,crea,modif);
    add (n);
    return *n;
}



template <class T>
void Manager<T>::Supprimer (T& toDelete)
{
    int i=0;
    while (type[i]->getID() != toDelete.getID())
    {
        i++;
    }

    for (i;i<nb;i++)
    {
        type[i]=type[i+1];
    }
    nb--;
    delete &toDelete;
}


                                                    // A FAIRE EN Qt PAREIL POUR SAVE
void NotesManager::load() {
    QFile fin(filename);
   // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadWrite | QIODevice::Text)) {
        //throw NotesException("Erreur ouverture fichier notes");
    return (void) 0;
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
                NotesManager::ajArticle(identificateur.toStdString(),titre.toStdString(),text.toStdString(),creation.toStdString(),modif.toStdString());

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
                NotesManager::ajMulti(identificateur.toStdString(),titre.toStdString(),text.toStdString(),path.toStdString(),
                                         creation.toStdString(),modif.toStdString());

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


                NotesManager::ajTache(identificateur.toStdString(),titre.toStdString(),text.toStdString(),
                                       priorite,echeance.toStdString(),state,
                                       creation.toStdString(),modif.toStdString());

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




void NotesManager::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException("erreur sauvegarde notes : ouverture fichier xml");
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for(NotesManager::ConstIterator it= this->getIterator(); !it.isDone(); it.next())
    {
            std::cout<<typeid(it.current()).name()<<std::endl;
        if (typeid(it.current())==typeid(article)) {// ATRICLE

        stream.writeStartElement("article");
        stream.writeTextElement("id",QString::fromStdString(it.current().getID()));
        stream.writeTextElement("titre",QString::fromStdString(it.current().getTitre()));
         stream.writeTextElement("creation",QString::fromStdString(it.current().getCreation()));
          stream.writeTextElement("modif",QString::fromStdString(it.current().getModif()));
          stream.writeTextElement("texte",QString::fromStdString(it.current().getTexte()));




        stream.writeEndElement();
        }

        else if (typeid(it.current())==typeid(media)) {
            stream.writeStartElement("media");
            stream.writeTextElement("id",QString::fromStdString(it.current().getID()));
            stream.writeTextElement("titre",QString::fromStdString(it.current().getTitre()));
             stream.writeTextElement("creation",QString::fromStdString(it.current().getCreation()));
              stream.writeTextElement("modif",QString::fromStdString(it.current().getModif()));
              stream.writeTextElement("texte",QString::fromStdString(it.current().getTexte()));
          const media& med = static_cast<const media&>(it.current());
          stream.writeTextElement("chemin",QString::fromStdString(med.getChemin()));


            stream.writeEndElement();
        }

         else if (typeid(it.current())==typeid(tache)) {
            stream.writeStartElement("tache");
            stream.writeTextElement("id",QString::fromStdString(it.current().getID()));
            stream.writeTextElement("titre",QString::fromStdString(it.current().getTitre()));
             stream.writeTextElement("creation",QString::fromStdString(it.current().getCreation()));
             stream.writeTextElement("modif",QString::fromStdString(it.current().getModif()));
           stream.writeTextElement("texte",QString::fromStdString(it.current().getTexte()));
           const tache& task = static_cast<const tache&>(it.current());
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

NotesManager& NotesManager::getManager(){
    if (!handler.instance) handler.instance=new NotesManager;
    return *handler.instance;
}

void NotesManager::freeManager(){
    delete handler.instance;
    handler.instance=nullptr;
}


