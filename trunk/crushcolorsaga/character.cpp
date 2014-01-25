#include "character.h"

#include <QPainter>


Character::Character(int id) :
    _id(id),
    _state(Idle)
{
}

QRectF Character::boundingRect() const
{
    return QRectF(0, 0, 32, 32);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_standing").arg(_id)));
}

void Character::moveLeft()
{

}

void Character::moveRight()
{

}

void Character::stop()
{

}

void Character::jump()
{

}

void Character::hit()
{

}
