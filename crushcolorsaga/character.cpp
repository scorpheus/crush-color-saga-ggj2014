#include "character.h"

#include <QDebug>
#include <QPainter>


Character::Character(int id) :
    _id(id),
    _states(Idle),
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
    if(_states.testFlag(HittingRight))
    {
        painter->translate(32, 0);
        painter->scale(-1, 1);
        painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_hit").arg(_id)));
    }
    else if(_states.testFlag(HittingLeft))
    {
        painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_hit").arg(_id)));
    }
    else if(_states.testFlag(MovingLeft))
    {
        painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_run0%2").arg(_id).arg(_animationIndex+1)));
    }
    else if(_states.testFlag(MovingRight))
    {
        painter->translate(32, 0);
        painter->scale(-1, 1);
        painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_run0%2").arg(_id).arg(_animationIndex+1)));
    }
    else
    {
        painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_standing").arg(_id)));
    }
}

void Character::updateAnimation()
{
    if(_states.testFlag(HittingLeft))
    {
        setStates(_states & ~HittingLeft);
    }
    else if(_states.testFlag(HittingRight))
    {
        setStates(_states & ~HittingRight);
    }
    else
    {
        _animationIndex = (_animationIndex + 1) % 2;
    }
    update();
}

void Character::setStates(States states)
{
    if(states != _states)
    {
        _timerAnimation->stop();
        _animationIndex = 0;
        _states = states;

        if(_states.testFlag(MovingLeft) || _states.testFlag(MovingRight) ||
           _states.testFlag(HittingLeft) || _states.testFlag(HittingRight))
        {
            _timerAnimation->start();
        }

        update();
    }
}
