#include "level_3.h"

#include "platform.h"

void Level_3::CreateLevelPlatform ( )
{
    Platform *platform = new Platform(6);
    platform->moveBy(90, 55);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(264, 55);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(8, 120);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(width()-16*6 -8, 120);
    addItem(platform);

    platform = new Platform(10);
    platform->moveBy(144, 184);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(8, 250);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(width()-16*6 -8,250);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(90,height()-8-16);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(264,height()-8-16);
    addItem(platform);

    /*addItem(new Platform(QPoint(90,55), 6));
    addItem(new Platform(QPoint(264,55), 6));
    addItem(new Platform(QPoint(8,120), 6));
    addItem(new Platform(QPoint(width()-16*6 -8,120), 6));
    addItem(new Platform(QPoint(144,184), 10));
    addItem(new Platform(QPoint(8,250), 6));
    addItem(new Platform(QPoint(width()-16*6 -8,250), 6));
    addItem(new Platform(QPoint(90,height()-8-16), 6));
    addItem(new Platform(QPoint(264,height()-8-16), 6));*/
}
