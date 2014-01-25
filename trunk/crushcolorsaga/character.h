#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

class Character : public QObject, public QGraphicsItem
{
    Q_OBJECT

    public:
        Character(int id);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    public slots:
        void moveLeft();
        void moveRight();
        void stop();
        void jump();
        void hit();

    private:
        typedef enum
        {
            Idle,
            MovingLeft,
            MovingRight,
            HittingLeft,
            HittingRight
        } State;

    private slots:
        void updateAnimation();

    private:
        void setState(State state);

    private:
        int _id;
        State _state;
        QTimer *_timerAnimation;
        int _animationIndex;
};

#endif // CHARACTER_H
