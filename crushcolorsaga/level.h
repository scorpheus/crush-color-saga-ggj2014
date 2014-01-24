#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>

class Level : public QGraphicsScene
{
    Q_OBJECT

    public:
        explicit Level(QObject *parent = 0);
};

#endif // LEVEL_H
