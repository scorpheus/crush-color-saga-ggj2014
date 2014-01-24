#include "gameconfigurationdialog.h"
#include "ui_gameconfigurationdialog.h"

GameConfigurationDialog::GameConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::GameConfigurationDialog)
{
    _ui->setupUi(this);
}

GameConfigurationDialog::~GameConfigurationDialog()
{
    delete _ui;
}
