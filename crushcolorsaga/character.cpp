#include "character.h"

#include <QDebug>
#include <QPainter>


Character::Character(int id) :
    _id(id),
    _state(Idle),
    _timerAnimation(new QTimer(this)),
    _animationIndex(0)
{
    _timerAnimation->setInterval(200);
    connect(_timerAnimation, SIGNAL(timeout()), SLOT(updateAnimation()));
}

QRectF Character::boundingRect() const
{
    return QRectF(0, 0, 32, 32);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    switch(_state)
    {
        case Idle:
            painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_standing").arg(_id)));
            break;
        case MovingRight:
            painter->translate(32, 0);
            painter->scale(-1, 1);
        case MovingLeft:
            painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_run0%2").arg(_id).arg(_animationIndex+1)));
            break;
        case Hitting:
            break;
    }
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

void Character::updateAnimation()
{
    _animationIndex = (_animationIndex + 1) % 2;
    update();
}

void Character::setState(State state)
{
    _timerAnimation->stop();
    _animationIndex = 0;
    _state = state;

    if(_state == MovingLeft || _state == MovingRight)
    {
        _timerAnimation->start();
    }

    update();
}
