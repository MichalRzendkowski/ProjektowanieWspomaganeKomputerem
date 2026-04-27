#ifndef GENERATORGRAFOW_H
#define GENERATORGRAFOW_H

#include "node.h"
#include "graf.h"
#include "produkcja.h"
#include <QList>
#include <QDebug>

class GeneratorGrafow
{
public:
    GeneratorGrafow(Node root, QList<Produkcja> produkcje);
    Graf generuj();

    QList<Produkcja> produkcje;
    Graf graf;
};

#endif // GENERATORGRAFOW_H
