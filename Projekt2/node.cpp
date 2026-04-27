#include "node.h"

Node::Node(bool terminalny, QString etykieta, int id , int x, int y, int w, int h){

    this->terminalny = terminalny;
    this->etykieta = etykieta;
    this->id = id;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}
