#ifndef FIREBALL_H
#define FIREBALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QDateTime>

#include "Box2D/Box2D.h"

class FireBall : public QObject, public QGraphicsItem
{
    public:
        explicit FireBall(const QColor &color, bool superPower, QGraphicsItem *owner);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

        inline virtual int type() const
        { return UserType + 102; }

        inline bool isSuperPower() const
        { return _superPower; }

        inline QGraphicsItem *getOwner() const
        { return _owner; }

        inline const QColor &getColor() const
        { return _color; }

    protected:
        virtual void timerEvent(QTimerEvent *);

    private:
        QGraphicsItem *_owner;
        bool _superPower;
        QColor _color;
        int _animationId;
        int _timerMove;
        QDateTime _lastUpdate;
        b2Body *_body;
};

#endif // FIREBALL_H
