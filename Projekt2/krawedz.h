#ifndef KRAWEDZ_H
#define KRAWEDZ_H

#include <QString>

class Krawedz
{
public:
    Krawedz(int id1, int id2, QString etykieta = "");

private:
    int id1, id2;
    QString etykieta;
};

#endif // KRAWEDZ_H
