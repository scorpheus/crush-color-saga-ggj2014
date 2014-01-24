#include "level.h"

#include "platform.h"

Level::Level(QObject *parent) :
    QGraphicsScene(parent)
{
    addItem(new Platform(QPoint(0, 0), 10));
}
