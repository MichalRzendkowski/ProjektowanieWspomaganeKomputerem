#ifndef FRACTALWIDGET_H
#define FRACTALWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsPolygonItem>
#include <QGraphicsObject>
#include "fractalview.h"
#include "fractalelement.h"
#include "grammarutils.h"

#define __SHOW_MARKERS

class FractalWidget : public QWidget
{
    Q_OBJECT
public:
    FractalWidget(QWidget *parent = nullptr);

private:
    void updateElements();
    void setupUI();
    void addTransformations();
    void applyTransformation(Transformation* t, Marker* m);
    void showSuggestions(QVector<int> types);
    void hideSuggestions();
    void onSuggestionClicked(Marker* m);
    bool matchTransformation(Transformation* t, Marker* m);
    bool notNull(Marker* m);
    QPolygonF translatePoly(QPolygonF poly, Marker* m);

    double scaleFactor = 1 / sqrt(3);
    int sideRotationAngle = 60;
    int topRotationAngle = -90;
    int firstPolySize = 100;
    double firstPolyX = firstPolySize * sqrt(3) / 4.0;
    double firstPolyY = firstPolySize * 3.0 / 4.0;

    QColor suggestionColor = Qt::green;
    QSize iconSize = QSize(150, 150);
    QIcon icon1 = QIcon(":/icons/transform1");
    QIcon icon2 = QIcon(":/icons/transform2");

    QSet<Transformation*> grammar;
    QSet<FractalElement*> elements;
    QSet<FractalElement*> suggestions;
    QSet<Marker*> markers;
    QPolygonF polyTemplate = QPolygonF({QPointF(0,0),
                                        QPointF(firstPolyX,firstPolyY),
                                        QPointF(0, firstPolySize),
                                        QPointF(-firstPolyX,firstPolyY)});

    QGraphicsScene *scene = new QGraphicsScene();
    FractalView *view = new FractalView(scene);
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    QPushButton *button1 = new QPushButton();
    QPushButton *button2 = new QPushButton();
};

#endif // FRACTALWIDGET_H
