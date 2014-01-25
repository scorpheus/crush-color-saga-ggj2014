#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>
#include <QObject>

class Character : public QObject, public QGraphicsItem
{
    Q_OBJECT

    public:
        Character(int id);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

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
            Hitting
        } State;

    private:
        int _id;
        State _state;
};

#endif // CHARACTER_H
