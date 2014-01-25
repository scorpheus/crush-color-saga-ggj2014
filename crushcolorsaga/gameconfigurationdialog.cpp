#include "gameconfigurationdialog.h"
#include "ui_gameconfigurationdialog.h"

#include <QPainter>

GameConfigurationDialog::GameConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::GameConfigurationDialog),
      _timerAnimation(new QTimer(this)),
      _id_character1(1),
      _animationIndex1(0),
      _id_character2(2),
      _animationIndex2(0)
{
    _ui->setupUi(this);

    _ui->character_1->setPixmap(QPixmap(QString(":/models/hero%1_run0%2").arg(_id_character1).arg(_animationIndex1+1)).scaled(64,64));
    _ui->character_2->setPixmap(QPixmap(QString(":/models/hero%1_run0%2").arg(_id_character2).arg(_animationIndex2+1)).scaled(64,64));

    _timerAnimation->setInterval(200);
    connect(_timerAnimation, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    _timerAnimation->start();
}

GameConfigurationDialog::~GameConfigurationDialog()
{
    delete _ui;
}

void GameConfigurationDialog::updateAnimation()
{
    _animationIndex1 = (_animationIndex1 + 1) % 2;
    _animationIndex2 = (_animationIndex2 + 1) % 2;

    _ui->character_1->setPixmap(QPixmap(QString(":/models/hero%1_run0%2").arg(_id_character1).arg(_animationIndex1+1)).scaled(64,64));
    _ui->character_2->setPixmap(QPixmap(QString(":/models/hero%1_run0%2").arg(_id_character2).arg(_animationIndex2+1)).scaled(64,64));
}

void GameConfigurationDialog::on_pushButton_char1_prev_clicked()
{
    --_id_character1;
    if(_id_character1<1)
        _id_character1 = nb_character;
}
void GameConfigurationDialog::on_pushButton_char1_next_clicked()
{
    ++_id_character1;
    if(_id_character1>nb_character)
        _id_character1 = 1;
}
void GameConfigurationDialog::on_pushButton_char2_prev_clicked()
{
    --_id_character2;
    if(_id_character2<1)
        _id_character2 = nb_character;
}
void GameConfigurationDialog::on_pushButton_char2_next_clicked()
{
    ++_id_character2;
    if(_id_character2>nb_character)
        _id_character2 = 1;
}
