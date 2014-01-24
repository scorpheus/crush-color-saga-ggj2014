#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <QObject>

class InputManager : public QObject
{
    Q_OBJECT

    public:
        explicit InputManager(QObject *parent = 0);

        virtual bool eventFilter(QObject *, QEvent *);

    signals:
        void moveLeft();
        void moveRight();
        void jump();
};

#endif // INPUTMANAGER_H
