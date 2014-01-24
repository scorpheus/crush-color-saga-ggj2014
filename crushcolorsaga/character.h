#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>

class Character : public QGraphicsItem
{
    public:
        Character();

    public slots:
        void moveLeft();
        void moveRight();
        void stop();
        void jump();
        void hit();
};

#endif // CHARACTER_H
