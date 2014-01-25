#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameconfiguration.h"

#include "level_1.h"
#include "level_2.h"


MainWindow* g_MainWindow;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    g_MainWindow = this;
    _ui->setupUi(this);

    GameConfiguration* _game_configuration = new GameConfiguration();

     _ui->graphicsView->scene()->deleteLater();
     _ui->graphicsView->setScene(_game_configuration);

    _ui->graphicsView->scale(2, 2);

    music = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(":/models/background_sound"));
    connect(music, SIGNAL(aboutToFinish()), this, SLOT(restartVideo()));
    music->play();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::restartVideo()
{
    music->enqueue(Phonon::MediaSource(QString(":/models/background_sound")));
}

void MainWindow::ChangeLevel(AllLevel level_choice)
{
    Level* _level;
    if(level_choice == choice_level_1)
        _level = new Level_1("level_test");
    else
    if(level_choice == choice_level_2)
        _level = new Level_2("level_colorstripe");

    _current_level = level_choice;

    _level->CreateLevelPlatform();
    _level->FinishCreateLevel();

     _ui->graphicsView->scene()->deleteLater();
     _ui->graphicsView->setScene(_level);
}

void MainWindow::NextLevel()
{
    switch(_current_level)
    {
        case choice_level_1:
           _current_level = choice_level_2;
        break;
        case choice_level_2:
            _current_level = choice_level_1;
        break;
    }

    ChangeLevel(_current_level);
}
