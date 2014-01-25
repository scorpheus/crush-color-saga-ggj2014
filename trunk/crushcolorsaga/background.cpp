#include "background.h"

#include <QPainter>


Background::Background(const QImage &image) :
    _image(image)
{
}

QRectF Background::boundingRect() const
{
    return QRectF(0, 0, 427, 341);
}

void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(0, 0, _image);
}
