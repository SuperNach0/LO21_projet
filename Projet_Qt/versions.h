#ifndef VERSIONS_H
#define VERSIONS_H
#include "fenetres.h"

/// Classe Fenetre d'affichage des anciennes versions
/** Cette fenêtre sert à afficher, sélectionner et éventuellement restaurer une version d'une note. Les versions sont affichées selon
 * la note depuis laquelle le menu contextuel et l'action "Anciennces versions" a été activée.
 */
class fenetre_anciennes_versions : public QWidget
{
    Q_OBJECT

public:
///Constructeur, initialise la fenetre d'affichage des anciennes versions avec un QListWidget
    /**
 * @param : Widget/Fenetre parente d'où provient la fenetre
 */
fenetre_anciennes_versions(QWidget *parent);

public slots:

///Slot appelé lors d'un clic sur l'une des notes du QListWidget. Cela provoque l'affichage de la version de la note dans la fenetre principale
/**
 * @param date
 */
void choix_ancienne_version(QString date);
///Slot appelé lors d'un clic sur "Restaurer". Supprime la note active et la remplace par la version sélectionnée.
void restaurer();

private:

    QVBoxLayout* m_layout_choix;
    QListWidget* m_listeNotes;
    QPushButton* m_restaurer;
    QPushButton* m_quit;
    QWidget* m_parent;
};


#endif // VERSIONS_H
