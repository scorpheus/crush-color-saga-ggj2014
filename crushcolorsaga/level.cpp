#include "level.h"

#include "platform.h"
#include "character.h"
#include "inputmanager.h"


Level::Level(QObject *parent) :
    QGraphicsScene(parent)
{
    setSceneRect(0, 0, 427, 341);

    addItem(new Platform(QPoint(0, 341-16), 27));

    Character *character1 = new Character(1);
    addItem(character1);

    InputManager *inputManager = new InputManager(this);
    connect(inputManager, SIGNAL(jump1()), character1, SLOT(jump()));
    connect(inputManager, SIGNAL(moveLeft1()), character1, SLOT(moveLeft()));
    connect(inputManager, SIGNAL(moveRight1()), character1, SLOT(moveRight()));
}
