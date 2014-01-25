#include "gameconfiguration.h"

#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsPixmapItem>

#include "mainwindow.h"
extern MainWindow* g_MainWindow;

/*static*/ int GameConfiguration::_id_character1 = 1;
/*static*/ int GameConfiguration::_id_character2 = 2;

class GameConfigurationValidate : public QGraphicsSimpleTextItem
{
public:  GameConfigurationValidate( const QString & text, QGraphicsItem * parent = 0 ) : QGraphicsSimpleTextItem(text, parent){};
    protected:
        virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){ g_MainWindow->ChangeLevel(MainWindow::choice_level_1); }
};

class GameConfigurationChar1ArrowPrev : public QGraphicsPixmapItem
{
public:  GameConfigurationChar1ArrowPrev( const QPixmap & pixmap, QGraphicsItem * parent = 0 ) : QGraphicsPixmapItem(pixmap, parent){};
    protected:
        virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){ --GameConfiguration::_id_character1; if(GameConfiguration::_id_character1<1) GameConfiguration::_id_character1 = GameConfiguration::nb_character; }
};

class GameConfigurationChar1ArrowNext : public QGraphicsPixmapItem
{
public:  GameConfigurationChar1ArrowNext( const QPixmap & pixmap, QGraphicsItem * parent = 0 ) : QGraphicsPixmapItem(pixmap, parent){};
    protected:
        virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){ ++GameConfiguration::_id_character1; if(GameConfiguration::_id_character1>GameConfiguration::nb_character) GameConfiguration::_id_character1 = 1; }
    class GameConfigurationChar2ArrowPrev : public QGraphicsPixmapItem
    {
    public:  GameConfigurationChar2ArrowPrev( const QPixmap & pixmap, QGraphicsItem * parent = 0 ) : QGraphicsPixmapItem(pixmap, parent){};
        protected:
            virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){ --GameConfiguration::_id_character2; if(GameConfiguration::_id_character2<1) GameConfiguration::_id_character2 = GameConfiguration::nb_character; }
    };

    class GameConfigurationChar2ArrowNext : public QGraphicsPixmapItem
    {
    public:  GameConfigurationChar2ArrowNext( const QPixmap & pixmap, QGraphicsItem * parent = 0 ) : QGraphicsPixmapItem(pixmap, parent){};
        protected:
            virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){ ++GameConfiguration::_id_character2; if(GameConfiguration::_id_character2>GameConfiguration::nb_character) GameConfiguration::_id_character2 = 1; }
    };


    GameConfiguration::GameConfiguration(QObject *parent) :
        QGraphicsScene(parent),
        _timerAnimation(new QTimer(this)),
        _animationIndex1(0),
        _animationIndex2(0)
    {
        setSceneRect(0, 0, 427, 341);

    connect(this, SIGNAL(selectionChanged()), this, SLOT(SelectionChanged()));

    QGraphicsSimpleTextItem* _text_item_character_1 = addSimpleText("Personnage 1");
    _text_item_character_1->setPos(width()*0.1, height()*0.2);

    QGraphicsSimpleTextItem* _text_item_character_2 = addSimpleText("Personnage 2");
    _text_item_character_2->setPos(width()*0.1, height()*0.3);

    GameConfigurationChar1ArrowPrev* _pixmap_item_character_1_arrow_left = new GameConfigurationChar1ArrowPrev(QPixmap(QString(":/models/select_arrow_left")));
    addItem(_pixmap_item_character_1_arrow_left);
    _pixmap_item_character_1_arrow_left->setPos(width()*0.4, height()*0.2);
    GameConfigurationChar2ArrowPrev* _pixmap_item_character_2_arrow_left = new GameConfigurationChar2ArrowPrev(QPixmap(QString(":/models/select_arrow_left")));
    addItem(_pixmap_item_character_2_arrow_left);
    _pixmap_item_character_2_arrow_left->setPos(width()*0.4, height()*0.3);

    GameConfigurationChar1ArrowNext* _pixmap_item_character_1_arrow_right = new GameConfigurationChar1ArrowNext(QPixmap(QString(":/models/select_arrow_right")));
    addItem(_pixmap_item_character_1_arrow_right);
    _pixmap_item_character_1_arrow_right->setPos(width()*0.7, height()*0.2);
    GameConfigurationChar2ArrowNext* _pixmap_item_character_2_arrow_right = new GameConfigurationChar2ArrowNext(QPixmap(QString(":/models/select_arrow_right")));
    addItem(_pixmap_item_character_2_arrow_right);
    _pixmap_item_character_2_arrow_right->setPos(width()*0.7, height()*0.3);

    _pixmap_item_character_1 = addPixmap(QPixmap(QString(":/models/hero%1_run0%2").arg(_id_character1).arg(_animationIndex1+1)));
    _pixmap_item_character_1->setPos(width()*0.55, height()*0.17);
    _pixmap_item_character_2 = addPixmap(QPixmap(QString(":/models/hero%1_run0%2").arg(_id_character2).arg(_animationIndex2+1)));
    _pixmap_item_character_2->setPos(width()*0.55, height()*0.27);

    _timerAnimation->setInterval(200);
    connect(_timerAnimation, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    _timerAnimation->start();

    QGraphicsSimpleTextItem* _text_item_validate = new GameConfigurationValidate("Valider");
    QGraphicsSimpleTextItem* _text_item_validate = new GameConfigurationValidate("Valider");
    addItem(_text_item_validate);
    _text_item_validate->setScale(2.0);
    QRectF validate_rect = _text_item_validate->boundingRect();
    _text_item_validate->setPos(width()*0.5 - validate_rect.width()*0.5, height()*0.7-validate_rect.height());
}

void GameConfiguration::drawBackground ( QPainter * painter, const QRectF & rect )
{
    painter->drawPixmap(0, 0, QPixmap(QString(":/models/%1").arg("_GameConfiguration_name")));
}

void GameConfiguration::updateAnimation()
{
    _animationIndex1 = (_animationIndex1 + 1) % 2;
    _animationIndex2 = (_animationIndex2 + 1) % 2;

    _pixmap_item_character_1->setPixmap(QPixmap(QString(":/models/hero%1_run0%2").arg(_id_character1).arg(_animationIndex1+1)));
    _pixmap_item_character_2->setPixmap(QPixmap(QString(":/models/hero%1_run0%2").arg(_id_character2).arg(_animationIndex2+1)));
}
