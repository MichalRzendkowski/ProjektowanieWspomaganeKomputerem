#ifndef NODE_H
#define NODE_H

#include <QString>

class Node
{
public:
    Node(bool terminalny, QString etykieta, int id = 0, int x = 0, int y = 0, int w = 0, int h = 0);
    int id, x, y, w, h;
    bool terminalny;
    QString etykieta;
};

#endif // NODE_H
