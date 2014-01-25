#ifndef GAMECONFIGURATION_H
#define GAMECONFIGURATION_H

#include <QGraphicsScene>

class GameConfiguration : public QGraphicsScene
{
    Q_OBJECT

    public:
        explicit GameConfiguration(QObject *parent = 0);

    int _animationIndex1;
    int _animationIndex2;
    static int _id_character1;
    static int _id_character2;

    static QColor _color_character1;
    static QColor _color_character2;

    static const int nb_character = 2;
protected:
    void drawBackground ( QPainter * painter, const QRectF & rect );

private:
    QGraphicsPixmapItem* _pixmap_item_character_1;
    QGraphicsPixmapItem* _pixmap_item_character_2;

    QGraphicsRectItem* _pixmap_color_character_1;
    QGraphicsRectItem* _pixmap_color_character_2;

private slots:
    void updateAnimation();

private:
    QTimer *_timerAnimation;


};

#endif // GAMECONFIGURATION_H
