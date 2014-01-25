#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

class Character : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_ENUMS(State)

    public:
        Character(int id);

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

    public slots:
        void setStates(Character::States states);

    private slots:
        void updateAnimation();

    private:
        int _id;
        States _states;
        QTimer *_timerAnimation;
        int _animationIndex;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Character::States);

#endif // CHARACTER_H
