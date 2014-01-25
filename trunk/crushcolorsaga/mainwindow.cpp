#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameconfigurationdialog.h"

#include "level_1.h"
#include "level_2.h"

MainWindow* g_MainWindow;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    g_MainWindow = this;
    _ui->setupUi(this);

 //   GameConfigurationDialog dialog(this);
 //   dialog.exec();

    ChangeLevel(choice_level_1);
    _ui->graphicsView->scale(2, 2);
}

MainWindow::~MainWindow()
{
    delete _ui;
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
