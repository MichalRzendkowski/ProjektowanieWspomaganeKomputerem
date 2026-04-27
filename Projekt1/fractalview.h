#ifndef FRACTALVIEW_H
#define FRACTALVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWheelEvent>

class FractalView : public QGraphicsView
{
    Q_OBJECT
public:
    FractalView(QGraphicsScene *scene, QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event) override;
};

#endif // FRACTALVIEW_H
