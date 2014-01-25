#include "inputmanager.h"

#include <QCoreApplication>
#include <QKeyEvent>


InputManager::InputManager(QObject *parent) :
    QObject(parent),
    _states1(Character::Idle)
{
    QCoreApplication::instance()->installEventFilter(this);
}

bool InputManager::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)(event);
        if(not keyEvent->isAutoRepeat())
        {
            Qt::Key key = Qt::Key(keyEvent->key());
            if(key == Qt::Key_Up)
            {
                _states1 |= Character::Jumping;
                emit state1(_states1);
                return true;
            }
            else if(key == Qt::Key_Left)
            {
                _states1 |= Character::MovingLeft;
                emit state1(_states1);
                return true;
            }
            else if(key == Qt::Key_Right)
            {
                _states1 |= Character::MovingRight;
                emit state1(_states1);
                return true;
            }
            else if(key == Qt::Key_Space)
            {
                if(_states1.testFlag(Character::MovingLeft))
                {
                    _states1 |= Character::HittingLeft;
                }
                else
                {
                    _states1 |= Character::HittingRight;
                }
                emit state1(_states1);
                return true;
            }
        }
    }
    else if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)(event);
        if(not keyEvent->isAutoRepeat())
        {
            Qt::Key key = Qt::Key(keyEvent->key());
            if(key == Qt::Key_Up)
            {
                _states1 &= ~Character::Jumping;
                emit state1(_states1);
                return true;
            }
            else if(key == Qt::Key_Left)
            {
                _states1 &= ~Character::MovingLeft;
                emit state1(_states1);
                return true;
            }
            else if(key == Qt::Key_Right)
            {
                _states1 &= ~Character::MovingRight;
                emit state1(_states1);
                return true;
            }
            else if(key == Qt::Key_Space)
            {
                if(_states1.testFlag(Character::MovingLeft))
                {
                    _states1 &= ~Character::HittingLeft;
                }
                else
                {
                    _states1 &= ~Character::HittingRight;
                }
                emit state1(_states1);
                return true;
            }
        }
    }

    return false;
}
