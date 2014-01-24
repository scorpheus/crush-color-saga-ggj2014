#ifndef GAMECONFIGURATIONDIALOG_H
#define GAMECONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui { class GameConfigurationDialog; }

class GameConfigurationDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit GameConfigurationDialog(QWidget *parent = 0);
        ~GameConfigurationDialog();

    private:
        Ui::GameConfigurationDialog *_ui;
};

#endif // GAMECONFIGURATIONDIALOG_H
