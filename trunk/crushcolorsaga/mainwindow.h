#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }

#include <Phonon/MediaObject>

class SoundManager;

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
       choice_level_3,
       nb_choice_level
    };

    void ChangeLevel(AllLevel level_choice);

    AllLevel _current_level;

   public slots:
        void NextLevel();
        void restartVideo();

    private:
        Ui::MainWindow *_ui;
        Phonon::MediaObject* music;                
        SoundManager *_sound_manager;


    public slots:
};

#endif // MAINWINDOW_H
