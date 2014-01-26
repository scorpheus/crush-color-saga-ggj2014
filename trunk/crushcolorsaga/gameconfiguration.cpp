#include "gameconfiguration.h"

#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsPixmapItem>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QLabel>
#include <QMovie>
#include <QGraphicsProxyWidget>
#include <QtCore/qmath.h>


#include "mainwindow.h"
extern MainWindow* g_MainWindow;

/*static*/ int GameConfiguration::_id_character1 = 1;
/*static*/ int GameConfiguration::_id_character2 = 2;

/*static*/ MainWindow::AllLevel GameConfiguration::_stage = MainWindow::choice_level_2;

/*static*/ QColor GameConfiguration::_color_character1 = Qt::red;
/*static*/ QColor GameConfiguration::_color_character2 = Qt::blue;

class GameConfigurationValidate : public QGraphicsPixmapItem
{
public:  GameConfigurationValidate( const QPixmap & pixmap, QGraphicsItem * parent = 0 ) : QGraphicsPixmapItem(pixmap, parent){};
    protected:
        virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){ g_MainWindow->ChangeLevel(GameConfiguration::_stage); }
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
};

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

class GameConfigurationStageArrowPrev : public QGraphicsPixmapItem
{
public:  GameConfigurationStageArrowPrev( const QPixmap & pixmap, QGraphicsItem * parent = 0 ) : QGraphicsPixmapItem(pixmap, parent){};
    protected:
        virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){
        switch(GameConfiguration::_stage)
        {
            case MainWindow::choice_level_1:
               GameConfiguration::_stage = MainWindow::choice_level_3;
            break;
            case MainWindow::choice_level_2:
                GameConfiguration::_stage = MainWindow::choice_level_1;
            break;
            case MainWindow::choice_level_3:
                GameConfiguration::_stage = MainWindow::choice_level_2;
            break;
        }}
};

class GameConfigurationStageArrowNext : public QGraphicsPixmapItem
{
public:  GameConfigurationStageArrowNext( const QPixmap & pixmap, QGraphicsItem * parent = 0 ) : QGraphicsPixmapItem(pixmap, parent){};
    protected:
        virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){
        switch(GameConfiguration::_stage)
        {
            case MainWindow::choice_level_1:
               GameConfiguration::_stage = MainWindow::choice_level_2;
            break;
            case MainWindow::choice_level_2:
                GameConfiguration::_stage = MainWindow::choice_level_3;
            break;
            case MainWindow::choice_level_3:
                GameConfiguration::_stage = MainWindow::choice_level_1;
            break;
        }}
};

//*****************************************************************************************************************

QColor FindNextColor(QColor color)
{
    const QColor _array_color[] = {Qt::red, Qt::green, Qt::blue};
    for(int i=0; i< 3; ++i)
        if(_array_color[i] == color)
        {
            if(i >= 2)
                return _array_color[0];
            else
                return _array_color[i+1];
        }
    return _array_color[0];
}
QColor FindPreviousColor(QColor color)
{
    const QColor _array_color[] = {Qt::red, Qt::green, Qt::blue};
    for(int i=0; i< 3; ++i)
        if(_array_color[i] == color)
        {
            if(i <= 0)
                return _array_color[2];
            else
                return _array_color[i-1];
        }
    return _array_color[0];
}

class GameConfigurationChar1ColorArrowPrev : public QGraphicsPixmapItem
{
public:  GameConfigurationChar1ColorArrowPrev( const QPixmap & pixmap, QGraphicsItem * parent = 0 ) : QGraphicsPixmapItem(pixmap, parent){};
    protected:
        virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){ GameConfiguration::_color_character1 = FindPreviousColor(GameConfiguration::_color_character1);  }
};

class GameConfigurationChar1ColorArrowNext : public QGraphicsPixmapItem
{
public:  GameConfigurationChar1ColorArrowNext( const QPixmap & pixmap, QGraphicsItem * parent = 0 ) : QGraphicsPixmapItem(pixmap, parent){};
    protected:
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){ GameConfiguration::_color_character1 = FindNextColor(GameConfiguration::_color_character1); }
};

