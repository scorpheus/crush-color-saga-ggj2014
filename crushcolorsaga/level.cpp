#include "level.h"

#include "movingprojectorbackground.h"
#include "contour.h"
#include "character.h"
#include "inputmanager.h"
#include "health_display.h"
#include "gameconfiguration.h"
#include "end_level.h"

#include <QElapsedTimer>
#include <QDebug>
#include <QPainter>
#include <QImage>
#include <QTimeLine>
#include <QDebug>

const qreal B2_TIMESTEP = 1/60.0;
const qint32 B2_VELOCITY_ITERATIONS = 6;
const qint32 B2_POSITION_ITERATIONS = 2;

Level::Level(QString level_name, QObject *parent) :
    QGraphicsScene(parent),
    _level_name(level_name),
    _end_level(NULL)
{
    setSceneRect(0, 0, 427, 341);
    startTimer(0);

    addItem(new Contour(this));

    world = new b2World(b2Vec2(0.0f, -1.0f));
    world->SetAllowSleeping(false);
    connect(this, SIGNAL(changed( const QList<QRectF> &)), this, SLOT(level_changed( const QList<QRectF> &)));
}

b2Body* body;

void Level::FinishCreateLevel()
{
    character1 = new Character(GameConfiguration::_id_character1, this, GameConfiguration::_color_character1);
    character1->moveBy(100, 100);
    addItem(character1);

    character2 = new Character(GameConfiguration::_id_character2, this, GameConfiguration::_color_character2);
    character2->moveBy(132, 100);
    addItem(character2);

    b2BodyDef bodyDef;

    bodyDef.type = b2_dynamicBody;

    bodyDef.position.Set(100.0f, 10.0f);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;

    dynamicBox.SetAsBox(32.0f, 32.0f);

    b2FixtureDef fixtureDef;

    fixtureDef.shape = &dynamicBox;

    fixtureDef.density = 10.0f;

    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);// was body.CreateShape(boxDef);

    b2BodyDef groundBodyDef;

    /*Premier niveau à gauche*/
    groundBodyDef.position.Set(90.0f, -342.0f+character1->boundingRect().height()/2);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    /*Dernier niveau à gauche*/
    b2BodyDef groundBodyDef2;
    groundBodyDef2.position.Set(90.0f, -62.0f);
    b2Body* groundBody2 = world->CreateBody(&groundBodyDef2);
    b2PolygonShape groundBox2;
    groundBox2.SetAsBox(50.0f, 10.0f);
    groundBody2->CreateFixture(&groundBox2, 0.0f);

    /*Premier niveau à droite*/
    b2BodyDef groundBodyDef3;
    groundBodyDef3.position.Set(264.0f, -62.0f);
    b2Body* groundBody3 = world->CreateBody(&groundBodyDef3);
    b2PolygonShape groundBox3;
    groundBox3.SetAsBox(50.0f, 10.0f);
    groundBody3->CreateFixture(&groundBox3, 0.0f);

    /*Dernier niveau à droite*/
    b2BodyDef groundBodyDef4;
    groundBodyDef4.position.Set(264.0f, -342.0f+character1->boundingRect().height()/2);
    b2Body* groundBody4 = world->CreateBody(&groundBodyDef4);
    b2PolygonShape groundBox4;
    groundBox4.SetAsBox(50.0f, 10.0f);
    groundBody4->CreateFixture(&groundBox4, 0.0f);

    /*Deuxième niveau à gauche*/
    b2BodyDef groundBodyDef5;
    groundBodyDef5.position.Set(8.0f, -120.0f);
    b2Body* groundBody5 = world->CreateBody(&groundBodyDef5);
    b2PolygonShape groundBox5;
    groundBox5.SetAsBox(50.0f, 10.0f);
    groundBody5->CreateFixture(&groundBox5, 0.0f);

    /*Quatrième niveau à gauche*/
    b2BodyDef groundBodyDef6;
    groundBodyDef6.position.Set(8.0f, -250.0f+character1->boundingRect().height()/2);
    b2Body* groundBody6 = world->CreateBody(&groundBodyDef6);
    b2PolygonShape groundBox6;
    groundBox6.SetAsBox(50.0f, 10.0f);
    groundBody6->CreateFixture(&groundBox6, 0.0f);


    HealthDisplay *health1 = new HealthDisplay(character1);
    addItem(health1);
    health1->moveBy(15, 15);

    HealthDisplay *health2 = new HealthDisplay(character2);
    addItem(health2);
    health2->moveBy(312, 15);

    InputManager *inputManager = new InputManager(this);
    connect(inputManager, SIGNAL(state1(Character::States)), character1, SLOT(setStates(Character::States)));
    connect(inputManager, SIGNAL(state2(Character::States)), character2, SLOT(setStates(Character::States)));

    _background = new Background(); //MovingProjectorBackground();
    _background->setZValue(-100);
    addItem(_background);

    connect(_background, SIGNAL(imageChanged()), character1, SLOT(CheckVulnerabilityColor()));
    connect(_background, SIGNAL(imageChanged()), character2, SLOT(CheckVulnerabilityColor()));
}

void Level::timerEvent(QTimerEvent * event)
{
    world->Step(B2_TIMESTEP, B2_VELOCITY_ITERATIONS, B2_POSITION_ITERATIONS);

    // Update QGraphicsItem's position and rotation from body.
    b2Vec2 position = body->GetPosition();
    float32 angle = body->GetAngle();
    character1->setPos(position.x, -position.y);
    character1->setRotation(-(angle * 360.0) / (2 * 3.14));
    //qDebug() << character1->pos();

    // this is new!
    world->ClearForces();
    // this is new!!
    world->DrawDebugData();
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
