#include "level.h"

#include "movingprojectorbackground.h"
#include "movingprojectorbackground_level3.h"
#include "wikimediaimagebackground.h"
#include "contour.h"
#include "character.h"
#include "inputmanager.h"
#include "health_display.h"
#include "gameconfiguration.h"
#include "end_level.h"
#include "platform.h"
#include "fireball.h"
#include "blowup.h"
#include "soundmanager.h"

#include <QElapsedTimer>
#include <QDebug>
#include <QPainter>
#include <QImage>
#include <QTimeLine>
#include <QDebug>

#include "mainwindow.h"
extern MainWindow* g_MainWindow;

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
    setSceneRect(0, 0, SCENEWIDTH, SCENEHEIGHT);
    startTimer(1000 / 60);

    _world = new b2World(b2Vec2(0.0f, -7.0f));
    _world->SetAllowSleeping(false);
    connect(this, SIGNAL(changed( const QList<QRectF> &)), this, SLOT(level_changed( const QList<QRectF> &)));
}

Level::~Level()
{
    delete _world;
}

void Level::CreateLevelPlatform()
{
    CreateLevelPlatformImpl(QSize(SCENEWIDTH, SCENEHEIGHT));
}

Contour *Level::CreateContour()
{
    QList<QRectF> borders;
    borders << QRectF(0, 0, SCENEWIDTH, 8);
    borders << QRectF(0, SCENEHEIGHT - 8, SCENEWIDTH, 8);
    borders << QRectF(0, 8, 8, SCENEHEIGHT - 16);
    borders << QRectF(SCENEWIDTH - 8, 8, 8, SCENEHEIGHT - 16);

    return new Contour(borders, this);
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
            bodyPlatform->CreateFixture(&boxPlatform, 0.0f)->SetFriction(0.3);
        }
    }

    // Register borders
    Contour *contour = CreateContour();
    contour->setZValue(-50);
    addItem(contour);
    foreach(const QRectF &border, contour->getBorders())
    {
        b2BodyDef bodyDefBorder;
        bodyDefBorder.position = graphicalToPhysical(border.center());
        b2Body* bodyBorder = _world->CreateBody(&bodyDefBorder);
        b2PolygonShape boxBorder;
        boxBorder.SetAsBox(border.width() / (2 * SCALE),
                           border.height() / (2 * SCALE));
        bodyBorder->CreateFixture(&boxBorder, 0.0f);
    }

    // Register character 1
    character1 = new Character(GameConfiguration::_id_character2, this, GameConfiguration::_color_character1);
    connect(character1, SIGNAL(registerFireBall(QGraphicsItem*,bool,Qt::LayoutDirection)),
                        SLOT(registerFireBall(QGraphicsItem*,bool,Qt::LayoutDirection)));
    connect(character1, SIGNAL(statesChanged(Character::States)), SLOT(characterStatesChanged(Character::States)));
    addItem(character1);

    b2BodyDef bodyDefChar1;
    bodyDefChar1.type = b2_dynamicBody;
    bodyDefChar1.position = graphicalToPhysical(QPointF(220.0f, 60.0f));
    bodyDefChar1.fixedRotation = true;

    b2Body *bodyChar1 = _world->CreateBody(&bodyDefChar1);

    b2PolygonShape dynamicBoxChar1;
    dynamicBoxChar1.SetAsBox(14.0f / (2 * SCALE), 26.0f / (2 * SCALE));

    b2FixtureDef fixtureDefChar1;
    fixtureDefChar1.shape = &dynamicBoxChar1;
    fixtureDefChar1.density = 25.0f;
    fixtureDefChar1.friction = 0.3f;
    bodyChar1->CreateFixture(&fixtureDefChar1);

    DynamicSprite sprite1;
    sprite1.body = bodyChar1;
    sprite1.item = character1;
    sprite1.delta = QPointF(18, 21);
    _bodies << sprite1;

    // Register character 2
    character2 = new Character(GameConfiguration::_id_character1, this, GameConfiguration::_color_character2);
    connect(character2, SIGNAL(registerFireBall(QGraphicsItem*,bool,Qt::LayoutDirection)),
                        SLOT(registerFireBall(QGraphicsItem*,bool,Qt::LayoutDirection)));
    connect(character2, SIGNAL(statesChanged(Character::States)), SLOT(characterStatesChanged(Character::States)));
    addItem(character2);

    b2BodyDef bodyDefChar2;
    bodyDefChar2.type = b2_dynamicBody;
    bodyDefChar2.position = graphicalToPhysical(QPointF(220.0f, 60.0f));
    bodyDefChar2.position = graphicalToPhysical(QPointF(70.0f, 10.0f));
    bodyDefChar2.fixedRotation = true;

    b2Body *bodyChar2 = _world->CreateBody(&bodyDefChar2);

    b2PolygonShape dynamicBoxChar2;
    dynamicBoxChar2.SetAsBox(14.0f / (2 * SCALE), 26.0f / (2 * SCALE));

    b2FixtureDef fixtureDefChar2;
    fixtureDefChar2.shape = &dynamicBoxChar2;
    fixtureDefChar2.density = 25.0f;
    fixtureDefChar2.friction = 0.3f;
    bodyChar2->CreateFixture(&fixtureDefChar2);

    DynamicSprite sprite2;
    sprite2.body = bodyChar2;
    sprite2.item = character2;
    sprite2.delta = QPointF(18, 21);
    _bodies << sprite2;

    HealthDisplay *health1 = new HealthDisplay(character2);
    addItem(health1);
    health1->moveBy(15, 15);

    HealthDisplay *health2 = new HealthDisplay(character1);
    addItem(health2);
    health2->moveBy(SCENEWIDTH - health2->boundingRect().width() - 15, 15);

    new InputManager(character1, character2, this);

    if(g_MainWindow->_current_level == g_MainWindow->choice_level_2)
        _background = new MovingProjectorBackground_Level3(_level_name);
    else
    if(g_MainWindow->_current_level == g_MainWindow->choice_level_3)
        _background = new WikimediaImageBackground();
    else
        _background = new MovingProjectorBackground();

    //_background = new Background();
  //   _background = new MovingProjectorBackground();
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

