#include "level.h"

#include "contour.h"
#include "character.h"
#include "inputmanager.h"
#include "health_display.h"
#include "gameconfigurationdialog.h"

#include <QPainter>
#include <QImage>

Level::Level(QString level_name, QObject *parent) :
    QGraphicsScene(parent),
    _level_name(level_name)
{
    setSceneRect(0, 0, 427, 341);

    addItem(new Contour(this));
}

void Level::FinishCreateLevel ( )
{
    Character *character1 = new Character(GameConfigurationDialog::_id_character1, this, GREEN);
    character1->moveBy(100, 100);
    addItem(character1);

    Character *character2 = new Character(GameConfigurationDialog::_id_character2, this, BLUE);
    character2->moveBy(132, 100);
    addItem(character2);

    addItem(new HealthDisplay(QPoint(9,18), character1));
    addItem(new HealthDisplay(QPoint(9,29), character2));

    InputManager *inputManager = new InputManager(this);
    connect(inputManager, SIGNAL(state1(Character::States)), character1, SLOT(setStates(Character::States)));
    connect(inputManager, SIGNAL(state2(Character::States)), character2, SLOT(setStates(Character::States)));
}

void Level::drawBackground ( QPainter * painter, const QRectF & rect )
{
    painter->drawPixmap(0, 0, QPixmap(QString(":/models/%1").arg(_level_name)));
}

ColorCharacter Level::GetBackgroundColor(QPoint pos)
{
    QRgb _color = QImage(QString(":/models/%1").arg(_level_name)).pixel(pos);
   if(qRed(_color) > 128)
   {
       if(qBlue(_color) > 128)
       {
           if(qGreen(_color) > 128)
               return WHITE;
           else
               return PURPLE;
       }
       else
       {
           if(qGreen(_color) > 128)
               return YELLOW;
           else
               return RED;
       }
   }
   else
   {
       if(qBlue(_color) > 128)
       {
           if(qGreen(_color) > 128)
               return CYAN;
           else
               return BLUE;
       }
       else
       {
           if(qGreen(_color) > 128)
               return GREEN;
           else
               return BLACK;
       }
   }
}
