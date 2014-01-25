#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <QObject>
#include <QTimer>

#include "character.h"

class InputManager : public QObject
{
    Q_OBJECT

    public:
        explicit InputManager(QObject *parent = 0);

        virtual bool eventFilter(QObject *, QEvent *);

    signals:
        void state1(Character::States states);
        void state2(Character::States states);

    private slots:
        void stopHit();

    private:
        Character::States _states1;
        Character::States _states2;
        QTimer *_timerStopHit1;
        QTimer *_timerStopHit2;
};

#endif // INPUTMANAGER_H
