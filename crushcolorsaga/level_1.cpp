#include "level_1.h"

#include "platform.h"

void Level_1::CreateLevelPlatform ( )
{
    addItem(new Platform(QPoint(90,55), 6));
    addItem(new Platform(QPoint(264,55), 6));
    addItem(new Platform(QPoint(8,120), 6));
    addItem(new Platform(QPoint(width()-16*6 -8,120), 6));
    addItem(new Platform(QPoint(144,184), 10));
    addItem(new Platform(QPoint(8,250), 6));
    addItem(new Platform(QPoint(width()-16*6 -8,250), 6));
    addItem(new Platform(QPoint(90,height()-8-16), 6));
    addItem(new Platform(QPoint(264,height()-8-16), 6));
}
