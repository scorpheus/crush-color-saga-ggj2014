#ifndef CONTOUR_H
#define CONTOUR_H

#include <QGraphicsItem>

class QGraphicsScene;

class Contour : public QGraphicsItem
{
    public:
        Contour(const QList<QRectF> &borders, QGraphicsScene *parent);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        inline const QList<QRectF> &getBorders() const
        { return _borders; }

    private:
        QList<QRectF> _borders;
        QGraphicsScene *_parent;
};

#endif // CONTOUR_H
