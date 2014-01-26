#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <Box2D/Box2D.h>
//#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include "character.h"

class Character;
class EndLevel;
class Background;

class Level : public QGraphicsScene
{
    Q_OBJECT

    public:
        explicit Level(QString level_name, QObject *parent = 0);

        QColor GetBackgroundColor(QPoint pos);


        virtual void CreateLevelPlatform()=0;
        virtual void FinishCreateLevel();

    private:
        typedef struct
        {
            b2Body *body;
            QGraphicsItem *item;
            QPointF delta;
        } DynamicSprite;

    private:
        Character *character1;
        Character *character2;
        EndLevel* _end_level;
        Background *_background;
        QString _level_name;
        QList<DynamicSprite> _bodies;

    private:
        QPointF physicalToGraphical(const b2Vec2 &point);
        b2Vec2 graphicalToPhysical(const QPointF &point);
        void punchingChecker();

    public slots:
        void level_changed( const QList<QRectF> & region);

    private slots:
        void registerFireBall(QGraphicsItem *fireBall);
        void characterStatesChanged(Character::States changedStates);

    protected:
        virtual void timerEvent(QTimerEvent *event);
        b2World*  _world;
};

#endif // LEVEL_H
