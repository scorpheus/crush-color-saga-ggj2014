#include "inputmanager.h"

#include <QCoreApplication>
#include <QKeyEvent>


InputManager::InputManager(QObject *parent) :
    QObject(parent)
{
    QCoreApplication::instance()->installEventFilter(this);
}

bool InputManager::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        Qt::Key key = Qt::Key(((QKeyEvent *)event)->key());
        if(key == Qt::Key_Up)
        {

        }
        else if(key == Qt::Key_Left)
        {

        }
        else if(key == Qt::Key_Right)
        {

        }
    }

    return false;
}
