#include "fireball.h"

#include <QPainter>


FireBall::FireBall(const QColor &color, bool superPower) :
    QGraphicsItem(),
    _superPower(superPower),
    _color(color),
    _animationId(0),
    _body(NULL)
{
    startTimer(40);
}

QRectF FireBall::boundingRect() const
{
    return QRectF(0, 0, 8, 8);
}

void FireBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPixmap pixmap = QPixmap(QString(":/models/bubble_%1").arg(_animationId));
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

void FireBall::timerEvent(QTimerEvent *)
{
    _animationId = (_animationId + 1) % 6;
    update();
}
