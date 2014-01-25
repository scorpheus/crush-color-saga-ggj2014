#include "character.h"

#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>

Character::Character(int id, Level *level) :
    _id(id),
    _states(Idle),
    _timerAnimation(new QTimer(this)),
    _animationIndex(0),
    _level(level),
    _Health(100)
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

    CheckVulnerabilityColor();
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
    ColorCharacter current_character_color = _level->GetBackgroundColor(scenePos().toPoint());

    // All color in white, so everyone got surhuman
    if(current_character_color == WHITE)
        shield = Surhuman;
    else    // no color so normal
    if(current_character_color == BLACK)
        shield = Normal;
    else    // the character is in its own color, surhuman
    if(current_character_color == character_color)
        shield = Surhuman;
    else    // the color is one of the side of the character color, very strong
    if((character_color == RED && (current_character_color == YELLOW || current_character_color == PURPLE )) ||
       (character_color == BLUE && (current_character_color == CYAN || current_character_color == PURPLE )) ||
       (character_color == GREEN && (current_character_color == CYAN || current_character_color == YELLOW )))
        shield = VeryStronger;
    else    // the color is rgb, just stronger
    if((character_color == RED && (current_character_color == BLUE || current_character_color == GREEN )) ||
       (character_color == BLUE && (current_character_color == GREEN || current_character_color == RED )) ||
       (character_color == GREEN && (current_character_color == BLUE || current_character_color == RED )))
        shield = Stronger;
    else    // for the opposite color, just be normal
        shield = Normal;
}
