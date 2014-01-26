#ifndef LEVEL_3_H
#define LEVEL_3_H

#include "level.h"

class Level_3 : public Level
{
    Q_OBJECT

    public:
        Level_3(QString level_name, QObject *parent = 0):Level(level_name, parent){};
        virtual void CreateLevelPlatform();
};

#endif // LEVEL_3_H
