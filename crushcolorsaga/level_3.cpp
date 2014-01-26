#include "level_3.h"

#include "platform.h"

void Level_3::CreateLevelPlatformImpl(const QSize &size)
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
}
