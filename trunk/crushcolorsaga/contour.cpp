#include "contour.h"

#include <QPainter>
#include <QGraphicsScene>


Contour::Contour(const QList<QRectF> &borders, QGraphicsScene *parent) :
    _borders(borders),
    _parent(parent)
{

}

QRectF Contour::boundingRect() const
{
    return QRectF(QPointF(0,0), QSize(_parent->width(), _parent->height()));
}

void Contour::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPixmap _contour_model(":/models/contour");
    int contour_width = QPixmap(":/models/contour").width();
    int contour_height = QPixmap(":/models/contour").height();

    foreach(const QRectF &rect, _borders)
    {
        for(qreal i=0 ; i<rect.width() ; i+=contour_width)
        {
            for(qreal j=0 ; j<rect.height() ; j+=contour_height)
            {
                painter->drawPixmap(QPointF(i, j) + rect.topLeft(), _contour_model);
            }
        }
    }
}