void Level::punchingChecker()
{
    QRectF body1Rect = _bodies[0].item->boundingRect();
    QRectF body2Rect = _bodies[1].item->boundingRect();

    body1Rect.translate(_bodies[0].item->pos());
    body2Rect.translate(_bodies[1].item->pos());

    int damageDone = 1;

    if(body1Rect.intersects(body2Rect))
    {
        if(body1Rect.x() > body2Rect.x())
        {
            if(((Character*)_bodies[0].item)->getStates().testFlag(Character::HittingLeft))
            {
                if(((Character*)_bodies[0].item)->getShield() == Character::Stronger)
                {
                    damageDone = 3;
                }
                else
                {
                    damageDone = 1;
                }
                b2Vec2 vel = _bodies[1].body->GetLinearVelocity();
                vel.y = 10.0;
                vel.x = -10.0;
                _bodies[1].body->SetLinearVelocity( vel );
                character2->setCharacterHealth(character2->getCharacterHealth() - damageDone);
                //qDebug() << ((Character*)_bodies[1].item)->getCharacterHealth();
            }
            else if(((Character*)_bodies[1].item)->getStates().testFlag(Character::HittingRight))
            {
                if(((Character*)_bodies[1].item)->getShield() == Character::Stronger)
                {
                    damageDone = 3;
                }
                else
                {
                    damageDone = 1;
                }
                b2Vec2 vel = _bodies[0].body->GetLinearVelocity();
                vel.y = 10.0;
                vel.x = 10.0;
                _bodies[0].body->SetLinearVelocity( vel );
                character1->setCharacterHealth(character1->getCharacterHealth() - damageDone);
               // qDebug() << ((Character*)_bodies[0].item)->getCharacterHealth();
            }
        }
        else if(body1Rect.x() < body2Rect.x())
        {
            if(((Character*)_bodies[1].item)->getStates().testFlag(Character::HittingLeft))
            {
                if(((Character*)_bodies[1].item)->getShield() == Character::Stronger)
                {
                    damageDone = 3;
                }
                else
                {
                    damageDone = 1;
                }
                b2Vec2 vel = _bodies[0].body->GetLinearVelocity();
                vel.y = 10.0;
                vel.x = -10.0;
                _bodies[0].body->SetLinearVelocity( vel );
                character1->setCharacterHealth(character1->getCharacterHealth() - damageDone);
               // qDebug() << ((Character*)_bodies[0].item)->getCharacterHealth();
            }
            else if(((Character*)_bodies[0].item)->getStates().testFlag(Character::HittingRight))
            {
                if(((Character*)_bodies[0].item)->getShield() == Character::Stronger)
                {
                    damageDone = 3;
                }
                else
                {
                    damageDone = 1;
                }
                b2Vec2 vel = _bodies[1].body->GetLinearVelocity();
                vel.y = 10.0;
                vel.x = 10.0;
                _bodies[1].body->SetLinearVelocity( vel );
                character2->setCharacterHealth(character2->getCharacterHealth() - damageDone);
               // qDebug() << ((Character*)_bodies[0].item)->getCharacterHealth();
            }
        }
    }
}

