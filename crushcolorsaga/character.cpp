#include "character.h"

#include <QBitmap>
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>

Character::Character(int id, Level *level, const QColor &color) :
    _id(id),
    _states(Idle),
    _timerAnimation(new QTimer(this)),
    _timerShield(new QTimer(this)),
    _animationIndex(0),
    _level(level),
    _Health(100),
    _shield(Normal),
    _color(color)
{
    _timerAnimation->setInterval(200);
    connect(_timerAnimation, SIGNAL(timeout()), SLOT(updateAnimation()));
    connect(_timerShield,    SIGNAL(timeout()), SLOT(updateShield()));

    QTimer::singleShot(0, this, SLOT(CheckVulnerabilityColor()));
}

QRectF Character::boundingRect() const
{
    return QRectF(0, 0, 36, 36);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPixmap pixmap;
    painter->translate(2, 2);

    if(_states.testFlag(HittingRight))
    {
        painter->translate(32, 0);
        painter->scale(-1, 1);
        pixmap = QPixmap(QString(":/models/hero%1_hit").arg(_id));
    }
    else if(_states.testFlag(HittingLeft))
    {
        pixmap = QPixmap(QString(":/models/hero%1_hit").arg(_id));
    }
    else if(_states.testFlag(MovingLeft))
    {
        pixmap = QPixmap(QString(":/models/hero%1_run0%2").arg(_id).arg(_animationIndex+1));
    }
    else if(_states.testFlag(MovingRight))
    {
        painter->translate(32, 0);
        painter->scale(-1, 1);
        pixmap =QPixmap(QString(":/models/hero%1_run0%2").arg(_id).arg(_animationIndex+1));
    }
    else
    {
        pixmap = QPixmap(QString(":/models/hero%1_standing").arg(_id));
    }

    switch(_shield)
    {
        case Normal:
            break;
        case Stronger:
            {
                QPixmap pixmapShield = QPixmap(pixmap.width(), pixmap.height());
                pixmapShield.fill(_color);
                pixmapShield.setMask(pixmap.mask());
                painter->drawPixmap(-2, -2, pixmap.width()+4, pixmap.height()+4, pixmapShield);
            }
            break;
        case VeryStronger:
            {
                QPixmap pixmapShield = QPixmap(pixmap.width(), pixmap.height());
                pixmapShield.fill(Qt::transparent);
                QPainter subPainter(&pixmapShield);
                subPainter.drawPixmap(0, 0, QPixmap(QString(":/models/particle_%1").arg(_particleIndex)));
                subPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
                subPainter.fillRect(0, 0, pixmap.width(), pixmap.height(), _color);
                subPainter.end();
                painter->drawPixmap(-2, -2, pixmap.width()+4, pixmap.height()+4, pixmapShield);
            }
            break;
        case Surhuman:
            {
                QPixmap pixmapShield = QPixmap(pixmap.width(), pixmap.height());
                pixmapShield.fill(_surhumanShieldCurrentColor);
                pixmapShield.setMask(pixmap.mask());
                painter->drawPixmap(-2, -2, pixmap.width()+4, pixmap.height()+4, pixmapShield);
            }
            break;
    }

    painter->drawPixmap(0, 0, pixmap);
}

Character::States Character::getStates()
{
    return _states;
}

void Character::updateAnimation()
{
    _animationIndex = (_animationIndex + 1) % 2;
    _level->update();
}

void Character::updateShield()
{
    if(_shield == Surhuman)
    {
        QDateTime now = QDateTime::currentDateTimeUtc();
        qint64 delta = _lastShieldUpdate.msecsTo(now);
        if(delta)
        {
            _surhumanShieldCurrentColor = QColor::fromHsv((_surhumanShieldCurrentColor.hue() + delta * 2) % 360, 255, 255);
            update();
            _lastShieldUpdate = now;
        }
    }
    else if(_shield == VeryStronger)
    {
        _particleIndex = (_particleIndex + 1) % 6;
        update();
    }
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

        _level->update();
    }
}

QVariant Character::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemPositionChange)
    {
        CheckVulnerabilityColor();
    }

    return QGraphicsItem::itemChange(change, value);
}

void Character::CheckVulnerabilityColor()
{
    QColor backgroundColor = _level->GetBackgroundColor(boundingRect().translated(scenePos().toPoint()).center().toPoint());

    ShieldState newShieldState;
    int hueDifference = qAbs(backgroundColor.hue() - _color.hue());
    if(hueDifference > 180)
    {
        hueDifference = qAbs(backgroundColor.hue() - (360 - _color.hue()));
    }

    // All color in white, so everyone got surhuman
    if(backgroundColor.saturation() <= 10 && backgroundColor.value() >= 245)
        newShieldState = Surhuman;
    else    // no color so normal
    if(backgroundColor.lightness() <= 10)
        newShieldState = Normal;
    else    // the character is in its own color, surhuman
    if(hueDifference <= 45)
        newShieldState = Surhuman;
    else    // the color is one of the side of the character color, very strong
    if(hueDifference <= 90)
        newShieldState = VeryStronger;
    else    // the color is rgb, just stronger
    if(hueDifference <= 135)
        newShieldState = Stronger;
    else    // for the opposite color, just be normal
        newShieldState = Normal;

    if(newShieldState != _shield)
    {
        _timerShield->stop();
        _shield = newShieldState;

        if(_shield == Surhuman)
        {
            _lastShieldUpdate = QDateTime::currentDateTimeUtc();
            _surhumanShieldCurrentColor = Qt::red;
            _timerShield->start(0);
        }
        else if(_shield == VeryStronger)
        {
            _particleIndex = 0;
            _timerShield->start(75);
        }

        update();
    }
}
