#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsItem>

class Platform : public QGraphicsItem
{
    public:
        Platform(QPoint start, int width);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private:
        QPoint _start;
        int _width;
};

#endif // PLATFORM_H