void Level::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    for(int i=0 ; i<_bodies.count() ; i++)
    {
        if(_bodies[i].item->type() == QGraphicsItem::UserType + 101)
        {
            Character *character = (Character *)_bodies[i].item;
            Character::States characterState = character->getStates();

            b2Vec2 vel = _bodies[i].body->GetLinearVelocity();
            vel.x = 0;

            if(characterState.testFlag(Character::MovingLeft))
            {
                vel.x -= 3;
            }
            if(characterState.testFlag(Character::MovingRight))
            {
                vel.x += 3;
            }

            _bodies[i].body->SetLinearVelocity(vel);
        }
    }

    _world->Step(B2_TIMESTEP, B2_VELOCITY_ITERATIONS, B2_POSITION_ITERATIONS);

    QMutableListIterator<DynamicSprite> iterator(_bodies);
    while(iterator.hasNext())
    {
        DynamicSprite &sprite = iterator.next();
        b2Vec2 position = sprite.body->GetPosition();
        float32 angle = sprite.body->GetAngle();
        sprite.item->setPos(physicalToGraphical(position) - sprite.delta);
        sprite.item->setRotation(-(angle * 360.0) / (2 * 3.14));

        if(sprite.item->type() == QGraphicsItem::UserType + 102)
        {
            qreal speed = qAbs(sprite.body->GetLinearVelocity().x);
            if(speed < 0.95)
            {
                FireBall *fireBall = (FireBall *)sprite.item;
                QRectF fireRect = sprite.item->boundingRect().translated(sprite.item->pos());

                // Blow up
                BlowUp *blowUp = new BlowUp(fireBall->getColor());
                blowUp->setPos(fireBall->pos() - QPoint(4, 4));
                addItem(blowUp);

                // Hurt enemy, if any
                Character *enemy = character2;
                if(((FireBall *)sprite.item)->getOwner() == character2)
                {
                    enemy = character1;
                }

                QRectF enemyRect = enemy->boundingRect().translated(enemy->pos());
                if(fireRect.intersects(enemyRect))
                {
                    SoundManager::PlayHitTaken();
                    int delta = fireBall->isSuperPower() ? 10 : 5;
                    enemy->setCharacterHealth(enemy->getCharacterHealth() - delta);
                }

                // Remove fire ball
                delete sprite.item;
                _world->DestroyBody(sprite.body);
                iterator.remove();

                // play explosion
                SoundManager::PlayExplosion();
            }
        }
    }

    checkCharactersOutside();

    punchingChecker();

    _world->ClearForces();
    _world->DrawDebugData();
}

