#include "level_2.h"

#include "platform.h"

void Level_2::CreateLevelPlatform ( )
{
    Platform *platform = new Platform(10);
    platform->moveBy(144, 55);
    addItem(platform);

    platform = new Platform(4);
    platform->moveBy(8, 120);
    addItem(platform);

    platform = new Platform(4);
    platform->moveBy(width()-16*6 -8,120);
    addItem(platform);

    platform = new Platform(5);
    platform->moveBy(144,184);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(8,250);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(width()-16*6 -8,250);
    addItem(platform);

    /*addItem(new Platform(QPoint(144,55), 10));
    addItem(new Platform(QPoint(8,120), 4));
    addItem(new Platform(QPoint(width()-16*6 -8,120), 4));
    addItem(new Platform(QPoint(144,184), 5));
    addItem(new Platform(QPoint(8,250), 6));
    addItem(new Platform(QPoint(width()-16*6 -8,250), 6));*/

}
