#ifndef PRODUKCJA_H
#define PRODUKCJA_H

#include "node.h"
#include <QList>

class Produkcja
{

public:
    Produkcja(QList<Node> lewa_strona, QList<Node> prawa_strona);
    bool dopasuj(QList<Node> lewa);
    QList<Node> zastosuj(QList<Node> lewa);

private:
    QList<Node> lewa_strona;
    QList<Node> prawa_strona;
};

#endif // PRODUKCJA_H