void Level::checkCharactersOutside()
{
    for(int i=0 ; i<_bodies.count() ; i++)
    {
        if(_bodies[i].item->type() == QGraphicsItem::UserType + 101)
        {
            Character *character = (Character *)_bodies[i].item;
            QPointF pos = character->pos();
            QPointF center = character->boundingRect().translated(character->pos()).center();
            QPointF newPosition;

            if(center.x() > SCENEWIDTH)
            {
                newPosition = pos - QPointF(SCENEWIDTH, 0);
            }
            else if(center.x() < 0)
            {
                newPosition = pos + QPointF(SCENEWIDTH, 0);
            }

            if(center.y() > SCENEHEIGHT)
            {
                newPosition = pos - QPointF(0, SCENEHEIGHT);
            }
            else if(center.y() < 0)
            {
                newPosition = pos + QPointF(0, SCENEHEIGHT);
            }

            if(! newPosition.isNull())
            {
                _bodies[i].body->SetTransform(graphicalToPhysical(newPosition + _bodies[i].delta), 0);
            }
        }
    }
}

void Level::level_changed( const QList<QRectF> & region )
{
    Q_UNUSED(region);
    // check if one of the character died
    if(character1->_Health <= 0)
    {
        if(!_end_level)
        {
            _end_level = new EndLevel(this, "Player 1: YOU WON !!");
            _end_level->hide();
            addItem(_end_level);
            _end_level->show();
            _end_level->timer->start();

        }
        return;
    }
    if(character2->_Health <= 0)
    {
        if(!_end_level)
        {
            _end_level = new EndLevel(this, "Player 2: YOU WON !!");
            _end_level->hide();
            addItem(_end_level);
            _end_level->show();
            _end_level->timer->start();

        }
        return;
    }
}

void Level::registerFireBall(QGraphicsItem *fireBall, bool superPower, Qt::LayoutDirection direction)
{
    addItem(fireBall);

    b2BodyDef bodyDefFireBall;
    bodyDefFireBall.type = b2_dynamicBody;
    bodyDefFireBall.position = graphicalToPhysical(fireBall->pos());
    bodyDefFireBall.fixedRotation = true;
    bodyDefFireBall.gravityScale = 0;

    b2Body *bodyFireBall = _world->CreateBody(&bodyDefFireBall);

    b2PolygonShape dynamicBoxFireBall;
    dynamicBoxFireBall.SetAsBox(fireBall->boundingRect().width() / (2 * SCALE),
                                fireBall->boundingRect().height() / (2 * SCALE));

    b2FixtureDef fixtureDefFireBall;
    fixtureDefFireBall.shape = &dynamicBoxFireBall;
    fixtureDefFireBall.density = 0.0f;
    fixtureDefFireBall.friction = 0.0f;
    bodyFireBall->CreateFixture(&fixtureDefFireBall);

    qreal factor = direction == Qt::LeftToRight ? 1.0 : -1.0;
    bodyFireBall->SetLinearVelocity(b2Vec2((superPower ? 10 : 5) * factor, 0));

    DynamicSprite spriteBall;
    spriteBall.body = bodyFireBall;
    spriteBall.item = fireBall;
    spriteBall.delta = QPointF(fireBall->boundingRect().width(), fireBall->boundingRect().height()) / 2;
    _bodies << spriteBall;
}

void Level::characterStatesChanged(Character::States changedStates)
{
    Character *character = (Character *)sender();
    Character::States characterState = character->getStates();

    for(int i=0 ; i<_bodies.count() ; i++)
    {
        if(_bodies[i].item == character)
        {
            if(changedStates.testFlag(Character::Jumping) && characterState.testFlag(Character::Jumping))
            {
                float impulse = _bodies[i].body->GetMass() * 5;
                _bodies[i].body->ApplyLinearImpulse(b2Vec2(0,impulse), _bodies[i].body->GetWorldCenter(), true);
            }
        }
    }
}

QColor Level::GetBackgroundColor(QPoint pos)
{
    return _background->colorAt(pos);
}
