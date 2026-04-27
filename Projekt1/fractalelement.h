#ifndef FRACTALELEMENT_H
#define FRACTALELEMENT_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "grammarutils.h"

class FractalElement : public QGraphicsObject
{
    Q_OBJECT
public:
    FractalElement(QPolygonF poly, QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void setColor(QColor color);
    void setMarker(Marker *m);

signals:
    void clicked(Marker* marker);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Marker *marker = new Marker(QPointF(0,0), 0, 0, 0);
    QColor color = Qt::blue;
    QPolygonF poly;
};

#endif // FRACTALELEMENT_H
