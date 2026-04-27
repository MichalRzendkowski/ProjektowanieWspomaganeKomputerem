#ifndef GRAF_H
#define GRAF_H

#include "node.h"
#include "krawedz.h"
#include "produkcja.h"
#include <QList>
#include <QRandomGenerator>
#include <QDebug>

class Graf
{
public:
    Graf();
    Graf(Node root);

    int dopasujLosowo(Produkcja produkcja);
    QList<int> dopasuj(Produkcja produkcja);
    void zastosuj(int id, Produkcja produkcja);

    void print();

    QList<Node> nodes;
    QList<Krawedz> krawedzie;
    int nodeId = 1;
};

#endif // GRAF_H
