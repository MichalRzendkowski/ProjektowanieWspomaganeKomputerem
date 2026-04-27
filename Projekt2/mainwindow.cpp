#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    QWidget *top = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(top);

    scene->setSceneRect(0, 0, width, height);
    view->setTransformationAnchor(QGraphicsView::NoAnchor);
    view->setResizeAnchor(QGraphicsView::NoAnchor);

    QPushButton *btn = new QPushButton("GENERUJ");
    layout->addWidget(btn);
    layout->addWidget(view);

    setCentralWidget(top);

    connect(btn, &QPushButton::clicked, this, &MainWindow::wyswietl);

    wyswietl();
}

void MainWindow::wyswietl(){
    scene->clear();
    Graf graf = generujGraf();
    graf.print();

    foreach(Node node, graf.nodes){
        auto *item = scene->addPixmap(obrazy[node.etykieta]);
        item->setPos(node.x, node.y);
    }
}

QList<Produkcja> MainWindow::generujProdukcje(){
    QList<Produkcja> produkcje;

    // Dwa poziome prostokąty
    Node prostokat_poziom = Node(false, "PROST_POZIOM");
    Node prostokat_poziom_gora = Node(false, "PROST_POZIOM", 0, 0, height/2, 0, -height/2);
    Node prostokat_poziom_dol = Node(false, "PROST_POZIOM", 0, 0, 0, 0, -height/2);
    produkcje.append(Produkcja({root}, {prostokat_poziom_gora, prostokat_poziom_dol}));

    // Dwa pionowe prostokąty
    Node prostokat_pion = Node(false, "PROST_PION");
    Node prostokat_pion_lewy = Node(false, "PROST_PION", 0, 0, 0, -width/2, 0);
    Node prostokat_pion_prawy = Node(false, "PROST_PION", 0, width/2, 0, -width/2, 0);
    produkcje.append(Produkcja({root}, {prostokat_pion_lewy, prostokat_pion_prawy}));

    // Prostokąt w kwadraty
    Node kwadrat = Node(false, "KWADRAT");
    Node kwadrat_lewy = Node(false, "KWADRAT", 0, 0, 0, -width/2, 0);
    Node kwadrat_prawy = Node(false, "KWADRAT", 0, width/2, 0, -width/2, 0);
    Node kwadrat_gora = Node(false, "KWADRAT", 0, 0, height/2, 0, -height/2);
    Node kwadrat_dol = Node(false, "KWADRAT", 0, 0, 0, 0, -height/2);
    produkcje.append(Produkcja({prostokat_poziom}, {kwadrat_lewy, kwadrat_prawy}));
    produkcje.append(Produkcja({prostokat_pion}, {kwadrat_gora, kwadrat_dol}));

    // Kwadrat w małe kwadraty
    Node maly_kwadrat = Node(false, "MALY_KWADRAT");
    Node kwadrat_lewy_dol = Node(false, "MALY_KWADRAT", 0, 0, 0, -width/4, -height/4);
    Node kwadrat_prawy_dol = Node(false, "MALY_KWADRAT", 0, width/4, 0, -width/4, -height/4);
    Node kwadrat_lewy_gora = Node(false, "MALY_KWADRAT", 0, 0, height/4, -width/4, -height/4);
    Node kwadrat_prawy_gora = Node(false, "MALY_KWADRAT", 0, width/4, height/4, -width/4, -height/4);
    produkcje.append(Produkcja({kwadrat}, {kwadrat_lewy_dol, kwadrat_prawy_dol, kwadrat_lewy_gora, kwadrat_prawy_gora}));

    // Terminale
    produkcje.append(Produkcja({prostokat_poziom}, {Node(true, "KORTY_POZIOM")}));
    produkcje.append(Produkcja({prostokat_poziom}, {Node(true, "GOLF_POZIOM")}));
    produkcje.append(Produkcja({prostokat_poziom}, {Node(true, "LAS_POZIOM")}));

    produkcje.append(Produkcja({prostokat_pion}, {Node(true, "KORTY_PION")}));
    produkcje.append(Produkcja({prostokat_pion}, {Node(true, "GOLF_PION")}));
    produkcje.append(Produkcja({prostokat_pion}, {Node(true, "LAS_PION")}));

    produkcje.append(Produkcja({kwadrat}, {Node(true, "PARKING")}));
    produkcje.append(Produkcja({kwadrat}, {Node(true, "POMNIK")}));
    produkcje.append(Produkcja({kwadrat}, {Node(true, "STAW")}));

    produkcje.append(Produkcja({maly_kwadrat}, {Node(true, "RABATKA")}));
    produkcje.append(Produkcja({maly_kwadrat}, {Node(true, "FONTANNA")}));
    produkcje.append(Produkcja({maly_kwadrat}, {Node(true, "LAWKI")}));
    produkcje.append(Produkcja({maly_kwadrat}, {Node(true, "DRZEWO")}));

    return produkcje;
}

Graf MainWindow::generujGraf(){
    GeneratorGrafow generator(root, generujProdukcje());
    return generator.generuj();
}

MainWindow::~MainWindow()
{
    delete ui;
}
