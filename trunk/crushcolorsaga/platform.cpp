#include "platform.h"

#include <QPainter>


Platform::Platform(int width) :
    _width(width)
{
}

QRectF Platform::boundingRect() const
{
    return QRectF(0, 0, _width * 16, 16);
}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i=0 ; i<_width ; i++)
    {
        painter->drawPixmap(0, 0, QPixmap(":/models/bloc"));
        painter->translate(16, 0);
    }
}
