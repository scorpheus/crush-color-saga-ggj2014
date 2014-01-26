#include "contour.h"

#include <QPainter>
#include <QGraphicsScene>


Contour::Contour(QGraphicsScene *parent) :
    _parent(parent)
{

}

QRectF Contour::boundingRect() const
{
    return QRectF(QPointF(0,0), QSize(_parent->width(), _parent->height()));
}

void Contour::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap _contour_model(":/models/contour");
    int contour_width = QPixmap(":/models/contour").width();
    int contour_height = QPixmap(":/models/contour").height();
    int nb_width = _parent->width()/contour_width;
    for(int i=0 ; i< nb_width; i++)
    {
        painter->drawPixmap(QPoint(contour_width*i, 0), _contour_model);
    }
    for(int i=0 ; i< nb_width; i++)
    {
        painter->drawPixmap(QPoint(contour_width*i, _parent->height()-contour_height), _contour_model);
    }

    int nb_height = _parent->width()/contour_width;
    for(int i=0 ; i< nb_height; i++)
    {
        painter->drawPixmap(QPoint(0, contour_height*i), _contour_model);
    }
    for(int i=0 ; i< nb_height; i++)
    {
        painter->drawPixmap(QPoint(_parent->width()-contour_width, contour_height*i), _contour_model);
    }
}
