#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>

class Character : public QGraphicsItem
{
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
        int _id;
};

#endif // CHARACTER_H
