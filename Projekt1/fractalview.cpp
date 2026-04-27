#include "fractalview.h"

FractalView::FractalView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent)
{
    setRenderHint(QPainter::Antialiasing);
    setDragMode(ScrollHandDrag);
}

void FractalView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
        scale(1.1, 1.1);
    else
        scale(1/1.1, 1/1.1);
}
