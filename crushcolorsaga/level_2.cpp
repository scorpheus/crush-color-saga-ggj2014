#include "level_2.h"

#include "platform.h"
#include "level.h"
#include "contour.h"

void Level_2::CreateLevelPlatformImpl(const QSize &size)
{
    Platform *platform = new Platform(5);
    platform->moveBy(0, 0);
    addItem(platform);

    platform = new Platform(5);
    platform->moveBy(0,16);
    addItem(platform);

    platform = new Platform(12);
    platform->moveBy(16*7, 0);
    addItem(platform);

    platform = new Platform(12);
    platform->moveBy(16*7, 16);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(16*21, 0);
    addItem(platform);

    platform = new Platform(6);
    platform->moveBy(16*21, 16);
    addItem(platform);

    for(int i=0; i<11; ++i)
    {
        platform = new Platform(1);
        platform->moveBy(0, 16*2 + 16*i);
        addItem(platform);
        platform = new Platform(2);
        platform->moveBy(16*25, 16*2 + 16*i);
        addItem(platform);
    }
    for(int i=0; i<5; ++i)
    {
        platform = new Platform(5);
        platform->moveBy(0, 16*16 + 16*i);
        addItem(platform);
        platform = new Platform(6);
        platform->moveBy(16*21, 16*16 + 16*i);
        addItem(platform);
    }
    platform = new Platform(12);
    platform->moveBy(16*7, 16*19 );
    addItem(platform);
    platform = new Platform(12);
    platform->moveBy(16*7, 16*20 );
    addItem(platform);

    platform = new Platform(5);
    platform->moveBy(16*6, 16*13 );
    addItem(platform);
    platform = new Platform(5);
    platform->moveBy(16*15, 16*13 );
    addItem(platform);

    platform = new Platform(4);
    platform->moveBy(16, 16*9 );
    addItem(platform);
    platform = new Platform(4);
    platform->moveBy(16*21, 16*9 );
    addItem(platform);

    platform = new Platform(5);
    platform->moveBy(16*6, 16*5 );
    addItem(platform);
    platform = new Platform(5);
    platform->moveBy(16*15, 16*5 );
    addItem(platform);
}

Contour *Level_2::CreateContour()
{
    return new Contour(QList<QRectF>(), this);
}
