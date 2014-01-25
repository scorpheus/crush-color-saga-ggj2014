#include "inputmanager.h"

#include <QCoreApplication>
#include <QKeyEvent>

#include "mainwindow.h"
extern MainWindow* g_MainWindow;

InputManager::InputManager(QObject *parent) :
    QObject(parent),
    _states1(Character::Idle),
    _states2(Character::Idle),
    _timerStopHit1(new QTimer(this)),
    _timerStopHit2(new QTimer(this))
{
    QCoreApplication::instance()->installEventFilter(this);

    connect(_timerStopHit1, SIGNAL(timeout()), SLOT(stopHit()));
    _timerStopHit1->setInterval(200);
    connect(_timerStopHit2, SIGNAL(timeout()), SLOT(stopHit()));
    _timerStopHit2->setInterval(200);
}

void InputManager::stopHit()
{
    if(sender() == _timerStopHit1)
    {
        _states1 &= ~Character::HittingLeft;
        _states1 &= ~Character::HittingRight;
        emit state1(_states1);
    }
    else if(sender() == _timerStopHit2)
    {
        _states2 &= ~Character::HittingLeft;
        _states2 &= ~Character::HittingRight;
        emit state2(_states2);
    }
}

bool InputManager::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)(event);
        if(! keyEvent->isAutoRepeat())
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
            else if(key == Qt::Key_Enter)
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
                _timerStopHit1->start();
                return true;
            }
            else if(key == Qt::Key_Z)
            {
                _states2 |= Character::Jumping;
                emit state2(_states2);
                return true;
            }
            else if(key == Qt::Key_Q)
            {
                _states2 |= Character::MovingLeft;
                emit state2(_states2);
                return true;
            }
            else if(key == Qt::Key_D)
            {
                _states2 |= Character::MovingRight;
                emit state2(_states2);
                return true;
            }
            else if(key == Qt::Key_Space)
            {
                if(_states2.testFlag(Character::MovingLeft))
                {
                    _states2 |= Character::HittingLeft;
                }
                else
                {
                    _states2 |= Character::HittingRight;
                }
                emit state2(_states2);
                _timerStopHit2->start();
                return true;
            }
        }
    }
    else if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)(event);
        if(! keyEvent->isAutoRepeat())
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
            else if(key == Qt::Key_Enter)
            {
                _states1 &= ~Character::HittingLeft;
                _states1 &= ~Character::HittingRight;
                emit state1(_states1);
                return true;
            }
            else if(key == Qt::Key_Z)
            {
                _states2 &= ~Character::Jumping;
                emit state2(_states2);
                return true;
            }
            else if(key == Qt::Key_Q)
            {
                _states2 &= ~Character::MovingLeft;
                emit state2(_states2);
                return true;
            }
            else if(key == Qt::Key_D)
            {
                _states2 &= ~Character::MovingRight;
                emit state2(_states2);
                return true;
            }
            else if(key == Qt::Key_Space)
            {
                _states2 &= ~Character::HittingLeft;
                _states2 &= ~Character::HittingRight;
                emit state2(_states2);
                return true;
            }
      /*      else if(key == Qt::Key_N)
            {
                g_MainWindow->NextLevel();
            }*/
        }
    }

    return false;
}
