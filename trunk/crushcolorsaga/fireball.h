#ifndef FIREBALL_H
#define FIREBALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QDateTime>

#include "Box2D/Box2D.h"

class FireBall : public QObject, public QGraphicsItem
{
    public:
        explicit FireBall(const QColor &color, bool superPower);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

        inline virtual int type() const
        { return UserType + 102; }

        inline bool isSuperPower() const
        { return _superPower; }

    protected:
        virtual void timerEvent(QTimerEvent *);

    private:
        bool _superPower;
        QColor _color;
        int _animationId;
        int _timerMove;
        QDateTime _lastUpdate;
        b2Body *_body;
};

#endif // FIREBALL_H
