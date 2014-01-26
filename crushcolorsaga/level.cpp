#include "level.h"

#include "movingprojectorbackground.h"
#include "wikimediaimagebackground.h"
#include "contour.h"
#include "character.h"
#include "inputmanager.h"
#include "health_display.h"
#include "gameconfiguration.h"
#include "end_level.h"
#include "platform.h"

#include <QElapsedTimer>
#include <QDebug>
#include <QPainter>
#include <QImage>
#include <QTimeLine>
#include <QDebug>

const qreal B2_TIMESTEP = 1/60.0;
const qint32 B2_VELOCITY_ITERATIONS = 6;
const qint32 B2_POSITION_ITERATIONS = 2;
const qreal SCALE = 50.0;


Level::Level(QString level_name, QObject *parent) :
    QGraphicsScene(parent),
    _level_name(level_name),
    _end_level(NULL),
    _bodies()
{
    setSceneRect(0, 0, 427, 341);
    startTimer(0);

    addItem(new Contour(this));

    _world = new b2World(b2Vec2(0.0f, -9.8f));
    _world->SetAllowSleeping(false);
    connect(this, SIGNAL(changed( const QList<QRectF> &)), this, SLOT(level_changed( const QList<QRectF> &)));
}

void Level::FinishCreateLevel()
{
    // Register platform physics
    foreach(QGraphicsItem *item, items())
    {
        if(item->type() == QGraphicsItem::UserType + 100)
        {
            Platform *platform = (Platform *)item;

            b2BodyDef bodyDefPlatform;
            QPointF center = platform->boundingRect().translated(platform->pos()).center();
            bodyDefPlatform.position = graphicalToPhysical(center);
            b2Body* bodyPlatform = _world->CreateBody(&bodyDefPlatform);
            b2PolygonShape boxPlatform;
            boxPlatform.SetAsBox(platform->boundingRect().width() / (2.0 * SCALE),
                                 platform->boundingRect().height() / (2.0 * SCALE));
            bodyPlatform->CreateFixture(&boxPlatform, 0.0f);
        }
    }

  /*  b2BodyDef bodyDefBottomBorder;
    QPointF center =*/

    // Register charachter 1
    character1 = new Character(GameConfiguration::_id_character1, this, GameConfiguration::_color_character1);
    addItem(character1);

    b2BodyDef bodyDefChar1;
    bodyDefChar1.type = b2_dynamicBody;
    bodyDefChar1.position = graphicalToPhysical(QPointF(70.0f, 10.0f));
    bodyDefChar1.fixedRotation = true;

    b2Body *bodyChar1 = _world->CreateBody(&bodyDefChar1);

    b2PolygonShape dynamicBoxChar1;
    dynamicBoxChar1.SetAsBox(32.0f / (2 * SCALE), 32.0f / (2 * SCALE));

    b2FixtureDef fixtureDefChar1;
    fixtureDefChar1.shape = &dynamicBoxChar1;
    fixtureDefChar1.density = 10.0f;
    fixtureDefChar1.friction = 0.5f;
    bodyChar1->CreateFixture(&fixtureDefChar1);

    _bodies << qMakePair(bodyChar1, (QGraphicsItem *)(character1));

    // Register character 1
    character2 = new Character(GameConfiguration::_id_character2, this, GameConfiguration::_color_character2);
    addItem(character2);

    b2BodyDef bodyDefChar2;
    bodyDefChar2.type = b2_dynamicBody;
    bodyDefChar2.position = graphicalToPhysical(QPointF(220.0f, 10.0f));
    bodyDefChar2.fixedRotation = true;

    b2Body *bodyChar2 = _world->CreateBody(&bodyDefChar2);

    b2PolygonShape dynamicBoxChar2;
    dynamicBoxChar2.SetAsBox(32.0f / (2 * SCALE), 32.0f / (2 * SCALE));

    b2FixtureDef fixtureDefChar2;
    fixtureDefChar2.shape = &dynamicBoxChar2;
    fixtureDefChar2.density = 10.0f;
    fixtureDefChar2.friction = 0.5f;
    bodyChar2->CreateFixture(&fixtureDefChar2);

    _bodies << qMakePair(bodyChar2, (QGraphicsItem *)(character2));

    HealthDisplay *health1 = new HealthDisplay(character1);
    addItem(health1);
    health1->moveBy(15, 15);

    HealthDisplay *health2 = new HealthDisplay(character2);
    addItem(health2);
    health2->moveBy(312, 15);

    InputManager *inputManager = new InputManager(this);
    connect(inputManager, SIGNAL(state1(Character::States)), character1, SLOT(setStates(Character::States)));
    connect(inputManager, SIGNAL(state2(Character::States)), character2, SLOT(setStates(Character::States)));

    //_background = new Background();
     _background = new MovingProjectorBackground();
    //_background = new WikimediaImageBackground();
    _background->setZValue(-100);
    addItem(_background);

    connect(_background, SIGNAL(imageChanged()), character1, SLOT(CheckVulnerabilityColor()));
    connect(_background, SIGNAL(imageChanged()), character2, SLOT(CheckVulnerabilityColor()));
}

QPointF Level::physicalToGraphical(const b2Vec2 &point)
{
    return QPointF(point.x * SCALE, height() - (point.y * SCALE));
}

b2Vec2 Level::graphicalToPhysical(const QPointF &point)
{
    return b2Vec2(point.x() / SCALE, (height() - point.y()) / SCALE);
}

void Level::timerEvent(QTimerEvent * event)
{
    _world->Step(B2_TIMESTEP, B2_VELOCITY_ITERATIONS, B2_POSITION_ITERATIONS);

    for(int i=0 ; i<_bodies.count() ; i++)
    {
        b2Vec2 position = _bodies[i].first->GetPosition();
        float32 angle = _bodies[i].first->GetAngle();
        QSizeF boundingSize = _bodies[i].second->boundingRect().size();
        _bodies[i].second->setPos(physicalToGraphical(position) - QPointF(boundingSize.width()/2, boundingSize.height()/2));
        _bodies[i].second->setRotation(-(angle * 360.0) / (2 * 3.14));
        //inside Step()
        b2Vec2 vel = _bodies[i].first->GetLinearVelocity();

        Character::States characterState = ((Character *)(_bodies[i].second))->getStates();

        if(characterState.testFlag(Character::MovingLeft))
        {
          vel.x = -1;
        }
        if(characterState.testFlag(Character::MovingRight))
        {
          vel.x = +1;
        }
        if(characterState.testFlag(Character::Idle))
        {
          vel.x = 0;
        }

        _bodies[i].first->SetLinearVelocity( vel );
        qDebug() << vel.x << vel.y;
    }

    _world->ClearForces();
    _world->DrawDebugData();
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
    return _background->colorAt(pos);
}
