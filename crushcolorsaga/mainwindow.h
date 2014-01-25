#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    enum AllLevel
    {
       choice_level_1 = 0,
       choice_level_2,
       nb_choice_level
    };

    void ChangeLevel(AllLevel level_choice);

   public slots:
        void NextLevel();

    private:
        Ui::MainWindow *_ui;

    AllLevel _current_level;

    public slots:
};

#endif // MAINWINDOW_H
