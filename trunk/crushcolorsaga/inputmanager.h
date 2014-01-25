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
        void moveLeft1();
        void moveRight1();
        void jump1();
        void hit1();
};

#endif // INPUTMANAGER_H
