#ifndef VERSIONS_H
#define VERSIONS_H
#include "fenetres.h"


class fenetre_anciennes_versions : public QWidget
{
    Q_OBJECT

public:

fenetre_anciennes_versions(QWidget *parent);

public slots:

void choix_ancienne_version(QString date);

private:

    QVBoxLayout* m_layout_choix;
    QListWidget* m_listeNotes;
    QPushButton* m_restaurer;
    QPushButton* m_quit;
    QWidget* m_parent;
};


#endif // VERSIONS_H
