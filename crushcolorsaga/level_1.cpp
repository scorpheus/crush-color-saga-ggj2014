#include "level_1.h"

#include "platform.h"

void Level_1::CreateLevelPlatformImpl(const QSize &size)
{
    Platform *platform = new Platform(6);
    platform->moveBy(90, 55);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(size.width() - platform->boundingRect().width() - 90, 55);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(8, 120);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(width()-16*6 -8, 120);
    addItem(platform);

    platform = new Platform(10);
    platform->moveBy((size.width() - platform->boundingRect().width()) / 2, 184);
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
    platform->moveBy(width() - platform->boundingRect().width() - 90,height()-8-16);
    addItem(platform);
}
