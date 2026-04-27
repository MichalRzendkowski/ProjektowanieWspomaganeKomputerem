#ifndef GRAMMARUTILS_H
#define GRAMMARUTILS_H

#include <QGraphicsObject>

struct Marker {
    QPointF position;
    double rotation;
    double size;
    int type;
    Marker(QPointF pos, double rot, double size, int t)
        : position(pos), rotation(rot), size(size), type(t) {}
};

struct TransformationRight{
    QPolygonF poly;
    Marker markerSide;
    Marker markerTop;
};

struct Transformation{
    Marker leftSide;
    TransformationRight rightSide;
    Transformation(Marker left, TransformationRight right)
        : leftSide(left), rightSide(right) {}
};

#endif // GRAMMARUTILS_H
