#include "contour.h"

#include <QPainter>
#include <QGraphicsScene>


Contour::Contour(QGraphicsScene *parent) :
    _parent(parent)
{

}

QRectF Contour::boundingRect() const
{
    return QRectF(_start, QSize(_width*16, 16));
}

void Contour::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int contour_width = QPixmap(":/models/contour").width();
    int contour_height = QPixmap(":/models/contour").height();
    int nb_width = _parent->width()/contour_width;
    for(int i=0 ; i< nb_width; i++)
    {
        painter->drawPixmap(QPoint(contour_width*i, 0), QPixmap(":/models/contour"));
    }
    for(int i=0 ; i< nb_width; i++)
    {
        painter->drawPixmap(QPoint(contour_width*i, _parent->height()-contour_height), QPixmap(":/models/contour"));
    }

    int nb_height = _parent->width()/contour_width;
    for(int i=0 ; i< nb_height; i++)
    {
        painter->drawPixmap(QPoint(0, contour_height*i), QPixmap(":/models/contour"));
    }
    for(int i=0 ; i< nb_height; i++)
    {
        painter->drawPixmap(QPoint(_parent->width()-contour_width, contour_height*i), QPixmap(":/models/contour"));
    }
}
