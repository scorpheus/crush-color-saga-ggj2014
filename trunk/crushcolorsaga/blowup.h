#ifndef BLOWUP_H
#define BLOWUP_H

#include <QObject>
#include <QGraphicsItem>

class BlowUp : public QObject, public QGraphicsItem
{
    Q_OBJECT

    public:
        explicit BlowUp(const QColor &color, QObject *parent = 0);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    public:
        virtual void timerEvent(QTimerEvent *);

    private:
        QColor _color;
        int _animation;
};

#endif // BLOWUP_H
