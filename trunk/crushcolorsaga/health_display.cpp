#include "health_display.h"
#include "character.h"

#include <QPainter>


HealthDisplay::HealthDisplay(Character *character) :
    _character(character)
{
}

QRectF HealthDisplay::boundingRect() const
{
    return QRectF(0, 0, 50, 12);
}

void HealthDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setOpacity(1);

    QRectF adjustedRect = boundingRect().adjusted(1, 1, -1, -1);

    int red = 0;
    int green = 0;
    qreal health = _character->_Health / 100.0;
    if(health > 0.5)
    {
        red = 510 - 510 * health;
        green = 255;
    }
    else
    {
        red = 255;
        green = health * 255 * 2;
    }

    painter->fillRect(QRectF(adjustedRect.topLeft(),
                             QSize((adjustedRect.width() * _character->_Health) / 100.0, adjustedRect.height())),
                      QColor(red, green, 0));

    QPen pen(Qt::black, 2);
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);
    painter->drawRect(adjustedRect);
}
