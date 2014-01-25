#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>

enum ColorCharacter
{
    BLACK=0,
    WHITE,
    RED,
    GREEN,
    BLUE,
    PURPLE,
    CYAN,
    YELLOW
};

class Level : public QGraphicsScene
{
    Q_OBJECT

    public:
        explicit Level(QString level_name, QObject *parent = 0);

        ColorCharacter GetBackgroundColor(QPoint pos);

protected:
    void drawBackground ( QPainter * painter, const QRectF & rect );

private:
    QString _level_name;
};

#endif // LEVEL_H
