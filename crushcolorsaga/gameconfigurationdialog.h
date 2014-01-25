#ifndef GAMECONFIGURATIONDIALOG_H
#define GAMECONFIGURATIONDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QGraphicsItem>

namespace Ui { class GameConfigurationDialog; }

class GameConfigurationDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit GameConfigurationDialog(QWidget *parent = 0);
        ~GameConfigurationDialog();

    int _id_character1;
    int _animationIndex1;
    int _id_character2;
    int _animationIndex2;

    private slots:
        void updateAnimation();

        void on_pushButton_char1_prev_clicked();
        void on_pushButton_char1_next_clicked();
        void on_pushButton_char2_prev_clicked();
        void on_pushButton_char2_next_clicked();

    private:
        Ui::GameConfigurationDialog *_ui;
        QTimer *_timerAnimation;

        static const int nb_character = 2;


};

#endif // GAMECONFIGURATIONDIALOG_H
