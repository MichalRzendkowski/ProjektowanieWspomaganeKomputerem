#include "graf.h"

Graf::Graf(){}

Graf::Graf(Node root) {
    nodes.append(root);
}

int Graf::dopasujLosowo(Produkcja produkcja){
    QList<int> dopasowania = dopasuj(produkcja);
    if(dopasowania.empty()) return -1;

    QRandomGenerator *generator = QRandomGenerator::global();
    int random = generator->bounded(dopasowania.size());
    return dopasowania[random];
}

QList<int> Graf::dopasuj(Produkcja produkcja){
    QList<int> dopasowania;

    foreach(Node node, nodes)
        if(produkcja.dopasuj({node}))
            dopasowania.append(node.id);

    return dopasowania;
}

void Graf::zastosuj(int id, Produkcja produkcja){

    QList<Node> dopasowanie;
    for(int i = 0; i < nodes.size(); i++){
        if(nodes[i].id != id) continue;
        dopasowanie = produkcja.zastosuj({nodes[i]});
        nodes.remove(i);
        break;
    }

    foreach(Node node, dopasowanie){
        nodeId++;
        node.id = nodeId;
        nodes.append(node);
    }
}

void Graf::print(){
    qDebug() << "NODES:";
    foreach(Node node, nodes){
        qDebug() << node.etykieta << "  id: " << node.id <<
            "  x: " << node.x << "  y: " << node.y <<
            "  w: " << node.w << "  h: " << node.h;
    }
}
