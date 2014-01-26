#ifndef CHARACTER_H
#define CHARACTER_H

#include <QDateTime>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsRectItem>

#include "level.h"

class Character : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_ENUMS(State)

    public:
        Character(int id, Level *level, const QColor &color);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    public:
        typedef enum
        {
            Idle         =0x00,
            MovingLeft   =0x01,
            MovingRight  =0x02,
            HittingLeft  =0x04,
            HittingRight =0x08,
            Jumping      =0x10
        } State;

        Q_DECLARE_FLAGS(States, State);

        typedef enum
        {
           Normal = 0,
           Stronger,
           VeryStronger,
           Surhuman
        } ShieldState;

        int _Health;

        Character::States getStates();

    public slots:
        void setStates(Character::States states);

    protected:
        virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    private slots:
        void updateAnimation();

        void CheckVulnerabilityColor();

        void updateShield();

    private:
        int _id;
        States _states;
        QTimer *_timerAnimation;
        QTimer *_timerShield;
        int _animationIndex;
        int _particleIndex;
        Level *_level;
        QColor _color;
        QColor _surhumanShieldCurrentColor;
        QDateTime _lastShieldUpdate;
        ShieldState _shield;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Character::States);

#endif // CHARACTER_H
