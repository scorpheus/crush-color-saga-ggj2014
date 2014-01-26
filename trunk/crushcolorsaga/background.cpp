#include "background.h"

#include <QPainter>

#include "level.h"


Background::Background(const QImage &image) :
    _image(image)
{
}

QRectF Background::boundingRect() const
{
    return QRectF(0, 0, SCENEWIDTH, SCENEHEIGHT);
}

void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(0, 0, _image);
}
