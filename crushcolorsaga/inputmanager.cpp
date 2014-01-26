#include "inputmanager.h"

#include <QCoreApplication>
#include <QKeyEvent>

#include "mainwindow.h"
extern MainWindow* g_MainWindow;

InputManager::InputManager(Character *character1, Character *character2, QObject *parent) :
    QObject(parent),
    _character1(character1),
    _character2(character2),
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
        Character::States states1 = _character1->getStates();
        states1 &= ~Character::Attack;
        _character1->setStates(states1);
    }
    else if(sender() == _timerStopHit2)
    {
        Character::States states2 = _character2->getStates();
        states2 &= ~Character::Attack;
        _character2->setStates(states2);
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
                _character1->setStates(_character1->getStates() | Character::Jumping);
                return true;
            }
            else if(key == Qt::Key_Left)
            {
                _character1->setStates(_character1->getStates() | Character::MovingLeft);
                return true;
            }
            else if(key == Qt::Key_Right)
            {
                _character1->setStates(_character1->getStates() | Character::MovingRight);
                return true;
            }
            else if(key == Qt::Key_Enter)
            {
                Character::States states1 = _character1->getStates();
                if(states1.testFlag(Character::MovingLeft))
                {
                    if(_character1->getShield() >= Character::VeryStronger)
                    {
                        states1 |= Character::ThrowingLeft;
                    }
                    else
                    {
                        states1 |= Character::HittingLeft;
                    }
                }
                else
                {
                    if(_character1->getShield() >= Character::VeryStronger)
                    {
                        states1 |= Character::ThrowingRight;
                    }
                    else
                    {
                        states1 |= Character::HittingRight;
                    }
                }
                _character1->setStates(states1);
                _timerStopHit1->start();
                return true;
            }
            else if(key == Qt::Key_Z)
            {
                _character2->setStates(_character2->getStates() | Character::Jumping);
                return true;
            }
            else if(key == Qt::Key_Q)
            {
                _character2->setStates(_character2->getStates() | Character::MovingLeft);
                return true;
            }
            else if(key == Qt::Key_D)
            {
                _character2->setStates(_character2->getStates() | Character::MovingRight);
                return true;
            }
            else if(key == Qt::Key_Space)
            {
                Character::States states2 = _character2->getStates();
                if(states2.testFlag(Character::MovingLeft))
                {
                    if(_character2->getShield() >= Character::VeryStronger)
                    {
                        states2 |= Character::ThrowingLeft;
                    }
                    else
                    {
                        states2 |= Character::HittingLeft;
                    }
                }
                else
                {
                    if(_character2->getShield() >= Character::VeryStronger)
                    {
                        states2 |= Character::ThrowingRight;
                    }
                    else
                    {
                        states2 |= Character::HittingRight;
                    }
                }
                _character2->setStates(states2);
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
                _character1->setStates(_character1->getStates() & ~Character::Jumping);
                return true;
            }
            else if(key == Qt::Key_Left)
            {
                _character1->setStates(_character1->getStates() & ~Character::MovingLeft);
                return true;
            }
            else if(key == Qt::Key_Right)
            {
                _character1->setStates(_character1->getStates() & ~Character::MovingRight);
                return true;
            }
            else if(key == Qt::Key_Enter)
            {
                _character1->setStates(_character1->getStates() & ~Character::Attack);
                return true;
            }
            else if(key == Qt::Key_Z)
            {
                _character2->setStates(_character2->getStates() & ~Character::Jumping);
                return true;
            }
            else if(key == Qt::Key_Q)
            {
                _character2->setStates(_character2->getStates() & ~Character::MovingLeft);
                return true;
            }
            else if(key == Qt::Key_D)
            {
                _character2->setStates(_character2->getStates() & ~Character::MovingRight);
                return true;
            }
            else if(key == Qt::Key_Space)
            {
                _character2->setStates(_character2->getStates() & ~(Character::Attack));
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
