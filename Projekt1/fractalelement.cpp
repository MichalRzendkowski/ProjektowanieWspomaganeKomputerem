#include "fractalelement.h"

FractalElement::FractalElement(QPolygonF poly, QGraphicsItem *parent) : QGraphicsObject(parent) {
    this->poly = poly;
}

QRectF FractalElement::boundingRect() const {
    return poly.boundingRect();
}

void FractalElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);
    QPen pen(Qt::black, 2);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawPolygon(poly);
}

void FractalElement::setColor(QColor color){
    this->color = color;;
}

void FractalElement::setMarker(Marker *m){
    delete marker;
    this->marker = m;
}

void FractalElement::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked(marker);
    QGraphicsObject::mousePressEvent(event);
    event->accept();
}
