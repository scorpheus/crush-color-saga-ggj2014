#ifndef LEVEL_2_H
#define LEVEL_2_H

#include "level.h"

class Level_2 : public Level
{
    Q_OBJECT

    public:
        Level_2(QString level_name, QObject *parent = 0):Level(level_name, parent){};
        virtual void CreateLevelPlatformImpl(const QSize &size);

protected:
        virtual Contour *CreateContour();
};

#endif // LEVEL_2_H