class GameConfigurationChar2ColorArrowPrev : public QGraphicsPixmapItem
{
public:  GameConfigurationChar2ColorArrowPrev( const QPixmap & pixmap, QGraphicsItem * parent = 0 ) : QGraphicsPixmapItem(pixmap, parent){};
    protected:
        virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){ GameConfiguration::_color_character2 = FindPreviousColor(GameConfiguration::_color_character2);  }
};

class GameConfigurationChar2ColorArrowNext : public QGraphicsPixmapItem
{
public:  GameConfigurationChar2ColorArrowNext( const QPixmap & pixmap, QGraphicsItem * parent = 0 ) : QGraphicsPixmapItem(pixmap, parent){};
    protected:
        virtual void mousePressEvent ( QGraphicsSceneMouseEvent * ){ GameConfiguration::_color_character2 = FindNextColor(GameConfiguration::_color_character2); }
};


GameConfiguration::GameConfiguration(QObject *parent) :
    QGraphicsScene(parent),
    _timerAnimation(new QTimer(this)),
    _animationIndex1(0),
    _animationIndex2(0)
{
        setSceneRect(0, 0, 427, 341);

    GameConfigurationChar1ArrowPrev* _pixmap_item_character_1_arrow_left = new GameConfigurationChar1ArrowPrev(QPixmap(QString(":/models/select_arrow_left")));
    addItem(_pixmap_item_character_1_arrow_left);
    _pixmap_item_character_1_arrow_left->setPos(67, 189);
    GameConfigurationChar2ArrowPrev* _pixmap_item_character_2_arrow_left = new GameConfigurationChar2ArrowPrev(QPixmap(QString(":/models/select_arrow_left")));
    addItem(_pixmap_item_character_2_arrow_left);
    _pixmap_item_character_2_arrow_left->setPos(293, 189);

    GameConfigurationChar1ArrowNext* _pixmap_item_character_1_arrow_right = new GameConfigurationChar1ArrowNext(QPixmap(QString(":/models/select_arrow_right")));
    addItem(_pixmap_item_character_1_arrow_right);
    _pixmap_item_character_1_arrow_right->setPos(107, 189);
    GameConfigurationChar2ArrowNext* _pixmap_item_character_2_arrow_right = new GameConfigurationChar2ArrowNext(QPixmap(QString(":/models/select_arrow_right")));
    addItem(_pixmap_item_character_2_arrow_right);
    _pixmap_item_character_2_arrow_right->setPos(333, 189);

    //*****************************************************************

    GameConfigurationChar1ColorArrowPrev* _pixmap_item_character_1_color_arrow_left = new GameConfigurationChar1ColorArrowPrev(QPixmap(QString(":/models/select_arrow_left")));
    addItem(_pixmap_item_character_1_color_arrow_left);
    _pixmap_item_character_1_color_arrow_left->setPos(67, 234);
    GameConfigurationChar2ColorArrowPrev* _pixmap_item_character_2_color_arrow_left = new GameConfigurationChar2ColorArrowPrev(QPixmap(QString(":/models/select_arrow_left")));
    addItem(_pixmap_item_character_2_color_arrow_left);
    _pixmap_item_character_2_color_arrow_left->setPos(293, 234);

    GameConfigurationChar1ColorArrowNext* _pixmap_item_character_1_color_arrow_right = new GameConfigurationChar1ColorArrowNext(QPixmap(QString(":/models/select_arrow_right")));
    addItem(_pixmap_item_character_1_color_arrow_right);
    _pixmap_item_character_1_color_arrow_right->setPos(107, 234);
    GameConfigurationChar2ColorArrowNext* _pixmap_item_character_2_color_arrow_right = new GameConfigurationChar2ColorArrowNext(QPixmap(QString(":/models/select_arrow_right")));
    addItem(_pixmap_item_character_2_color_arrow_right);
    _pixmap_item_character_2_color_arrow_right->setPos(333, 234);

    //*****************************************************************

    GameConfigurationStageArrowPrev* _pixmap_item_stage_color_arrow_left = new GameConfigurationStageArrowPrev(QPixmap(QString(":/models/select_arrow_left")));
    addItem(_pixmap_item_stage_color_arrow_left);
    _pixmap_item_stage_color_arrow_left->setPos(163,238);
    GameConfigurationStageArrowNext* _pixmap_item_stage_color_arrow_right = new GameConfigurationStageArrowNext(QPixmap(QString(":/models/select_arrow_right")));
    addItem(_pixmap_item_stage_color_arrow_right);
    _pixmap_item_stage_color_arrow_right->setPos(238, 238);


    _pixmap_item_character_1 = addPixmap(QPixmap(QString(":/models/portait_char_%1").arg(_id_character1)));
    _pixmap_item_character_1->setPos(83, 185);
    _pixmap_item_character_2 = addPixmap(QPixmap(QString(":/models/select_dance").arg(_id_character2)));
    _pixmap_item_character_2->setPos(309, 185);

    _pixmap_stage = addPixmap(QPixmap(QString(":/models/portait_char_%1")));
    _pixmap_stage->setPos(178, 227);

    _pixmap_color_character_1 = addRect( 83, 230, 24, 24, QPen(Qt::NoPen), QBrush (_color_character1));
    _pixmap_color_character_2 = addRect( 309, 230, 24, 24, QPen(Qt::NoPen), QBrush (_color_character2));

    _timerAnimation->setInterval(200);
    connect(_timerAnimation, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    _timerAnimation->start();

    GameConfigurationValidate* _text_item_validate = new GameConfigurationValidate(QPixmap(QString(":/models/select_dance")));
    _text_item_validate->setPos(156,288);
    addItem(_text_item_validate);

    updateAnimation();

    // add flying at
    QTimeLine* timer = new QTimeLine(rand()%2000);
    timer->connect(timer, SIGNAL(finished()), this, SLOT(SendFlyingCat()));
    timer->start();
}

void GameConfiguration::SendFlyingCat()
{
    QLabel *gif_anim = new QLabel();
    gif_anim->setAttribute( Qt::WA_TranslucentBackground, true );
    QMovie *movie = new QMovie(":/models/flying_cat");
    gif_anim->setMovie(movie);
    movie->start();
    QGraphicsProxyWidget *_flying_cat = addWidget(gif_anim);

    //QGraphicsPixmapItem* _flying_cat = addPixmap(QPixmap(QString(":/models/portait_char_%1").arg(_id_character1)));
    _flying_cat->setPos(-80, -70);
    QTimeLine* timer = new QTimeLine(10000);
    timer->setFrameRange(0, 100);

    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation(this);
    animation->setItem(_flying_cat);
    animation->setTimeLine(timer);

    for (float i = 0.0; i < 200.0; ++i)
        animation->setPosAt (i / 200.0, QPointF(i*qCos(i/200.0)*2.0-70.0, 1.5*i/qCos(200.0+i/100.0)-90.0));
    timer->start();
}

void GameConfiguration::drawBackground ( QPainter * painter, const QRectF & rect )
{
    painter->drawPixmap(0, 0, QPixmap(QString(":/models/%1").arg("bg_menu")));
}

void GameConfiguration::updateAnimation()
{
    _pixmap_item_character_1->setPixmap(QPixmap(QString(":/models/portait_char_%1").arg(_id_character1)));
    _pixmap_item_character_2->setPixmap(QPixmap(QString(":/models/portait_char_%1").arg(_id_character2)));

    _pixmap_color_character_1->setBrush(QBrush (_color_character1));
    _pixmap_color_character_2->setBrush(QBrush (_color_character2));

    switch(GameConfiguration::_stage)
    {
        case MainWindow::choice_level_1:
           _pixmap_stage->setPixmap(QPixmap(QString(":/models/stage1")));
        break;
        case MainWindow::choice_level_2:
            _pixmap_stage->setPixmap(QPixmap(QString(":/models/stage2")));
        break;
        case MainWindow::choice_level_3:
            _pixmap_stage->setPixmap(QPixmap(QString(":/models/stage3")));
        break;
    }
}
