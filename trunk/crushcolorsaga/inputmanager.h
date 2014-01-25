#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <QObject>

#include "character.h"

class InputManager : public QObject
{
    Q_OBJECT

    public:
        explicit InputManager(QObject *parent = 0);

        virtual bool eventFilter(QObject *, QEvent *);

    signals:
        void state1(Character::States states);

    private:
        Character::States _states1;
};

#endif // INPUTMANAGER_H
