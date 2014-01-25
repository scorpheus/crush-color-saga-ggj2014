#include "end_level.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QTimeLine>
#include <QGraphicsItemAnimation>

#include "mainwindow.h"
extern MainWindow* g_MainWindow;


EndLevel::EndLevel(QGraphicsScene *parent, QString end_text) :
    _parent(parent),
    _end_text(end_text)
{
    timer = new QTimeLine(2000);
    timer->setFrameRange(0, 100);

    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(this);
    animation->setTimeLine(timer);

    for (int i = 0; i < 200; ++i)
        animation->setShearAt (i / 200.0, 2.0-i/100.0, 2.0-i/100.0);

    timer->connect(timer, SIGNAL(finished()), g_MainWindow, SLOT(NextLevel()));
}

QRectF EndLevel::boundingRect() const
{
    return QRectF(0, 0, 16, 40);
}

void EndLevel::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::darkBlue);
    painter->scale(2,2);
    painter->drawText(QPointF(_parent->width()*0.25 - 50, _parent->height()*0.25), _end_text);
    _parent->update();
}
