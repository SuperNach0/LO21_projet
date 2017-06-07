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

/*
std::ostream& operator<<(std::ostream& f, const note& n)
{
    f<<"id: "<<n.getID() << std::endl;
    f<<"titre:"<<n.getTitre() << std::endl;
    f<<"date creation:"<<n.getCreation() << std::endl;
    f <<"date modif:"<< n.getModif()<<std::endl;
    return f;
}

std::ostream& operator<<(std::ostream& f, article const& article_a_afficher)
{
    f << "cote la mif\n";
    return f;
}
*/
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

    strftime(tmps, 32, "%Y-%m-%d %H:%M", &timeInfo);
    std::string temps = tmps;
return temps;
}
//**********************

////**************************MANAGER*********/
///



void NotesManager2::addNote(note* n){
    for(unsigned int i=0; i<nbNote; i++){
        if (Note[i]->getID()==n->getID()) throw NotesException("error, creation of an already existent note");
    }
    if (nbNote==nbMaxNote){
        note** newNotes= new note*[nbMaxNote+5];
        for(unsigned int i=0; i<nbNote; i++) newNotes[i]=Note[i];
        note** oldNotes=Note;
        Note=newNotes;
        nbMaxNote+=5;
        if (oldNotes) delete[] oldNotes;
    }
    Note[nbNote++]=n;
}




NotesManager2::NotesManager2():Note (nullptr),nbNote(0),nbMaxNote(0),filename(""){

} // constructeur de manager


NotesManager2::~NotesManager2(){
    if (filename!="") save();               // SAVE PAS ENCORE DEFINIE car SAVE en Qt
    for(unsigned int i=0; i<nbNote; i++) delete Note[i];
    delete[] Note;
    std::cout<<"le manager est detruit"<<std::endl;
}


NotesManager2::Handler NotesManager2::handler=Handler();


note& NotesManager2::getNote(const std::string& id){
    // si l'article existe déjà, on en renvoie une référence
    for(unsigned int i=0; i<nbNote; i++){
        if (Note[i]->getID()==id) return *Note[i];}
    //throw NotesException("Note non trouvee\n");
    article* vide = new article("","",""); ///A CORRIGER SI POSSIBLE
    return *vide;

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


note& NotesManager2::ajArticle(const std::string& id,const std::string& txt){
    article* n=new article(id,"",txt);
    addNote (n);
    return *n;
}
note& NotesManager2::ajMulti(const std::string& id,const std::string& description,const std::string& image){

    media* n=new media(id,"",description,image);
    addNote (n);
    return *n;
}

note& NotesManager2::ajTache(const std::string& id, const std::string& action , const unsigned int priorite, const std::string& echeance, enum etat stat) {
    tache* n=new tache(id,"",action,priorite,echeance,stat);
    addNote (n);
    return *n;
}
/*
void NotesManager2::SupprimerNote (note& toDelete) {
    unsigned int i =0;
    note** newNotes= new note*[nbMaxNote];
    for (i;i<nbNote;i++)
    {
        if (Note[i]->getID()!=toDelete.getID()){
            newNotes [i] = Note[i];

        }else break;
    }

    i++;
    for (i;i<nbNote;i++)
    {
       newNotes [i-1] = Note[i];
    }

    delete Note[nbNote] ;
    nbNote--;

    for (i=0;i<nbNote;i++)
    {
        Note[i] = newNotes[i];
    }

    delete[] newNotes;

}
*/

void NotesManager2::SupprimerNote (note& toDelete)
{
    int i=0;
    while (Note[i]->getID() != toDelete.getID())
    {
        i++;
    }

    for (i;i<nbNote;i++)
    {
        Note[i]=Note[i+1];
    }
    nbNote--;
    delete &toDelete;
}


/*                                                       A FAIRE EN Qt PAREIL POUR SAVE
void NotesManager::load() {
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
            if(xml.name() == "article") {
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
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
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
                        if(xml.name() == "text") {
                            xml.readNext();
                            text=xml.text().toString();
                            qDebug()<<"text="<<text<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                addArticle(identificateur,titre,text);
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

*/


void NotesManager2::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException("erreur sauvegarde notes : ouverture fichier xml");
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for(NotesManager2::ConstIterator it= this->getIterator(); !it.isDone(); it.next())
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

/*
   void article ::  MiseAJour () {
     std::cout <<"mettez a jour le texte "<<std::endl;
     std::cin>> texte;
     setModif();

 }
*/

//************************fonction de media****************


 void media :: afficher(std::ostream& f) const {
     f<<"***Media***" << std::endl;
     note::afficher();
     f <<" chemin ="<<chemin<<std::endl<<std::endl;
     }
 /*
 void media :: MiseAJour () {

     std::cout <<"mettez a jour la description "<<std::endl;
     std::cin>> description;
     setModif();
     }
*/

 //*****************************fonctions de taches ***************

  void tache :: afficher(std::ostream& f ) const {
      f<< "*** Tache ***"<<"\n";

      note::afficher();
      f<<" priorite :"<< priorite << " echeance : "<< echeance<<" etat = "<<status <<std::endl<<std::endl;

  }
  /*
  void tache:: MiseAJour () {
      std::string act;
      std::cout<< "mettez a jour laction"<<std::endl;
      std::cin>> act;
      this->action = act;
      setModif();

  }
*/
