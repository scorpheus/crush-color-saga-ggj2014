#include "platform.h"

#include <QPainter>


Platform::Platform(QPoint start, int width) :
    _start(start),
    _width(width)
{
}

QRectF Platform::boundingRect() const
{
    return QRectF(_start, QSize(_width*16, 16));
}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i=0 ; i<_width ; i++)
    {
        painter->drawPixmap(_start, QPixmap(":/models/bloc"));
        painter->translate(16, 0);
    }
}
