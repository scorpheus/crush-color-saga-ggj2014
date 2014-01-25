#include "character.h"

#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>

Character::Character(int id, Level *level, ColorCharacter color) :
    _id(id),
    _states(Idle),
    _timerAnimation(new QTimer(this)),
    _animationIndex(0),
    _level(level),
    _Health(100),
    _shield(Normal),
    _character_color(color)
{
    _visual_shield = new QGraphicsRectItem(boundingRect());
    _level->addItem(_visual_shield);
    _visual_shield->setBrush(Qt::cyan);

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
        moveBy(-2, 0);
        painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_run0%2").arg(_id).arg(_animationIndex+1)));
    }
    else if(_states.testFlag(MovingRight))
    {
        moveBy(2, 0);

        painter->translate(32, 0);
        painter->scale(-1, 1);
        painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_run0%2").arg(_id).arg(_animationIndex+1)));
    }
    else
    {
        painter->drawPixmap(0, 0, QPixmap(QString(":/models/hero%1_standing").arg(_id)));
    }

    CheckVulnerabilityColor();
    UpdateVisualShield();
    _visual_shield->setPos(pos());
}

void Character::updateAnimation()
{
    _animationIndex = (_animationIndex + 1) % 2;
    update();
}

void Character::setStates(States states)
{
    if(states != _states)
    {
        _timerAnimation->stop();
        _animationIndex = 0;
        _states = states;

        if(_states.testFlag(MovingLeft) || _states.testFlag(MovingRight))
        {
            _timerAnimation->start();
        }

        update();
    }
}

void Character::CheckVulnerabilityColor()
{
    ColorCharacter current__character_color = _level->GetBackgroundColor(scenePos().toPoint() + QPoint(boundingRect().width(), boundingRect().height())*0.5f);

    // All color in white, so everyone got surhuman
    if(current__character_color == WHITE)
        _shield = Surhuman;
    else    // no color so normal
    if(current__character_color == BLACK)
        _shield = Normal;
    else    // the character is in its own color, surhuman
    if(current__character_color == _character_color)
        _shield = Surhuman;
    else    // the color is one of the side of the character color, very strong
    if((_character_color == RED && (current__character_color == YELLOW || current__character_color == PURPLE )) ||
       (_character_color == BLUE && (current__character_color == CYAN || current__character_color == PURPLE )) ||
       (_character_color == GREEN && (current__character_color == CYAN || current__character_color == YELLOW )))
        _shield = VeryStronger;
    else    // the color is rgb, just stronger
    if((_character_color == RED && (current__character_color == BLUE || current__character_color == GREEN )) ||
       (_character_color == BLUE && (current__character_color == GREEN || current__character_color == RED )) ||
       (_character_color == GREEN && (current__character_color == BLUE || current__character_color == RED )))
        _shield = Stronger;
    else    // for the opposite color, just be normal
        _shield = Normal;

}

void Character::UpdateVisualShield()
{
    switch(_shield)
    {
    case Normal:
        _visual_shield->setBrush(Qt::cyan);
        break;
    case Stronger:
        _visual_shield->setBrush(Qt::green);
        break;
    case VeryStronger:
        _visual_shield->setBrush(Qt::yellow);
        break;
    case Surhuman:
        _visual_shield->setBrush(Qt::red);
        break;
    }

}
