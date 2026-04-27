#include "produkcja.h"

Produkcja::Produkcja(QList<Node> lewa_strona, QList<Node> prawa_strona){
    this->lewa_strona = lewa_strona;
    this->prawa_strona = prawa_strona;
}

bool Produkcja::dopasuj(QList<Node> lewa){

    bool match = false;
    foreach(Node node1, lewa){
        foreach(Node node2, lewa_strona){
            if(node1.etykieta == node2.etykieta && !node1.terminalny){
                match = true;
            }
        }

        if(!match){
            return false;
        }
    }

    return true;
}


QList<Node> Produkcja::zastosuj(QList<Node> lewa_strona){
    if(!dopasuj(lewa_strona)) return QList<Node>();

    QList<Node> prawa = prawa_strona;

    for(int i = 0; i < prawa.size(); i++){
        prawa[i].x += lewa_strona[0].x;
        prawa[i].y += lewa_strona[0].y;
        prawa[i].w += lewa_strona[0].w;
        prawa[i].h += lewa_strona[0].h;
    }

    return prawa;
}
