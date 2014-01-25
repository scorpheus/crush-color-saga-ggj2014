#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsItem>

class Platform : public QGraphicsItem
{
    public:
        Platform(int width);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        inline virtual int type() const
        { return UserType + 100; }

    private:
        int _width;
};

#endif // PLATFORM_H
