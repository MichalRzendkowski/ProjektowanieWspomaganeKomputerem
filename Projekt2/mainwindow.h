#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QGraphicsScene>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMap>
#include "graf.h"
#include "generatorgrafow.h"
#include "produkcja.h"
#include "node.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int width = 400;
    int height = 400;
    Node root = Node(false, "PARK", 0, 0, 0, width, height);

    QList<Produkcja> generujProdukcje();
    Graf generujGraf();
    void wyswietl();

    QGraphicsScene *scene;
    QGraphicsView  *view;

    QMap<QString, QPixmap> obrazy = {{"KORTY_POZIOM", QPixmap(":/obrazy/KORTY_POZIOM.png")},
                                     {"GOLF_POZIOM", QPixmap(":/obrazy/GOLF_POZIOM.png")},
                                     {"LAS_POZIOM", QPixmap(":/obrazy/LAS_POZIOM.png")},
                                     {"KORTY_PION", QPixmap(":/obrazy/KORTY_PION.png")},
                                     {"GOLF_PION", QPixmap(":/obrazy/GOLF_PION.png")},
                                     {"LAS_PION", QPixmap(":/obrazy/LAS_PION.png")},
                                     {"PARKING", QPixmap(":/obrazy/PARKING.png")},
                                     {"POMNIK", QPixmap(":/obrazy/POMNIK.png")},
                                     {"STAW", QPixmap(":/obrazy/STAW.png")},
                                     {"RABATKA", QPixmap(":/obrazy/RABATKA.png")},
                                     {"FONTANNA", QPixmap(":/obrazy/FONTANNA.png")},
                                     {"LAWKI", QPixmap(":/obrazy/LAWKI.png")},
                                     {"DRZEWO", QPixmap(":/obrazy/DRZEWO.png")},};
};
#endif // MAINWINDOW_H
