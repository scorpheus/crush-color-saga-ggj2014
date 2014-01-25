#include "level.h"

#include "movingprojectorbackground.h"
#include "contour.h"
#include "character.h"
#include "inputmanager.h"
#include "health_display.h"
#include "gameconfiguration.h"
#include "end_level.h"

#include <QDebug>
#include <QPainter>
#include <QImage>
#include <QTimeLine>

Level::Level(QString level_name, QObject *parent) :
    QGraphicsScene(parent),
    _level_name(level_name),
    _end_level(NULL)
{
    setSceneRect(0, 0, 427, 341);

    addItem(new Contour(this));

    connect(this, SIGNAL(changed( const QList<QRectF> &)), this, SLOT(level_changed( const QList<QRectF> &)));
}

void Level::FinishCreateLevel()
{
    character1 = new Character(GameConfiguration::_id_character1, this, Qt::yellow);
    character1->moveBy(100, 100);
    addItem(character1);

    character2 = new Character(GameConfiguration::_id_character2, this, Qt::blue);
    character2->moveBy(132, 100);
    addItem(character2);

    HealthDisplay *health1 = new HealthDisplay(character1);
    addItem(health1);
    health1->moveBy(15, 15);

    HealthDisplay *health2 = new HealthDisplay(character2);
    addItem(health2);
    health2->moveBy(312, 15);

    InputManager *inputManager = new InputManager(this);
    connect(inputManager, SIGNAL(state1(Character::States)), character1, SLOT(setStates(Character::States)));
    connect(inputManager, SIGNAL(state2(Character::States)), character2, SLOT(setStates(Character::States)));

    //_background = new Background(QImage(QString(":/models/%1").arg(_level_name)));
    _background = new MovingProjectorBackground();
    _background->setZValue(-100);
    addItem(_background);
}

void Level::level_changed( const QList<QRectF> & region )
{
    // check if one of the character died
    if(character1->_Health <= 0)
    {
        if(!_end_level)
        {
            _end_level = new EndLevel(this, "Player 2: YOU WON !!");
            addItem(_end_level);
            _end_level->timer->start();

        }
        return;
    }
    if(character2->_Health <= 0)
    {
        if(!_end_level)
        {
            _end_level = new EndLevel(this, "Player 1: YOU WON !!");
            addItem(_end_level);
            _end_level->timer->start();

        }
        return;
    }
}

QColor Level::GetBackgroundColor(QPoint pos)
{
    return QImage(QString(":/models/%1").arg(_level_name)).pixel(pos);
}
