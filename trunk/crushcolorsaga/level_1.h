#ifndef LEVEL_1_H
#define LEVEL_1_H

#include "level.h"

class Level_1 : public Level
{
    Q_OBJECT

    public:
        Level_1(QString level_name, QObject *parent = 0):Level(level_name, parent){};
        virtual void CreateLevelPlatform();
};

#endif // LEVEL_1_H
