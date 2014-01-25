#ifndef CONTOUR_H
#define CONTOUR_H

#include <QGraphicsItem>

class QGraphicsScene;

class Contour : public QGraphicsItem
{
    public:
        Contour(QGraphicsScene *parent);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private:
        QPoint _start;
        int _width;
        QGraphicsScene *_parent;
};

#endif // CONTOUR_H
