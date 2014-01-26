#ifndef FIREBALL_H
#define FIREBALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QDateTime>

class FireBall : public QObject, public QGraphicsItem
{
    public:
        explicit FireBall(const QColor &color, bool superPower, Qt::LayoutDirection direction);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    protected:
        virtual void timerEvent(QTimerEvent *);

    private:
        QColor _color;
        int _animationId;
        bool _superPower;
        Qt::LayoutDirection _direction;
        int _timerMove;
        QDateTime _lastUpdate;
};

#endif // FIREBALL_H
