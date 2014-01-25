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
    character1->moveBy(100, 100);
    addItem(character1);

    InputManager *inputManager = new InputManager(this);
    connect(inputManager, SIGNAL(state1(Character::States)), character1, SLOT(setStates(Character::States)));
}
