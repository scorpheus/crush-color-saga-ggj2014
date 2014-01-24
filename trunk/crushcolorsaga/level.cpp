#include "level.h"

#include "platform.h"
#include "character.h"

Level::Level(QObject *parent) :
    QGraphicsScene(parent)
{
    setSceneRect(0, 0, 427, 341);

    addItem(new Platform(QPoint(0, 341-16), 27));
    addItem(new Character(1));
}
