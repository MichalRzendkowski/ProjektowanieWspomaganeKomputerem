#include "generatorgrafow.h"


GeneratorGrafow::GeneratorGrafow(Node root, QList<Produkcja> produkcje){
    graf = Graf(root);
    this->produkcje = produkcje;
}


Graf GeneratorGrafow::generuj(){

    QRandomGenerator *generator = QRandomGenerator::global();


    QList<Produkcja> mozliweProdukcje = QList<Produkcja>();

    while(true){

        mozliweProdukcje.clear();

        foreach(Produkcja produkcja, produkcje){
            if(graf.dopasujLosowo(produkcja) >= 0){
                mozliweProdukcje.append(produkcja);
            }
        }

        if(mozliweProdukcje.empty()) break;

        int random = generator->bounded(mozliweProdukcje.size());
        int dopasowanie = graf.dopasujLosowo(mozliweProdukcje[random]);
        graf.zastosuj(dopasowanie, mozliweProdukcje[random]);

    }


    return graf;
}
