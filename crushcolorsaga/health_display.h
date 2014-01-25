#ifndef HEALTHDISPLAY_H
#define HEALTHDISPLAY_H

#include <QGraphicsItem>
class Character;

class HealthDisplay : public QGraphicsItem
{
    public:
        HealthDisplay(QPoint start, Character *character);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private:
        QPoint _start;
        Character* _character;
};

#endif // HEALTHDISPLAY_H
