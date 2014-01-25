#ifndef END_LEVEL_H
#define END_LEVEL_H

#include <QGraphicsItem>

class QGraphicsScene;
class QTimeLine;

class EndLevel : public QGraphicsItem
{
    public:
        EndLevel(QGraphicsScene *parent, QString end_text);

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        QTimeLine *timer;

    private:
        QPoint _start;
        int _width;
        QGraphicsScene *_parent;
        QString _end_text;
};

#endif // END_LEVEL_H
