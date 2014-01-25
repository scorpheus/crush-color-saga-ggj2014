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
    };

    void ChangeLevel(AllLevel level_choice);

    private:
        Ui::MainWindow *_ui;

    public slots:
};

#endif // MAINWINDOW_H
