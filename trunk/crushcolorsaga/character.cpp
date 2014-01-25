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
        case HittingRight:
            painter->translate(32, 0);
            painter->scale(-1, 1);
        case HittingLeft:
            painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_hit").arg(_id)));
            break;
    }
}

void Character::moveLeft()
{
    setState(MovingLeft);
}

void Character::moveRight()
{
    setState(MovingRight);
}

void Character::stop()
{
    setState(Idle);
}

void Character::jump()
{

}

void Character::hit()
{
    if(_state == MovingLeft)
    {
        setState(HittingLeft);
    }
    else
    {
        setState(HittingRight);
    }
}

void Character::updateAnimation()
{
    if(_state == HittingLeft || _state == HittingRight)
    {
        _state = Idle;
    }
    else
    {
        _animationIndex = (_animationIndex + 1) % 2;
    }
    update();
}

void Character::setState(State state)
{
    if(state != _state)
    {
        _timerAnimation->stop();
        _animationIndex = 0;
        _state = state;

        if(_state == MovingLeft || _state == MovingRight || _state == HittingLeft || _state == HittingRight)
        {
            _timerAnimation->start();
        }

        update();
    }
}
