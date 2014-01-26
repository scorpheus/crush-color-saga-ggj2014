#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <QObject>
#include <QTimer>

#include "character.h"

class InputManager : public QObject
{
    Q_OBJECT

    public:
        explicit InputManager(Character *character1, Character *character2, QObject *parent = 0);

        virtual bool eventFilter(QObject *, QEvent *);

    private slots:
        void stopHit();

    private:
        Character *_character1;
        Character *_character2;
        QTimer *_timerStopHit1;
        QTimer *_timerStopHit2;
};

#endif // INPUTMANAGER_H
