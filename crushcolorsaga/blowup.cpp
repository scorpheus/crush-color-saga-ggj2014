#include "blowup.h"

#include <QPainter>


BlowUp::BlowUp(const QColor &color, QObject *parent) :
    QGraphicsItem(),
    _color(color),
    _animation(0)
{
    startTimer(50);
}

QRectF BlowUp::boundingRect() const
{
    return QRectF(0, 0, 16, 16);
}

void BlowUp::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPixmap pixmap = QPixmap(QString(":/models/bigboom_%1").arg(_animation));
    QPixmap pixmapColored = QPixmap(pixmap.width(), pixmap.height());
    pixmapColored.fill(Qt::transparent);
    QPainter subPainter(&pixmapColored);
    subPainter.drawPixmap(0, 0, pixmap);
    subPainter.setCompositionMode(QPainter::CompositionMode_Plus);
    subPainter.fillRect(0, 0, pixmap.width(), pixmap.height(), _color);
    subPainter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    subPainter.drawPixmap(0, 0, pixmap);
    subPainter.end();

    painter->drawPixmap(0, 0, pixmapColored);
}

void BlowUp::timerEvent(QTimerEvent *)
{
    _animation++;

    if(_animation > 6)
    {
        deleteLater();
    }
    else
    {
        update();
    }
}
