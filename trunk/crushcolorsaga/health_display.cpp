#include "health_display.h"
#include "character.h"

#include <QPainter>


HealthDisplay::HealthDisplay(QPoint start, Character *character) :
    _start(start),
    _character(character)
{
}

QRectF HealthDisplay::boundingRect() const
{
    return QRectF(_start, QSize(40, 8));
}

void HealthDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawText(_start, QString::number(_character->_Health));

}
